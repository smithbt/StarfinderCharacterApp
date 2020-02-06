#pragma once

#include <QIdentityProxyModel>
#include "AbilityModel.h"
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

	void setBAB(int b);
	void setAbilityModel(AbilityModel* am);

	QVariant data(const QModelIndex& index, int role) const override;

	virtual QHash<int, QByteArray> roleNames() const override;

private:
	int bab;
	AbilityModel* aModel;
};
