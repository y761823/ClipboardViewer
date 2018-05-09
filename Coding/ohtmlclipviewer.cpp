#include "ohtmlclipviewer.h"

#include <QTextBrowser>
#include <QVBoxLayout>
#include <QDebug>

OHtmlClipViewer::OHtmlClipViewer(QWidget *parent) : QWidget(parent)
{
	m_pBrower = new QTextBrowser();

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(m_pBrower);
}

void OHtmlClipViewer::setClipData(const QByteArray &data, const QString &mimeType)
{
	Q_UNUSED(mimeType);
	m_pBrower->setHtml(QString::fromUtf8(data));
}

void OHtmlClipViewer::clear()
{
	m_pBrower->clear();
}
