#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QStringList>
#include <QString>
#include <QByteArray>
#include <QPlainTextEdit>
#include "clipboardfactory.h"
#include "clipboard_i.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPushButton* getClipBtn = new QPushButton("从剪贴板获取数据", this);
    connect(getClipBtn, &QPushButton::clicked, this, &MainWindow::refreshFormatsWidget);

	clipTypeBox = new QComboBox(this);
	clipTypeBox->addItems(ClipboardFactory::getClipboardTypes());

    QHBoxLayout* hLayoutTop = new QHBoxLayout();
    hLayoutTop->addWidget(clipTypeBox);
    hLayoutTop->addWidget(getClipBtn);

    formatsWidget = new QListWidget(this);
    connect(formatsWidget, &QListWidget::currentTextChanged, this, &MainWindow::refreshValueWidget);

    valueWidget = new QPlainTextEdit(this);
    valueWidget->setReadOnly(true);

    QHBoxLayout* hLayoutMid = new QHBoxLayout();
    hLayoutMid->addWidget(formatsWidget);
    hLayoutMid->addWidget(valueWidget);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayoutTop);
    vLayout->addLayout(hLayoutMid);

    QWidget* widget = new QWidget(this);
    widget->setLayout(vLayout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::refreshFormatsWidget()
{
	IClipboard* clipboard = ClipboardFactory::getClipboard(clipTypeBox->currentText());
	QStringList formats = clipboard->formats();

    formatsWidget->clear();
    for (QString const& format : formats)
        formatsWidget->addItem(format);
}

void MainWindow::refreshValueWidget(QString const& format)
{
	IClipboard* clipboard = ClipboardFactory::getClipboard(clipTypeBox->currentText());
	if (clipboard->hasFormat(format))
    {
		QByteArray bytes = clipboard->data(format);
        QString str = QString::fromUtf8(bytes);
        valueWidget->setPlainText(str);
        valueWidget->setReadOnly(true);
    }
    else
    {
        // 剪贴板已更新
//        refreshFormatsWidget();
        valueWidget->clear();
    }
}
