#include "omainwindow.h"
#include "ui_omainwindow.h"

#include "clipboardfactory.h"
#include "clipboard_i.h"

#include "otextclipviewer.h"
#include "oimageclipviewer.h"

OMainWindow::OMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::OMainWindow)
{
	ui->setupUi(this);

	ui->clipTypeBox->addItems(ClipboardFactory::getClipboardTypes());

	initTabWidget();

	connect(ui->getClipBtn, &QPushButton::clicked, this, &OMainWindow::refreshFormatsWidget);
	connect(ui->formatsWidget, &QListWidget::currentTextChanged, this, &OMainWindow::refreshValueWidget);
}

OMainWindow::~OMainWindow()
{
	delete ui;
}

void OMainWindow::initTabWidget()
{
	{
		OTextClipViewer* v = new OTextClipViewer();
		ui->tabWidget->addTab(v, tr("Text"));
	}

	{
		OImageClipViewer* v = new OImageClipViewer();
		ui->tabWidget->addTab(v, tr("Image"));
	}
}

void OMainWindow::refreshFormatsWidget()
{
	IClipboard* clipboard = ClipboardFactory::getClipboard(ui->clipTypeBox->currentText());
	QStringList formats = clipboard->formats();

	ui->formatsWidget->clear();
	for (QString const& format : formats)
		ui->formatsWidget->addItem(format);
}

void OMainWindow::refreshValueWidget(QString const& format)
{
	QWidget* widget = ui->tabWidget->currentWidget();
	if (IClipViewer* viewer = dynamic_cast<IClipViewer*>(widget))
	{
		IClipboard* clipboard = ClipboardFactory::getClipboard(ui->clipTypeBox->currentText());
		if (clipboard->hasFormat(format))
		{
			QByteArray bytes = clipboard->data(format);
			viewer->setClipData(bytes, format);
		}
		else
		{
			// 剪贴板已更新
			viewer->clear();
		}
	}
}
