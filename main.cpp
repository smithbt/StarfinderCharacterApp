#include "StarfinderCharacterApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qRegisterMetaType<Weapon*>();
	QMetaType::registerComparators<Weapon*>();
	StarfinderCharacterApp w;
	w.show();
	return a.exec();
}
