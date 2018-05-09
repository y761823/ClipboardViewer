#include "oexportclipviewer.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

OExportClipViewer::OExportClipViewer(QWidget *parent) : QWidget(parent)
{
	m_btn = new QPushButton(tr("Export"));
	m_btn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	QVBoxLayout* vLayout = new QVBoxLayout(this);
	vLayout->addWidget(m_btn, 0, Qt::AlignCenter);

	connect(m_btn, &QPushButton::clicked, this, &OExportClipViewer::onExportClick);
}

void OExportClipViewer::setClipData(const QByteArray& data, const QString& mimeType)
{
	m_data = data;
	m_mimeType = mimeType;
	m_btn->setEnabled(!m_data.isEmpty());
}

void OExportClipViewer::clear()
{
	m_data = {};
	m_mimeType.clear();
	m_btn->setEnabled(false);
}

void OExportClipViewer::onExportClick()
{
	QString fileName = QFileDialog::getSaveFileName();
	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (file.open(QFile::WriteOnly))
		{
			file.write(m_data);
			file.close();
		}
		else
		{
			QMessageBox box(QMessageBox::NoIcon, tr("Error"), tr("Can't open %1").arg(fileName), QMessageBox::Ok);
			box.exec();
		}
	}
}
