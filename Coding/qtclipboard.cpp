#include "qtclipboard.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QStringList>
#include <QMimeData>
#include <QByteArray>

QStringList QtClipboard::formats()
{
	QClipboard* clipboard = QGuiApplication::clipboard();
	QMimeData const* mimeData = clipboard->mimeData();
	return mimeData->formats();
}

bool QtClipboard::hasFormat(QString const& format)
{
	QClipboard* clipboard = QGuiApplication::clipboard();
	QMimeData const* mimeData = clipboard->mimeData();
	return mimeData->hasFormat(format);
}

QByteArray QtClipboard::data(QString const& format)
{
	QClipboard* clipboard = QGuiApplication::clipboard();
	QMimeData const* mimeData = clipboard->mimeData();
	return mimeData->data(format);
}
