#include "RangedWeapon.h"

int RangedWeapon::capacity()
{
	return ammo.max;
}

int RangedWeapon::usage()
{
	return ammo.step;
}
