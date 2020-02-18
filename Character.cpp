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
	weapons(),
	cModel(new ClassModel(this))
{
	connect(cModel, &ClassModel::dataChanged, [this](QModelIndex, QModelIndex, QVector<int> roles) {});
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
	delete cModel;
}

void Character::setProperty(int prop, const QVariant& value, int role)
{
	switch (prop) {
	case CharacterName: 
		characterName = value.toString();
		break;
	case BAB: 
		bab = value.toInt();
		break;
	case Fortitude: 
		fortitude = value.toInt();
		break;
	case Reflex: 
		reflex = value.toInt();
		break;
	case Will: 
		will = value.toInt();
		break;
	case Stamina: 
		if (value.canConvert<Resource*>())
			stamina = value.value<Resource*>();
		break;
	case Strength:
		if (value.canConvert<Ability*>())
			strength = value.value<Ability*>();
		break;
	case Dexterity:
		if (value.canConvert<Ability*>())
			dexterity = value.value<Ability*>();
		break;
	case Constitution:
		if (value.canConvert<Ability*>())
			constitution = value.value<Ability*>();
		break;
	case Intelligence:
		if (value.canConvert<Ability*>())
			intelligence = value.value<Ability*>();
		break;
	case Wisdom:
		if (value.canConvert<Ability*>())
			wisdom = value.value<Ability*>();
		break;
	case Charisma:
		if (value.canConvert<Ability*>())
			charisma = value.value<Ability*>();
		break;
	case Weapons:
		if (value.canConvert<QVector<Weapon*>>())
			weapons = value.value<QVector<Weapon*>>();
		break;
	}
}

QVariant Character::getProperty(int prop, int role) const
{
	switch (prop) {
	case CharacterName: return characterName;
	case BAB: return bab;
	case Fortitude: return fortitude;
	case Reflex: return reflex;
	case Will: return will;
	case Stamina: return QVariant::fromValue(stamina);
	case Strength: return QVariant::fromValue(strength);
	case Dexterity: return QVariant::fromValue(dexterity);
	case Constitution: return QVariant::fromValue(constitution);
	case Intelligence: return QVariant::fromValue(intelligence);
	case Wisdom: return QVariant::fromValue(wisdom);
	case Charisma: return QVariant::fromValue(charisma);
	case Weapons: return QVariant::fromValue(weapons);
	}
	return QVariant();
}

void Character::setClassLevelPair(QString name, int level)
{
	cModel->insertRow(0);
	cModel->setItemData(cModel->index(0), { 
		{ClassModel::Name,	name},
		{ClassModel::Level,	level} });
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
	cModel->read(json);
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
	cModel->write(json);
}

QJsonObject Character::toJsonObject() const
{
	QJsonObject json;
	write(json);
	return json;
}
