#pragma once

#include <QIdentityProxyModel>
#include "CharacterModel.h"
#include "Weapon.h"

class WeaponProxyModel : public QIdentityProxyModel
{
	Q_OBJECT

public:
	enum {
		WeaponRole = Qt::UserRole + 1,
		AttackRole,
		DamageRole
	};

	WeaponProxyModel(QObject *parent);
	~WeaponProxyModel();

	void setCharacterModel(CharacterModel* cm);

	QVariant data(const QModelIndex& index, int role) const override;

	virtual QHash<int, QByteArray> roleNames() const override;

private:
	CharacterModel* cModel;
};
