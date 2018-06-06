#ifndef OPDFCLIPVIEWER_H
#define OPDFCLIPVIEWER_H

#include <CoreGraphics/CGPDFDocument.h>

#include <QWidget>
#include <QScrollArea>
#include "clipviewer_i.h"


class OImageViewer;

class OPdfClipViewer : public QScrollArea, public IClipViewer
{
	Q_OBJECT
public:
	explicit OPdfClipViewer(QWidget *parent = nullptr);

public:
	void setClipData(QByteArray const& data, QString const& mimeType) override;
	void clear() override;

signals:

public slots:

private:
	CGPDFDocumentRef m_cgPdfDocument;
	OImageViewer* m_viewer;
};

#endif // OPDFCLIPVIEWER_H
