#pragma once

#include <QAbstractListModel>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QVector>
#include "Ability.h"

class ClassModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum ClassRoles {
		Name = Qt::UserRole + 1, 
		Level,
		Key_Ability, 
		BAB, 
		Fortitude, 
		Reflex, 
		Will, 
		Stamina, 
		HP, 
		Skills
	};
	
	ClassModel(QObject *parent);
	~ClassModel();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

	QStringList allClassNames() const;

private:
	struct ClassLevelPair 
	{
		QString name;
		int level;

		void read(const QJsonObject& json)
		{
			if (json.contains("Class") && json.value("Class").isString())
				name = json.value("Class").toString();
			if (json.contains("Level") && json.value("Level").isDouble())
				level = json.value("Level").toInt();
		}

		void write(QJsonObject& json) const
		{
			json.insert("Class", name);
			json.insert("Level", level);
		}

		QString toString() const
		{
			return QString("%1 %2").arg(name).arg(level);
		}
	};

	QVector<ClassLevelPair> m_classes;
	int calcSavingThrow(int level, bool isGood) const;
	int calcLeveledValue(int level, double rate) const;
	
	bool createReferenceTable();

	struct ClassEntry {
		QString name;
		QString keyAbility;
		double bab_rate;
		bool fort_isGood;
		bool ref_isGood;
		bool will_isGood;
		int stamina_rate;
		int hp_rate;
		int skill_rate;
	};

	QVector<ClassEntry> referenceTable;
	QStringList names;
};