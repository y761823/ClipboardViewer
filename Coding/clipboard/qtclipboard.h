#ifndef QTCLIPBOARD_H
#define QTCLIPBOARD_H

#include "clipboard_i.h"

class QtClipboard : public IClipboard
{
public:
	static QtClipboard* instance()
	{
		static QtClipboard inst;
		return &inst;
	}

	QStringList formats() override;
	bool hasFormat(QString const& format) override;
	QByteArray data(QString const& format) override;
    void setMimeData(QMimeData *pMimeData) override;

private:
	QtClipboard() = default;
};

#endif // QTCLIPBOARD_H
