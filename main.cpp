#include "StarfinderCharacterApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qRegisterMetaType<Weapon>();
	StarfinderCharacterApp w;
	w.show();
	return a.exec();
}
