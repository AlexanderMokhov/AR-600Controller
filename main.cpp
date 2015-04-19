#include "AR600MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AR600MainWindow w;
	w.show();
	
	return a.exec();
}
