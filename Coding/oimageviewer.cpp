#include "oimageviewer.h"

#include <QPainter>
#include <QDebug>

OImageViewer::OImageViewer(QWidget *parent) : QWidget(parent)
{

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
	painter.fillRect(this->rect(), Qt::Dense2Pattern);
	painter.drawImage(QPoint(), m_img);
}
