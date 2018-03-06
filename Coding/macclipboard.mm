#include "macclipboard.h"

#import <AppKit/NSPasteboard.h>

#include <QStringList>
#include <QByteArray>

QStringList MacClipboard::formats()
{
	NSPasteboard* pasteBoard = [NSPasteboard generalPasteboard];
	NSArray<NSString*>* nsarr = [pasteBoard types];

	QStringList res;
	for (NSString* format in nsarr)
		res.append(QString::fromNSString(format));

	return res;
}

bool MacClipboard::hasFormat(QString const& format)
{
	NSPasteboard* pasteBoard = [NSPasteboard generalPasteboard];
	return [[pasteBoard types] containsObject:format.toNSString()];
}

QByteArray MacClipboard::data(QString const& format)
{
	NSPasteboard* pasteBoard = [NSPasteboard generalPasteboard];
	NSData* nsData = [pasteBoard dataForType:format.toNSString()];
	return QByteArray::fromNSData(nsData);
}
