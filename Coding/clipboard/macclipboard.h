#ifndef MACCLIPBOARD_H
#define MACCLIPBOARD_H

#include "clipboard_i.h"

class MacClipboard : public IClipboard
{
public:
	static MacClipboard* instance()
	{
		static MacClipboard inst;
		return &inst;
	}

	QStringList formats() override;
	bool hasFormat(QString const& format) override;
	QByteArray data(QString const& format) override;

private:
	MacClipboard() = default;
};

#endif // MACCLIPBOARD_H
