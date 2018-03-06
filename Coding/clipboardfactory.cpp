#include "clipboardfactory.h"
#include <QStringList>
#include <QString>
#include "qtclipboard.h"

#ifdef Q_OS_MAC
#include "macclipboard.h"
#endif

namespace
{
	QString const STypeQtClipboard = "QtClipboard";
	QString const STypeMacClipboard = "MacClipboard";

	QStringList g_clipboardTypeList
	{
		STypeQtClipboard,
	#ifdef Q_OS_MAC
		STypeMacClipboard,
	#endif
	};
}


IClipboard* ClipboardFactory::getClipboard(const QString& clipboardName)
{
	if (clipboardName == STypeQtClipboard)
		return QtClipboard::instance();
#ifdef Q_OS_MAC
	if (clipboardName == STypeMacClipboard)
		return MacClipboard::instance();
#endif
	return nullptr;
}

QStringList ClipboardFactory::getClipboardTypes()
{
	return g_clipboardTypeList;
}

