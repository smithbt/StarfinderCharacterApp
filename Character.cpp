#include "Character.h"

Character::Character(QObject* parent)
	: QObject(parent),
	characterName(QString()),
	race(new Race(this)),
	pcClass(new ClassInfo(this)),
	stamina(new Resource(this)),
	hitpoints(new Resource(this)),
	abilities({
		{"Strength", new Ability(this) },
		{"Dexterity", new Ability(this) },
		{"Constitution", new Ability(this) },
		{"Intelligence", new Ability(this) },
		{"Wisdom", new Ability(this) },
		{"Charisma", new Ability(this) }, }),
	weapons()
{ 
	connect(abilities["Constitution"], &Ability::modifierChanged, this, &Character::calcMaxStamina);
	connect(pcClass, &ClassInfo::levelChanged, this, &Character::calcMaxStamina);
	connect(pcClass, &ClassInfo::levelChanged, this, &Character::calcMaxHP);
}

Character::~Character()
{
	delete race;
	delete pcClass;
	delete stamina;
	delete hitpoints;

	qDeleteAll(abilities);

	qDeleteAll(weapons);
}

QString Character::getCharacterName() const
{
	return characterName;
}

Race* Character::getRace() const
{
	return race;
}

int Character::getClassLevel() const
{
	return pcClass->level();
}

int Character::getBAB() const
{
	return pcClass->getPropertyValue(ClassInfo::BAB);
}

int Character::getFortitude() const
{
	return pcClass->getPropertyValue(ClassInfo::Fortitude) + abilities["Constitution"]->modifier();
}

int Character::getReflex() const
{
	return pcClass->getPropertyValue(ClassInfo::Reflex) + abilities["Dexterity"]->modifier();
}

int Character::getWill() const
{
	return pcClass->getPropertyValue(ClassInfo::Will) + abilities["Wisdom"]->modifier();
}

Resource* Character::getStamina() const
{
	return stamina;
}

Resource* Character::getHP() const
{
	return hitpoints;
}

Ability* Character::getAbility(const QString abilityName) const
{
	if (abilities.contains(abilityName))
		return abilities.value(abilityName);
	return nullptr;
}

QVariant Character::getAbilityProperty(const QString abilityName, const QString propertyName) const
{
	if (abilities.contains(abilityName)) {
		if (!propertyName.compare("base"))
			return abilities[abilityName]->getBase();
		if (!propertyName.compare("upgrade"))
			return abilities[abilityName]->getUpgrade();
		if (!propertyName.compare("score"))
			return abilities[abilityName]->score();
		if (!propertyName.compare("modifier"))
			return abilities[abilityName]->modifier();
	}
	return QVariant();
}

void Character::setCharacterName(const QString name)
{
	characterName = name;
}

void Character::setRace(Race* race)
{
	this->race = race;
}

void Character::setClassLevel(int level)
{
	pcClass->setLevel(level);
}

void Character::setStamina(Resource* s)
{
	stamina = s;
}

void Character::setHP(Resource* hp)
{
	hitpoints = hp;
}

void Character::setAbility(const QString abilityName, Ability* a)
{
	if (abilities.contains(abilityName))
		abilities.insert(abilityName, a);
}

bool Character::setAbilityProperty(const QString abilityName, const QString propertyName, const QVariant& value)
{
	if (abilities.contains(abilityName)) {
		if (!propertyName.compare("base"))
			abilities[abilityName]->setBase(value.toInt());
		if (!propertyName.compare("upgrade"))
			abilities[abilityName]->setUpgrade(value.toInt());
		return true;
	}
	return false;
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
	switch (weapons[index]->type) {
	case Weapon::Type::Melee:
		weapons[index]->attackMod = getBAB() + abilities.value("Strength")->modifier();
		weapons[index]->damageMod = abilities.value("Strength")->modifier();
		break;
	case Weapon::Type::Ranged:
		weapons[index]->attackMod = getBAB() + abilities.value("Dexterity")->modifier();
		weapons[index]->damageMod = 0;
		break;
	}
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

	// Race
	if (json.contains("Race") && json.value("Race").isObject())
		race->read(json.value("Race").toObject());

	// Parse Ints
	if (json.contains("Class") && json.value("Class").isObject())
		pcClass->read(json.value("Class").toObject());

	// Parse Resources
	if (json.contains("Stamina") && json.value("Stamina").isObject())
		stamina->read(json.value("Stamina").toObject());
	if (json.contains("HitPoints") && json.value("HitPoints").isObject())
		hitpoints->read(json.value("HitPoints").toObject());

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
			weapons.append(w);
		}
	}
}

void Character::write(QJsonObject& json) const
{
	json.insert("CharacterName", characterName);
	json.insert("Race", race->toJsonObject());
	json.insert("Class", pcClass->toJsonObject());

	// Resources
	json.insert("Stamina", stamina->toJsonObject());
	json.insert("HitPoints", hitpoints->toJsonObject());

	// Abilities
	QJsonObject aObject;
	for (QHash<QString, Ability*>::ConstIterator i = abilities.cbegin(); i != abilities.cend(); ++i)
		aObject.insert(i.key(), i.value()->toJsonObject());
	json.insert("Abilities", aObject);
	
	// Weapons
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

void Character::calcMaxStamina()
{
	int newMax = pcClass->getPropertyValue(ClassInfo::Stamina) + (pcClass->level() * abilities["Constitution"]->modifier());
	stamina->setMax(newMax);
}

void Character::calcMaxHP()
{
	int newMax = pcClass->getPropertyValue(ClassInfo::HP) + race->hitPoints();
	hitpoints->setMax(newMax);
}