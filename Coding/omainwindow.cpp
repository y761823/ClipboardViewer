#include "omainwindow.h"
#include "ui_omainwindow.h"

#include <QDebug>

#include "clipboard/clipboardfactory.h"
#include "clipboard/clipboard_i.h"

#include "clipviewer/otextclipviewer.h"
#include "clipviewer/oimageclipviewer.h"
#include "clipviewer/ohtmlclipviewer.h"
#include "clipviewer/oexportclipviewer.h"

OMainWindow::OMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::OMainWindow)
{
	ui->setupUi(this);
	ui->splitter->setStretchFactor(0, 0);
	ui->splitter->setStretchFactor(1, 1);

	ui->clipTypeBox->addItems(ClipboardFactory::getClipboardTypes());

	initTabWidget();

	connect(ui->clipTypeBox, &QComboBox::currentTextChanged, this, &OMainWindow::refreshFormatsWidget);
	connect(ui->getClipBtn, &QPushButton::clicked, this, &OMainWindow::refreshFormatsWidget);
	connect(ui->formatsWidget, &QListWidget::itemSelectionChanged, this, &OMainWindow::refreshValueWidget);
	connect(ui->tabWidget, &QTabWidget::currentChanged, this, &OMainWindow::refreshValueWidget);
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

	{
		OHtmlClipViewer* v = new OHtmlClipViewer();
		ui->tabWidget->addTab(v, tr("Html"));
	}

	{
		OExportClipViewer* v = new OExportClipViewer();
		ui->tabWidget->addTab(v, tr("Export"));
	}
}

void OMainWindow::refreshFormatsWidget()
{
	IClipboard* clipboard = ClipboardFactory::getClipboard(ui->clipTypeBox->currentText());
	QStringList formats = clipboard->formats();

	ui->formatsWidget->clear();
	for (QString const& format : formats)
		ui->formatsWidget->addItem(format);

	refreshValueWidget();
}

void OMainWindow::refreshValueWidget()
{
	QString format;
	QList<QListWidgetItem*> items = ui->formatsWidget->selectedItems();
	if (!items.isEmpty())
		format = items.first()->text();

	QWidget* widget = ui->tabWidget->currentWidget();
	if (IClipViewer* viewer = dynamic_cast<IClipViewer*>(widget))
	{
		IClipboard* clipboard = ClipboardFactory::getClipboard(ui->clipTypeBox->currentText());
		if (!format.isEmpty() && clipboard->hasFormat(format))
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
