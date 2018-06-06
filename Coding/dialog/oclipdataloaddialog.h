#ifndef OCLIPDATALOADDIALOG_H
#define OCLIPDATALOADDIALOG_H

#include <QDialog>

namespace Ui {
class OClipDataLoadDialog;
}

class OClipDataLoadDialog : public QDialog
{
	Q_OBJECT

public:
	explicit OClipDataLoadDialog(QWidget *parent = 0);
	~OClipDataLoadDialog();

public:
	QString getClipFormat();
	QByteArray getClipData();

protected:
	void onBrowserBtnClick();
	void onFileLineEditTextChange();

private:
	Ui::OClipDataLoadDialog *ui;
};

#endif // OCLIPDATALOADDIALOG_H
