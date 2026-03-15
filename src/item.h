#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <random>

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
    Item(std::string name, float weight, int size, bool equipable, bool consumable) {
        this->name = name;
        this->weight = weight;
        this->size = size;
        this->equipable = equipable;
        this->consumable = consumable;
    }

    std::string getName() { return name; }
    float getWeight() { return weight; }
    int getSize() { return size; }
    bool isEquipable() { return equipable; }
    bool isConsumable() { return consumable; }
};

class Weapon : public Item {
private:
    int damage;
    int range;
    int type;

public:
    Weapon(std::string name, float weight, int size, bool equipable, bool consumable,
           int damage, int range, int type)
        : Item(name, weight, size, equipable, consumable) {
        this->damage = damage;
        this->range = range;
        this->type = type;
    }

    int getDamage() { return damage; }
    int getRange() { return range; }
    int getType() { return type; }
};

class Potion : public Item {
private:
    int healing;
    int damage;
    int type;

public:
    Potion(std::string name, float weight, int size, bool equipable, bool consumable,
           int healing, int damage, int type)
        : Item(name, weight, size, equipable, consumable) {
        this->healing = healing;
        this->damage = damage;
        this->type = type;
    }
};

#endif