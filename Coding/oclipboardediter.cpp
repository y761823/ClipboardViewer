#include "oclipboardediter.h"
#include "ui_oclipboardediter.h"

#include "clipboard/clipboard_i.h"
#include "dialog/oclipdataloaddialog.h"
#include <QMimeData>
#include <QDebug>

OClipboardEditer::OClipboardEditer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OClipboardEditer)
    , m_clipboard(nullptr)
{
    ui->setupUi(this);

	connect(ui->addBtn, &QPushButton::clicked, this, &OClipboardEditer::addBtnClick);
    connect(ui->removeBtn, &QPushButton::clicked, this, &OClipboardEditer::removeBtnClick);
}

OClipboardEditer::~OClipboardEditer()
{
    delete ui;
}

void OClipboardEditer::initWith(IClipboard *clipboard)
{
    m_clipboard = clipboard;
    m_datas.clear();
    for (QString const& format : clipboard->formats())
    {
        QByteArray const& data = clipboard->data(format);
        m_datas[format] = data;
    }
}

void OClipboardEditer::refreshFormatList()
{
    ui->formatsWidget->clear();
    for (auto it = m_datas.begin(); it != m_datas.end(); ++it)
        ui->formatsWidget->addItem(it->first);
}

void OClipboardEditer::accept()
{
    if (m_clipboard)
    {
        QMimeData mimeData;
        for (auto it = m_datas.begin(); it != m_datas.end(); ++it)
            mimeData.setData(it->first, it->second);
        m_clipboard->setMimeData(&mimeData);
    }

	QDialog::accept();
}

void OClipboardEditer::addBtnClick()
{
	OClipDataLoadDialog dialog(this);
	int result = dialog.exec();
	if (result == QDialog::Accepted)
	{
		QString format = dialog.getClipFormat();
		QByteArray bytes = dialog.getClipData();
		if (!format.isEmpty() && !bytes.isEmpty())
		{
			m_datas[format] = bytes;
			refreshFormatList();
		}
	}
}

void OClipboardEditer::removeBtnClick()
{
    QList<QListWidgetItem*> list = ui->formatsWidget->selectedItems();
    for (QListWidgetItem* pItem : list)
    {
        auto it = m_datas.find(pItem->text());
        if (it != m_datas.end())
            m_datas.erase(it);
    }
    refreshFormatList();
}

void OClipboardEditer::showEvent(QShowEvent* e)
{
    refreshFormatList();
    QDialog::showEvent(e);
}
