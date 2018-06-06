#ifndef OIMAGEVIEWER_H
#define OIMAGEVIEWER_H

#include <QWidget>
#include <QImage>

class OImageViewer : public QWidget
{
	Q_OBJECT
public:
	explicit OImageViewer(QWidget *parent = nullptr);

	void setImage(QImage img);
	void clearImage();

protected:
	void paintEvent(QPaintEvent *) override;
signals:

public slots:

private:
	QImage m_img;
	QBrush m_bgBrush;
};

#endif // OIMAGEVIEWER_H
