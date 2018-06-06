#include "oclipdataloaddialog.h"
#include "ui_oclipdataloaddialog.h"

#include <QFileDialog>
#include <QFile>

OClipDataLoadDialog::OClipDataLoadDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OClipDataLoadDialog)
{
	ui->setupUi(this);

	connect(ui->browserBtn, &QPushButton::clicked, this, &OClipDataLoadDialog::onBrowserBtnClick);
	connect(ui->fileLineEdit, &QLineEdit::textChanged, this, &OClipDataLoadDialog::onFileLineEditTextChange);
}

OClipDataLoadDialog::~OClipDataLoadDialog()
{
	delete ui;
}

QString OClipDataLoadDialog::getClipFormat()
{
	return ui->formatLineEdit->text();
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
