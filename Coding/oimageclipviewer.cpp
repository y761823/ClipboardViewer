#include "oimageclipviewer.h"
#include "ui_oimageclipviewer.h"

#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QClipboard>

OImageClipViewer::OImageClipViewer(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::OImageClipViewer),
	m_pImg(nullptr)
{
	ui->setupUi(this);
}

OImageClipViewer::~OImageClipViewer()
{
	delete ui;
}

void OImageClipViewer::setClipData(const QByteArray &data, const QString &mimeType)
{
	delete m_pImg;
	m_pImg = nullptr;

	if (mimeType == "application/x-qt-image")
	{
		QImage img = QGuiApplication::clipboard()->image();
		if (!img.isNull())
			m_pImg = new QImage(img);
	}
	else
	{
		QImageReader reader(data);
		if (reader.canRead())
		{
			QImage img = reader.read();
			if (!img.isNull())
				m_pImg = new QImage(img);
		}
	}

	update();
}

void OImageClipViewer::clear()
{
	if (m_pImg)
	{
		delete m_pImg;
		m_pImg = nullptr;
		update();
	}
}

void OImageClipViewer::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.fillRect(this->rect(), Qt::white);
	if (m_pImg)
		painter.drawImage(QPoint(0, 0), *m_pImg);
}
