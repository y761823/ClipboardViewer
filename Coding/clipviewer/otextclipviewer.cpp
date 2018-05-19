#include "otextclipviewer.h"

#include <QTextBrowser>
#include <QVBoxLayout>
#include <QDebug>

OTextClipViewer::OTextClipViewer(QWidget *parent) : QWidget(parent)
{
	m_pBrower = new QTextBrowser();

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(m_pBrower);
}

void OTextClipViewer::setClipData(const QByteArray &data, const QString &mimeType)
{
	Q_UNUSED(mimeType);
	m_pBrower->setPlainText(QString::fromUtf8(data));
}

void OTextClipViewer::clear()
{
	m_pBrower->clear();
}

