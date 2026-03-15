#ifndef ITEM_H
#define ITEM_H

#include <string>


//item.h deveria servir pra conseguir usar as variaveis e funcoes do item.cpp pra gerar itens no itemlist.cpp e itemlist.h


enum weaponType { sword = 1, polearm = 2, bow = 3 };
enum potionType { support = 1, aggressive = 2, mystery = 3 };
enum amount { small = 1, medium = 2, big = 3 };

class Item {

private:
    std::string name;
    float weight;
    int size;
    bool equipable;
    bool consumable;

public:
    Item(std::string name, float weight, int size, bool equipable, bool consumable);

    std::string getName();
    float getWeight();
    int getSize();
    bool isEquipable();
    bool isConsumable();
};

class Weapon : public Item {

private:
    int damage;
    int range;
    int type;

public:
    Weapon(std::string name, float weight, int size, bool equipable, bool consumable,
           int damage, int range, int type);

    int getDamage();
    int getRange();
    int getType();
};

class Potion : public Item {

private:
    int healing;
    int damage;
    int type;

public:
    Potion(std::string name, float weight, int size, bool equipable, bool consumable,
           int healing, int damage, int type);
};

#endif