#include "Character.h"

Character::Character(QObject* parent)
	: QObject(parent),
	model(new CharacterModel(parent)),
	wModel(new WeaponModel(parent)),
	aModel(new AbilityModel(parent)),
	cModel(new ClassModel(parent))
{
	connect(cModel, &ClassModel::dataChanged, [this](QModelIndex, QModelIndex, QVector<int> roles) mutable { 
		if (roles.contains(ClassModel::BAB)) emit babChanged(bab()); });
}

Character::~Character()
{
	delete model;
	delete aModel;
	delete wModel;
	delete cModel;
}

int Character::bab()
{
	int bab = 0;
	for (int i = 0; i < cModel->rowCount(); ++i) {
		bab += cModel->index(i).data(ClassModel::BAB).toInt();
	}
	return bab;
}

void Character::setProperty(CharacterModel::Key k, QVariant& value) 
{
	QModelIndex index = model->index(k);
	if (!index.isValid())
		model->insertRow(k);
	model->setData(model->index(k), value);
}

void Character::setClassLevelPair(QString name, int level)
{
	cModel->insertRow(0);
	cModel->setItemData(cModel->index(0), { 
		{ClassModel::Name,	name},
		{ClassModel::Level,	level} });
}

void Character::addWeapon(Weapon* w)
{
	wModel->insertRow(0);
	wModel->setData(wModel->index(0), QVariant::fromValue(w));
}

Ability* Character::getAbility(Ability::Score s)
{
	return aModel->index(s, 0).data().value<Ability*>();
}

void Character::setAbility(Ability* a)
{
	aModel->setData(aModel->index(a->type), QVariant::fromValue(a));
}

void Character::read(const QJsonObject& json)
{
	model->read(json);
	wModel->read(json);
	aModel->read(json);
	cModel->read(json);
}

void Character::write(QJsonObject& json) const
{
	model->write(json);
	wModel->write(json);
	aModel->write(json);
	cModel->write(json);
}
