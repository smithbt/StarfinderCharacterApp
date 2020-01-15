#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QMetaType>
#include <QVariant>
#include <QVector>
#include <QPair>
#include "Ability.h"
#include "Weapon.h"

class CharacterNode
{
    Q_GADGET
public:
    enum class Type {
        Name,
        List,
        Ability,
        Weapon
    };
    Q_ENUM(Type)

    CharacterNode(const QPair<Type, QVariant>& data, CharacterNode* parentItem = nullptr);
    ~CharacterNode();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    void appendChild(CharacterNode* child);

    CharacterNode* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    bool insertChildren(int position, int count);
    CharacterNode* parentNode();
    bool removeChildren(int position, int count);
    bool setData(int column, const QVariant& value);


private:
    QVector<CharacterNode*> children;
    QPair<Type, QVariant> itemData;
    CharacterNode* parent;

};
