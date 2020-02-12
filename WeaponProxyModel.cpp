#include "WeaponProxyModel.h"

WeaponProxyModel::WeaponProxyModel(QObject* parent)
	: QIdentityProxyModel(parent),
	bab(0),
	cModel(nullptr)
{
}

WeaponProxyModel::~WeaponProxyModel()
{
}

void WeaponProxyModel::setBAB(int b)
{
	bab = b;
}

void WeaponProxyModel::setCharacterModel(CharacterModel* cm)
{
	cModel = cm;
}

QVariant WeaponProxyModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) // invalid index
		return QVariant();

	const int idx = index.row();
	if (idx >= sourceModel()->rowCount() || idx < 0) // out of range
		return QVariant();

	QVariant sourceData = sourceModel()->data(index);
	if (sourceData.canConvert<Weapon*>()) {
		if (role == WeaponRole)
			return sourceData;

		const Weapon* w = sourceData.value<Weapon*>();
		int aMod = 0;
		int dMod = 0;
		switch (w->type) {
		case Weapon::Type::Melee:
			aMod = (bab + cModel->index(CharacterModel::Strength).data().value<Ability*>()->modifier());
			dMod = (cModel->index(CharacterModel::Strength).data().value<Ability*>()->modifier());
			break;
		case Weapon::Type::Ranged:
			aMod = (bab + cModel->index(CharacterModel::Dexterity).data().value<Ability*>()->modifier());
			break;
		default:
			aMod = bab;
		}

		if (role == AttackRole)
			return aMod;

		if (role == DamageRole)
			return dMod;

		if (role == Qt::DisplayRole) {
			QString attack = QString::asprintf("%+i", aMod);
			QString damage = w->damage->dice() + QString::asprintf("%+i ", dMod) + w->damage->type;
			QString listing = QString("%1: %2 / %3").arg(w->name).arg(attack).arg(damage);
			return listing;
		}
	}

	return QIdentityProxyModel::data(index, role);
}

QHash<int, QByteArray> WeaponProxyModel::roleNames() const
{
	QHash<int, QByteArray> names;
	names[WeaponRole] = "weapon";
	names[AttackRole] = "attack";
	names[DamageRole] = "damage";
	return names;
}
