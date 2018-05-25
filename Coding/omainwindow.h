#ifndef OMAINWINDOW_H
#define OMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class OMainWindow;
}

class OMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit OMainWindow(QWidget *parent = 0);
	~OMainWindow();

protected:
	void initTabWidget();
	void refreshFormatsWidget();
	void refreshValueWidget();
    void showClipboradEditer();

private:
	Ui::OMainWindow *ui;
};

#endif // OMAINWINDOW_H
