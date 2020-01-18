#include "StarfinderCharacterApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qRegisterMetaType<Weapon*>();
	QMetaType::registerComparators<Weapon*>();
	qRegisterMetaType<RangedWeapon*>();
	QMetaType::registerComparators<RangedWeapon*>();
	qRegisterMetaType<Ability*>();
	QMetaType::registerComparators<Ability*>();
	StarfinderCharacterApp w;
	w.show();
	return a.exec();
}
