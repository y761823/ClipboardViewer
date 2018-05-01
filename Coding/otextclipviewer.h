#ifndef QTEXTCLIPVIEWER_H
#define QTEXTCLIPVIEWER_H

#include <QWidget>
#include "clipviewer_i.h"

class QTextBrowser;

class OTextClipViewer : public QWidget, public IClipViewer
{
	Q_OBJECT
public:
	explicit OTextClipViewer(QWidget *parent = 0);

public:
	void setClipData(const QByteArray &data, const QString &mimeType) override;
	void clear() override;

signals:

public slots:

private:
	QTextBrowser* m_pBrower;
};

#endif // QTEXTCLIPVIEWER_H
