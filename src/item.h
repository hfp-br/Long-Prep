#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <random>

#define CAT_PAREDE        0x0001
#define CAT_ITEM          0x0002
#define CAT_ITEMSEGURADO  0x0004

enum weaponType { sword = 1, polearm = 2, bow = 3 };
enum potionType { support = 1, aggressive = 2, mystery = 3 };
enum amount { small = 1, medium = 2, big = 3 };
enum rarity { common, uncommon, rare, epic, legendary };

class Item {
private:
    std::string name;
    float weight;
    int size;
    bool equipable;
    bool consumable;
    rarity raridade;

public:
    virtual ~Item() = default;
    Item(std::string name, float weight, int size, bool equipable, bool consumable, rarity raridade = common) {
        this->name     = name;
        this->weight   = weight;
        this->size     = size;
        this->equipable  = equipable;
        this->consumable = consumable;
        this->raridade   = raridade;
    }

    std::string getName()    { return name; }
    float getWeight()        { return weight; }
    int getSize()            { return size; }
    bool isEquipable()       { return equipable; }
    bool isConsumable()      { return consumable; }
    rarity getRarity()       { return raridade; }
};

class Weapon : public Item {
private:
    int damage;
    int range;
    int type;
    float attackSpeed;

public:
    Weapon(std::string name, float weight, int size, bool equipable, bool consumable,
           int damage, int range, int type, float attackspeed, rarity raridade = common)
        : Item(name, weight, size, equipable, consumable, raridade) {
        this->damage      = damage;
        this->range       = range;
        this->type        = type;
        this->attackSpeed = attackspeed;
    }

    int getDamage()         { return damage; }
    int getRange()          { return range; }
    int getType()           { return type; }
    float getAttackSpeed()  { return attackSpeed; }
};

class Potion : public Item {
private:
    int healing;
    int damage;
    int type;

public:
    Potion(std::string name, float weight, int size, bool equipable, bool consumable,
           int healing, int damage, int type, rarity raridade = common)
        : Item(name, weight, size, equipable, consumable, raridade) {
        this->healing = healing;
        this->damage  = damage;
        this->type    = type;
    }

    int getHealing() { return healing; }
    int getDamage()  { return damage; }
    int getType()    { return type; }
};

class Armor : public Item {
private:
    int defense;

public:
    Armor(std::string name, float weight, int size, bool equipable, bool consumable,
          int defense, rarity raridade = common)
        : Item(name, weight, size, equipable, consumable, raridade) {
        this->defense = defense;
    }

    int getDefense() const { return defense; }
};

#endif