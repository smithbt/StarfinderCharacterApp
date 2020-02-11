#include "ClassModel.h"

ClassModel::ClassModel(QObject* parent)
	: QAbstractListModel(parent),
	m_classes(),
    referenceTable(),
    names()
{
    createReferenceTable();
}

ClassModel::~ClassModel()
{
}

void ClassModel::read(const QJsonObject& json)
{
    beginResetModel();
    if (json.contains("Classes") && json.value("Classes").isArray()) {
        QJsonArray cArray = json.value("Classes").toArray();
        m_classes.clear();
        for (int i = 0; i < cArray.size(); ++i) {
            QJsonObject cObj = cArray.at(i).toObject();
            ClassLevelPair clp;
            clp.read(cObj);
            m_classes.append(clp);
        }
    }
    endResetModel();
}

void ClassModel::write(QJsonObject& json) const
{
    QJsonArray cArray;
    for (ClassLevelPair clp : m_classes) {
        QJsonObject cObj;
        clp.write(cObj);
        cArray.append(cObj);
    }
    json.insert("Classes", cArray);
}

QVariant ClassModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) // invalid index
        return QVariant();

    const int row = index.row();
    if (row >= m_classes.size() || row < 0) // out of range
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_classes.at(row).toString();

    const ClassEntry refCE = referenceTable.at(names.indexOf(m_classes.at(row).name));
    const int level = m_classes.at(row).level;
    if (role >= Qt::UserRole)
        switch (role) {
        case Name: 
            return m_classes.at(row).name;
        case Level:
            return level;
        case Key_Ability: 
            return refCE.keyAbility;
        case BAB: 
            return calcLeveledValue(level, refCE.bab_rate);
        case Fortitude: 
            return calcSavingThrow(level, refCE.fort_isGood);
        case Reflex: 
            return calcSavingThrow(level, refCE.ref_isGood);
        case Will: 
            return calcSavingThrow(level, refCE.will_isGood);
        case Stamina: 
            return calcLeveledValue(level, refCE.stamina_rate);
        case HP: 
            return calcLeveledValue(level, refCE.hp_rate);
        case Skills: 
            return calcLeveledValue(level, refCE.skill_rate);
        }

    return QVariant();
}

Qt::ItemFlags ClassModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

int ClassModel::rowCount(const QModelIndex& parent) const
{
    return m_classes.size();
}

bool ClassModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid()) // invalid index
        return false;

    const int row = index.row();
    if (row >= m_classes.size() || row < 0) // out of range
        return false;

    if (role == Name) {
        ClassLevelPair clp = m_classes.at(row);
        if (value.toString() != clp.name) {
            clp.name = value.toString();
            emit dataChanged(index, index, { Name });
        }
        m_classes.replace(row, clp);
    }

    if (role == Level) {
        ClassLevelPair clp = m_classes.at(row);
        int newLevel = value.toInt();
        int oldLevel = clp.level;
        if (newLevel != oldLevel) {
            // update level
            clp.level = newLevel;
            ClassEntry ce = referenceTable.at(names.indexOf(clp.name));
            QVector<int> changedRoles({ Level, Stamina, HP, Skills });

            // check BAB
            if (calcLeveledValue(newLevel, ce.bab_rate) != calcLeveledValue(oldLevel, ce.bab_rate))
                changedRoles.append(BAB);

            // check Fortitude
            if (calcSavingThrow(newLevel, ce.fort_isGood) != calcSavingThrow(oldLevel, ce.fort_isGood))
                changedRoles.append(Fortitude);

            // check Reflex
            if (calcSavingThrow(newLevel, ce.ref_isGood) != calcSavingThrow(oldLevel, ce.ref_isGood))
                changedRoles.append(Reflex);

            // check Will
            if (calcSavingThrow(newLevel, ce.will_isGood) != calcSavingThrow(oldLevel, ce.will_isGood))
                changedRoles.append(Will);


            emit dataChanged(index, index, changedRoles);
        }
        m_classes.replace(row, clp);
    }

    return false;
}

bool ClassModel::insertRows(int position, int rows, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int i = (position); i < (position + rows); ++i) {
        m_classes.insert(i, ClassLevelPair());
    }

    endInsertRows();
    return true;
}

bool ClassModel::removeRows(int position, int rows, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int i = position; i < (position + rows); ++i) {
        m_classes.removeAt(i);
    }

    endRemoveRows();
    return true;
}

QStringList ClassModel::allClassNames() const
{
    return names;
}

int ClassModel::calcSavingThrow(int level, bool isGood) const
{
    return (isGood ? (2 + level / 2) : (level / 3));
}

int ClassModel::calcLeveledValue(int level, double rate) const
{
    return (level * rate);
}

bool ClassModel::createReferenceTable()
{
    QFile classFile(":/StarfinderCharacterApp/Resources/classes.csv");

    if (!classFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Could not open file.");
        return false;
    }
    QTextStream inStream(&classFile);
    // readLine to skip header
    inStream.readLine();

    // parse each remaining line into a ClassEntry
    QString line;
    while (inStream.readLineInto(&line)) {
        QStringList dataList = line.split(",");
        int idx = dataList.takeFirst().toInt();
        ClassEntry entry;
        entry.name = dataList.at(0);
        entry.keyAbility = Ability::scoreFromString(dataList.at(1));
        entry.bab_rate = dataList.at(2).toDouble();
        entry.fort_isGood = dataList.at(3).compare("FALSE", Qt::CaseInsensitive); // if value is FALSE, compare() returns 0.
        entry.ref_isGood = dataList.at(4).compare("FALSE", Qt::CaseInsensitive); // if value is FALSE, compare() returns 0.
        entry.will_isGood = dataList.at(5).compare("FALSE", Qt::CaseInsensitive); // if value is FALSE, compare() returns 0.
        entry.stamina_rate = dataList.at(6).toInt();
        entry.hp_rate = dataList.at(7).toInt();
        entry.skill_rate = dataList.at(8).toInt();
        referenceTable.insert(idx, entry);
        names.insert(idx, entry.name);
    }

    return true;
}
