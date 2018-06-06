#include "opdfclipviewer.h"

#include <cmath>

#include <CoreGraphics/CGImage.h>
#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGDataProvider.h>
#include <CoreGraphics/CGBitmapContext.h>
#include <CoreGraphics/CGDirectDisplay.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CFData.h>

#include <QImage>

#include "viewer/oimageviewer.h"

CGColorSpaceRef displayColorSpace()
{
	CGColorSpaceRef colorSpace = 0;
	CGDirectDisplayID displayID = CGMainDisplayID();
	colorSpace = CGDisplayCopyColorSpace(displayID);
	if (colorSpace == 0)
		colorSpace = CGColorSpaceCreateDeviceRGB();
	return colorSpace;
}

// from qt qcocoahelpers.mm 5.6.0
CGContextRef qt_mac_cg_context(QImage *image)
{
	if (!image)
		return 0;

	CGColorSpaceRef colorspace = displayColorSpace();
	uint flags = kCGImageAlphaPremultipliedFirst;
	flags |= kCGBitmapByteOrder32Host;
	CGContextRef ret = CGBitmapContextCreate(image->bits(), image->width(), image->height(),
											8, image->bytesPerLine(), colorspace, flags);
	CGColorSpaceRelease(colorspace);
	return ret;
}

OPdfClipViewer::OPdfClipViewer(QWidget *parent) : QScrollArea(parent)
{
	m_viewer = new OImageViewer();
	this->setWidget(m_viewer);
	this->setWidgetResizable(true);
}

void OPdfClipViewer::setClipData(const QByteArray& data, const QString& mimeType)
{
	Q_UNUSED(mimeType);

	CFDataRef cfData = data.toCFData();
	CGDataProviderRef cgDataProvider = CGDataProviderCreateWithCFData(cfData);
	CGPDFDocumentRef cgPdfDocument = CGPDFDocumentCreateWithProvider(cgDataProvider);

	if (cgPdfDocument)
	{
		size_t pageCnt = CGPDFDocumentGetNumberOfPages(cgPdfDocument);
		for (size_t i = 1; i <= pageCnt; ++i)
		{
			CGPDFPageRef cgPdfPage = CGPDFDocumentGetPage(cgPdfDocument, i);
			QRect rc = QRectF::fromCGRect(CGPDFPageGetBoxRect(cgPdfPage, kCGPDFCropBox)).toRect();
			QImage img(rc.size(), QImage::Format_ARGB32_Premultiplied);
			img.fill(0x00ffffff);

			CGContextRef ctx = qt_mac_cg_context(&img);
			if (ctx)
			{
				CGContextDrawPDFPage(ctx, cgPdfPage);
				CGContextRelease(ctx);
			}
			m_viewer->setImage(img);
		}
	}
	else
	{
		m_viewer->clearImage();
	}

	CGPDFDocumentRelease(cgPdfDocument);
	CGDataProviderRelease(cgDataProvider);
	CFRelease(cfData);
}

void OPdfClipViewer::clear()
{
	m_viewer->clearImage();
}
