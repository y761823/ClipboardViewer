#include "oimageclipviewer.h"
#include "ui_oimageclipviewer.h"

#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QClipboard>
#include <QBuffer>

#include "viewer/oimageviewer.h"

OImageClipViewer::OImageClipViewer(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::OImageClipViewer)
{
	ui->setupUi(this);

	m_viewer = new OImageViewer();
	ui->scrollArea->setWidget(m_viewer);
}

OImageClipViewer::~OImageClipViewer()
{
	delete ui;
}

void OImageClipViewer::setClipData(const QByteArray &data, const QString &mimeType)
{
	QImage img;
	if (mimeType == "application/x-qt-image")
	{
		img = QGuiApplication::clipboard()->image();
	}
	else
	{
		QByteArray barr = data;
		QBuffer buff(&barr);
		QImageReader reader(&buff);
		if (reader.canRead())
			img = reader.read();
	}

	if (!img.isNull())
	{
		m_viewer->setImage(img);

		ui->sizeLine->setText(QString("%1x%2").arg(img.width()).arg(img.height()));
		ui->sizeLine->setEnabled(true);
	}
	else
		clear();
}

void OImageClipViewer::clear()
{
	m_viewer->clearImage();
	ui->sizeLine->setEnabled(false);
}
