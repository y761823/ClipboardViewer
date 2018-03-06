#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListWidget;
class QPlainTextEdit;
class QComboBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void refreshFormatsWidget();
    void refreshValueWidget(QString const& format);

private:
    QListWidget* formatsWidget;
    QPlainTextEdit* valueWidget;
	QComboBox* clipTypeBox;
};

#endif // MAINWINDOW_H
