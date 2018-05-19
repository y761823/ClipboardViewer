#ifndef OHTMLCLIPVIEWER_H
#define OHTMLCLIPVIEWER_H

#include <QWidget>
#include "clipviewer_i.h"

class QTextBrowser;

class OHtmlClipViewer : public QWidget, public IClipViewer
{
	Q_OBJECT
public:
	explicit OHtmlClipViewer(QWidget *parent = nullptr);

public:
	void setClipData(const QByteArray &data, const QString &mimeType) override;
	void clear() override;

signals:

public slots:

private:
	QTextBrowser* m_pBrower;
};

#endif // OHTMLCLIPVIEWER_H
