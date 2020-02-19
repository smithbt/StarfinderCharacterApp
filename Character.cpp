#include "Character.h"

Character::Character(QObject* parent)
	: QObject(parent),
	characterName(QString()),
	bab(0),
	fortitude(0),
	reflex(0),
	will(0),
	stamina(new Resource(this)),
	strength(new Ability(this)),
	dexterity(new Ability(this)),
	constitution(new Ability(this)),
	intelligence(new Ability(this)),
	wisdom(new Ability(this)),
	charisma(new Ability(this)),
	weapons()
{
}

Character::~Character()
{
	delete stamina;

	delete strength;
	delete dexterity;
	delete constitution;
	delete intelligence;
	delete wisdom;
	delete charisma;

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

Ability* Character::getStrength() const
{
	return strength;
}

Ability* Character::getDexterity() const
{
	return dexterity;
}

Ability* Character::getConstitution() const
{
	return constitution;
}

Ability* Character::getIntelligence() const
{
	return intelligence;
}

Ability* Character::getWisdom() const
{
	return wisdom;
}

Ability* Character::getCharisma() const
{
	return charisma;
}

void Character::setCharacterName(const QString name)
{
	characterName = name;
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
	if (json.contains("Strength") && json.value("Strength").isObject())
		strength->read(json.value("Strength").toObject());
	if (json.contains("Dexterity") && json.value("Dexterity").isObject())
		dexterity->read(json.value("Dexterity").toObject());
	if (json.contains("Constitution") && json.value("Constitution").isObject()) 
		constitution->read(json.value("Constitution").toObject());
	if (json.contains("Intelligence") && json.value("Intelligence").isObject()) 
		intelligence->read(json.value("Intelligence").toObject());
	if (json.contains("Wisdom") && json.value("Wisdom").isObject()) 
		wisdom->read(json.value("Wisdom").toObject());
	if (json.contains("Charisma") && json.value("Charisma").isObject()) 
		charisma->read(json.value("Charisma").toObject());

	if (json.contains("Weapons") && json.value("Weapons").isArray()) {
		QJsonArray wArray = json.value("Weapons").toArray();
		qDeleteAll(weapons);
		for (int i = 0; i < wArray.size(); ++i) {
			QJsonObject wObj = wArray.at(i).toObject();
			Weapon* w = new Weapon(this);
			w->read(wObj);
			int aMod = bab;
			int dMod = 0;
			switch (w->type) {
			case Weapon::Type::Melee:
				aMod += strength->modifier();
				dMod = (strength->modifier());
				break;
			case Weapon::Type::Ranged:
				aMod += dexterity->modifier();
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
	json.insert("Strength", strength->toJsonObject());
	json.insert("Dexterity", dexterity->toJsonObject());
	json.insert("Constitution", constitution->toJsonObject());
	json.insert("Intelligence", intelligence->toJsonObject());
	json.insert("Wisdom", wisdom->toJsonObject());
	json.insert("Charisma", charisma->toJsonObject());
	
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
