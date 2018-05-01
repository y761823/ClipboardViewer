#ifndef OIMAGECLIPVIEWER_H
#define OIMAGECLIPVIEWER_H

#include <QWidget>
#include "clipviewer_i.h"

namespace Ui {
class OImageClipViewer;
}

class QImage;

class OImageClipViewer : public QWidget, public IClipViewer
{
	Q_OBJECT

public:
	explicit OImageClipViewer(QWidget *parent = 0);
	~OImageClipViewer();

public:
	void setClipData(QByteArray const& data, QString const& mimeType) override;
	void clear() override;

protected:
	void paintEvent(QPaintEvent* e) override;

private:
	Ui::OImageClipViewer *ui;
	QImage* m_pImg;
};

#endif // OIMAGECLIPVIEWER_H
