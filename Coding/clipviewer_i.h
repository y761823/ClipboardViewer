#ifndef CLIPVIEWER_I_H
#define CLIPVIEWER_I_H

class QByteArray;
class QString;

struct IClipViewer
{
	virtual void setClipData(QByteArray const& data, QString const& mimeType) = 0;
	virtual void clear() = 0;
};

#endif // CLIPVIEWER_I_H
