#ifndef OEXPORTCLIPVIEWER_H
#define OEXPORTCLIPVIEWER_H

#include <QWidget>
#include "clipviewer_i.h"

#include <QByteArray>
#include <QString>

class QPushButton;

class OExportClipViewer : public QWidget, public IClipViewer
{
	Q_OBJECT
public:
	explicit OExportClipViewer(QWidget *parent = nullptr);

public:
	void setClipData(const QByteArray &data, const QString &mimeType) override;
	void clear() override;

signals:

public slots:
	void onExportClick();

private:
	QByteArray m_data;
	QString m_mimeType;
	QPushButton* m_btn;
};

#endif // OEXPORTCLIPVIEWER_H
