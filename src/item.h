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

class IInteragivel {
public:
    virtual void interagir() = 0;
    virtual ~IInteragivel() = default;
};

class ICraftavel {
public:
    virtual int getCraftType() const = 0;
    virtual ~ICraftavel() = default;
};

class Item : public IInteragivel{
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

    virtual void interagir() = 0;
};

class Weapon final : public Item {
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

    virtual void interagir(){};
};

class Armor final : public Item {
private:
    int defense;

public:
    Armor(std::string name, float weight, int size, bool equipable, bool consumable,
          int defense, rarity raridade = common)
        : Item(name, weight, size, equipable, consumable, raridade) {
        this->defense = defense;
    }

    int getDefense() const { return defense; }
    virtual void interagir(){};
};

class Ingredient final : public Item, public ICraftavel{
    private:
        int type;
    
    public:
        Ingredient(int type,std::string name, float weight, int size, bool equipable, bool consumable)
        : Item(name, weight, size, equipable, consumable) {
            this->type=type;
    }

    void interagir() override {
        std::cout << "Invocando item\n";
    }

    void setType(int x){type=x;}

    int getCraftType() const override {
        return type;
    }
};


class Potion: public Item {

    private:
        int type;    // variavel para definir o tipo de poção, usando um Enum

    public:
        // CORRIGIDO: construtor deve ter o mesmo nome da classe (Potion, não CraftPotion)
        // CORRIGIDO: inicialização da classe base deve usar o nome correto (Item, não CraftItem)
        Potion(std::string name, float weight, int size, bool equipable, bool consumable, int type)
            : Item(name, weight, size, equipable, consumable) {
            this->type = type;
        }

        virtual int EfeitoPocao()=0;

        void interagir()=0;

        
}; // classe das poções
    
class Potion_Damage final: public Potion {
    public:
        Potion_Damage(std::string name, float weight, int size)
        : Potion(name, weight, size, false, true, 0) {}

        int EfeitoPocao() override {
            return 0;
        }

        void interagir() override {};

    private:
};

class Potion_Health final: public Potion {
    public:
        Potion_Health(std::string name, float weight, int size)
        : Potion(name, weight, size, false, true, 1) {}

        int EfeitoPocao() override {
            return 1;
        }

        void interagir() override {};

    private:
};

class Potion_Speed final: public Potion {
    public:
        Potion_Speed(std::string name, float weight, int size)
        : Potion(name, weight, size, false, true, 2) {}

        int EfeitoPocao() override {
            return 2;
        }

        void interagir() override {};

    private:
};

class Potion_Luck final: public Potion {
    public:
        Potion_Luck(std::string name, float weight, int size)
        : Potion(name, weight, size, false, true, 3) {}

        int EfeitoPocao() override {
            return 3;
        }

        void interagir() override {};

    private:
};

class Potion_Mult final: public Potion {
    public:
        Potion_Mult(std::string name, float weight, int size)
        : Potion(name, weight, size, false, true, 4) {}

        int EfeitoPocao() override {
            return 4;
        }

        void interagir() override {};

    private:
};


#endif