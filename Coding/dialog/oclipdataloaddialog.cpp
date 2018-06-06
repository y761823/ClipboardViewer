#include "oclipdataloaddialog.h"
#include "ui_oclipdataloaddialog.h"

#include <QFileDialog>
#include <QFile>

OClipDataLoadDialog::OClipDataLoadDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OClipDataLoadDialog)
{
	ui->setupUi(this);

#ifdef Q_OS_MAC
	ui->formatEdit->addItem("com.adobe.pdf");
	ui->formatEdit->addItem("public.tiff");
	ui->formatEdit->addItem("public.utf8-plain-text");
	ui->formatEdit->addItem("public.html");
	ui->formatEdit->addItem("public.url");
	ui->formatEdit->addItem("public.png");
	ui->formatEdit->addItem("public.jpeg");
#endif
	ui->formatEdit->setCurrentIndex(-1);

	connect(ui->browserBtn, &QPushButton::clicked, this, &OClipDataLoadDialog::onBrowserBtnClick);
	connect(ui->fileLineEdit, &QLineEdit::textChanged, this, &OClipDataLoadDialog::onFileLineEditTextChange);
}

OClipDataLoadDialog::~OClipDataLoadDialog()
{
	delete ui;
}

QString OClipDataLoadDialog::getClipFormat()
{
	return ui->formatEdit->currentText();
}

QByteArray OClipDataLoadDialog::getClipData()
{
	QByteArray res;
	QString fileName = ui->fileLineEdit->text();
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly))
		res = file.readAll();
	return res;
}

void OClipDataLoadDialog::onBrowserBtnClick()
{
	QString fileName = QFileDialog::getOpenFileName(this);
	this->raise(); // bug on Mac?
	if (!fileName.isEmpty())
		ui->fileLineEdit->setText(fileName);
}

void OClipDataLoadDialog::onFileLineEditTextChange()
{
	QFileInfo info(ui->fileLineEdit->text());
	if (info.exists())
	{
		QPalette palette = ui->fileLineEdit->palette();
		palette.setColor(QPalette::Text, Qt::black);
		ui->fileLineEdit->setPalette(palette);
	}
	else
	{
		QPalette palette = ui->fileLineEdit->palette();
		palette.setColor(QPalette::Text, Qt::red);
		ui->fileLineEdit->setPalette(palette);
	}
}
