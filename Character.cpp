#include "Character.h"

Character::Character(QObject* parent)
	: QObject(parent),
	model(new CharacterModel(this)),
	wModel(new WeaponModel(this)),
	cModel(new ClassModel(this))
{
	connect(cModel, &ClassModel::dataChanged, [this](QModelIndex, QModelIndex, QVector<int> roles) {
		if (roles.contains(ClassModel::BAB)) setProperty(CharacterModel::BAB, QVariant(bab()));
		if (roles.contains(ClassModel::Fortitude)) setProperty(CharacterModel::Fortitude, QVariant(fortitude()));
		if (roles.contains(ClassModel::Reflex)) setProperty(CharacterModel::Reflex, QVariant(reflex()));
		if (roles.contains(ClassModel::Will)) setProperty(CharacterModel::Will, QVariant(will()));
		});
}

Character::~Character()
{
	delete model;
	delete wModel;
	delete cModel;
}

void Character::runWizard()
{
	CreatorWizard wizard;
	wizard.setClassList(cModel->allClassNames());
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
	int save = getProperty(CharacterModel::Constitution).value<Ability*>()->modifier();
	for (int i = 0; i < cModel->rowCount(); ++i) {
		save += cModel->index(i).data(ClassModel::Fortitude).toInt();
	}
	return save;
}

int Character::reflex()
{
	int save = getProperty(CharacterModel::Dexterity).value<Ability*>()->modifier();
	for (int i = 0; i < cModel->rowCount(); ++i) {
		save += cModel->index(i).data(ClassModel::Reflex).toInt();
	}
	return save;
}

int Character::will()
{
	int save = getProperty(CharacterModel::Wisdom).value<Ability*>()->modifier();
	for (int i = 0; i < cModel->rowCount(); ++i) {
		save += cModel->index(i).data(ClassModel::Will).toInt();
	}
	return save;
}

int Character::stamina()
{
	int conMod = getProperty(CharacterModel::Constitution).value<Ability*>()->modifier();
	int stamina = 0;
	for (int i = 0; i < cModel->rowCount(); ++i) {
		stamina += (cModel->index(i).data(ClassModel::Stamina).toInt() 
			+ (conMod * cModel->index(i).data(ClassModel::Level).toInt()));
	}
	return stamina;
}

void Character::setProperty(CharacterModel::RowIndex k, QVariant& value, int role)
{
	model->setData(model->index(k), value, role);
}

QVariant Character::getProperty(CharacterModel::RowIndex row)
{
	return model->index(row).data();
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

void Character::read(const QJsonObject& json)
{
	model->read(json);
	wModel->read(json);
	cModel->read(json);
}

void Character::write(QJsonObject& json) const
{
	model->write(json);
	wModel->write(json);
	cModel->write(json);
}
