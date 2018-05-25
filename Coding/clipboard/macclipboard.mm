#include "macclipboard.h"

#import <AppKit/NSPasteboard.h>
#import <AppKit/NSPasteboardItem.h>

#include <QStringList>
#include <QByteArray>
#include <QMimeData>

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

void MacClipboard::setMimeData(QMimeData* pMimeData)
{
    NSPasteboardItem* nsItem = [NSPasteboardItem new];
    for (QString const& format : pMimeData->formats())
    {
        QByteArray const& data = pMimeData->data(format);
        [nsItem setData:data.toRawNSData() forType:format.toNSString()];
    }

    NSPasteboard* pasteBoard = [NSPasteboard generalPasteboard];
    [pasteBoard clearContents];
    [pasteBoard writeObjects:@[nsItem]];
}
