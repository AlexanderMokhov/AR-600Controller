#include "AR600Controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AR600Controller w;
	w.show();
	
	return a.exec();
}
