#include "Character.h"

Character::Character(QObject* parent)
	: QObject(parent),
	model(new CharacterModel(parent)),
	wModel(new WeaponModel(parent)),
	aModel(new AbilityModel(parent)),
	cModel(new ClassModel(parent))
{
	connect(cModel, &ClassModel::dataChanged, [this](QModelIndex, QModelIndex, QVector<int> roles) {
		if (roles.contains(ClassModel::BAB)) emit babChanged(bab());
		if (roles.contains(ClassModel::Fortitude)) emit fortitudeChanged(fortitude());
		if (roles.contains(ClassModel::Reflex)) emit reflexChanged(reflex());
		if (roles.contains(ClassModel::Will)) emit willChanged(will()); });
	connect(cModel, &ClassModel::modelReset, [this]() {
		emit babChanged(bab());
		emit fortitudeChanged(fortitude());
		emit reflexChanged(reflex());
		emit willChanged(will());
		});
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

int Character::fortitude()
{
	int save = getAbility(Ability::Constitution)->modifier();
	for (int i = 0; i < cModel->rowCount(); ++i) {
		save += cModel->index(i).data(ClassModel::Fortitude).toInt();
	}
	return save;
}

int Character::reflex()
{
	int save = getAbility(Ability::Dexterity)->modifier();
	for (int i = 0; i < cModel->rowCount(); ++i) {
		save += cModel->index(i).data(ClassModel::Reflex).toInt();
	}
	return save;
}

int Character::will()
{
	int save = getAbility(Ability::Wisdom)->modifier();
	for (int i = 0; i < cModel->rowCount(); ++i) {
		save += cModel->index(i).data(ClassModel::Will).toInt();
	}
	return save;
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
