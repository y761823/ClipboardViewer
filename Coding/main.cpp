#include "omainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	OMainWindow w;
    w.show();

    return a.exec();
}
