#include "Character.h"

Character::Character(QObject* parent)
	: QObject(parent),
	characterName(QString()),
	bab(0),
	fortitude(0),
	reflex(0),
	will(0),
	stamina(new Resource(this)),
	abilities({
		{"Strength", new Ability(this) },
		{"Dexterity", new Ability(this) },
		{"Constitution", new Ability(this) },
		{"Intelligence", new Ability(this) },
		{"Wisdom", new Ability(this) },
		{"Charisma", new Ability(this) }, }),
	weapons()
{
}

Character::~Character()
{
	delete stamina;

	qDeleteAll(abilities);

	qDeleteAll(weapons);
}

QString Character::getCharacterName() const
{
	return characterName;
}

int Character::getBAB() const
{
	return bab;
}

int Character::getFortitude() const
{
	return fortitude;
}

int Character::getReflex() const
{
	return reflex;
}

int Character::getWill() const
{
	return will;
}

Resource* Character::getStamina() const
{
	return stamina;
}

Ability* Character::getAbility(const QString abilityName) const
{
	if (abilities.contains(abilityName))
		return abilities.value(abilityName);
	return nullptr;
}

void Character::setCharacterName(const QString name)
{
	characterName = name;
}

void Character::setStamina(Resource* s)
{
	stamina = s;
}

void Character::setAbility(const QString abilityName, Ability* a)
{
	if (abilities.contains(abilityName))
		abilities.insert(abilityName, a);
}

QVector<Weapon*> Character::getWeapons() const
{
	return weapons;
}

void Character::setWeapons(const QVector<Weapon*> newWeapons)
{
	if (newWeapons != weapons) {
		weapons = newWeapons;
		emit weaponListChanged(weapons);
	}
}

Weapon* Character::getWeaponAt(int index) const
{
	return weapons.at(index);
}

void Character::setWeaponAt(int index, Weapon* weapon)
{
	weapons.replace(index, weapon);
	emit weaponListChanged(weapons);
}

void Character::insertWeaponAt(int index, Weapon* weapon)
{
	weapons.insert(index, weapon);
	emit weaponListChanged(weapons);
}

void Character::removeWeaponAt(int index)
{
	Weapon* w = weapons.takeAt(index);
	delete w;
	emit weaponListChanged(weapons);
}

int Character::getWeaponCount() const
{
	return weapons.size();
}

void Character::read(const QJsonObject& json)
{
	// Parse Strings
	if (json.contains("CharacterName") && json.value("CharacterName").isString())
		characterName = json.value("CharacterName").toString();

	// Parse Ints
	if (json.contains("BAB") && json.value("BAB").isDouble())
		bab = json.value("BAB").toInt();
	if (json.contains("Fortitude") && json.value("Fortitude").isDouble())
		fortitude = json.value("Fortitude").toInt();
	if (json.contains("Reflex") && json.value("Reflex").isDouble())
		reflex = json.value("Reflex").toInt();
	if (json.contains("Will") && json.value("Will").isDouble())
		will = json.value("Will").toInt();

	// Parse Resources
	if (json.contains("Stamina") && json.value("Stamina").isObject()) 
		stamina->read(json.value("Stamina").toObject());

	// Parse Abilities
	if (json.contains("Abilities") && json.value("Abilities").isObject()) {
		QJsonObject aObject = json.value("Abilities").toObject();
		for (QHash<QString, Ability*>::Iterator i = abilities.begin(); i != abilities.end(); ++i)
			if (aObject.contains(i.key()) && aObject.value(i.key()).isObject()) {
				i.value()->read(aObject.value(i.key()).toObject());
			}
	}

	if (json.contains("Weapons") && json.value("Weapons").isArray()) {
		QJsonArray wArray = json.value("Weapons").toArray();
		qDeleteAll(weapons);
		weapons.clear();
		for (int i = 0; i < wArray.size(); ++i) {
			QJsonObject wObj = wArray.at(i).toObject();
			Weapon* w = new Weapon(this);
			w->read(wObj);
			int aMod = bab;
			int dMod = 0;
			switch (w->type) {
			case Weapon::Type::Melee:
				aMod += abilities.value("Strength")->modifier();
				dMod = (abilities.value("Strength")->modifier());
				break;
			case Weapon::Type::Ranged:
				aMod += abilities.value("Dexterity")->modifier();
				break;
			}
			w->attackMod = aMod;
			w->damageMod = dMod;
			weapons.append(w);
		}
	}
}

void Character::write(QJsonObject& json) const
{
	json.insert("CharacterName", characterName);
	json.insert("BAB", bab);
	json.insert("Fortitude", fortitude);
	json.insert("Reflex", reflex);
	json.insert("Will", will);

	// Resources
	json.insert("Stamina", stamina->toJsonObject());

	// Abilities
	QJsonObject aObject;
	for (QHash<QString, Ability*>::ConstIterator i = abilities.begin(); i != abilities.end(); ++i)
		aObject.insert(i.key(), i.value()->toJsonObject());
	json.insert("Abilities", aObject);
	
	QJsonArray wArray;
	for (Weapon* w : weapons)
		wArray.append(w->toJsonObject());
	json.insert("Weapons", wArray);
}

QJsonObject Character::toJsonObject() const
{
	QJsonObject json;
	write(json);
	return json;
}
