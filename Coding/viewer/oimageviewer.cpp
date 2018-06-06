#include "oimageviewer.h"

#include <QPainter>
#include <QDebug>

OImageViewer::OImageViewer(QWidget *parent) : QWidget(parent)
{
	int s = 12;
	QImage img(2 * s, 2 * s, QImage::Format_ARGB32_Premultiplied);
	img.fill(0xffffffff);
	QPainter painter(&img);
	painter.fillRect(QRect(0, 0, s, s), QColor(0xffcccccc));
	painter.fillRect(QRect(s, s, s, s), QColor(0xffcccccc));
	m_bgBrush = QBrush(img);
}

void OImageViewer::setImage(QImage img)
{
	if (!img.isNull())
	{
		m_img = img;
		setFixedSize(img.size());
		setVisible(true);
		update();
	}
	else
	{
		clearImage();
	}
}

void OImageViewer::clearImage()
{
	m_img = {};
	setVisible(false);
}

void OImageViewer::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.fillRect(this->rect(), m_bgBrush);
	painter.drawImage(QPoint(), m_img);
}
