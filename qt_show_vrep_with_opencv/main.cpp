#include "OpencvShow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpencvShow w;
    w.show();
	return a.exec();
}
