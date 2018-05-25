#ifndef CLIPBOARD_I_H
#define CLIPBOARD_I_H

class QStringList;
class QString;
class QByteArray;
class QMimeData;

struct IClipboard
{
	virtual QStringList formats() = 0;
	virtual bool hasFormat(QString const& format) = 0;
	virtual QByteArray data(QString const& format) = 0;
    virtual void setMimeData(QMimeData* pMimeData) = 0;
};

#endif // CLIPBOARD_I_H
