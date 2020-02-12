#include "StarfinderCharacterApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StarfinderCharacterApp w;
	w.show();
	return a.exec();
}
