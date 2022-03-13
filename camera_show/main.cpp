#include "videodisplayinqt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	videodisplayinqt w;
	w.show();
	return a.exec();
}
