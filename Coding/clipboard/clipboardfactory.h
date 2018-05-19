#ifndef CLIPBOARDFACTORY_H
#define CLIPBOARDFACTORY_H

class QString;
class QStringList;
struct IClipboard;

class ClipboardFactory
{
public:
	static IClipboard* getClipboard(QString const& clipboardName);
	static QStringList getClipboardTypes();
};

#endif // CLIPBOARDFACTORY_H
