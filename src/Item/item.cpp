#include "item.h"
using namespace std;

namespace RPG{
    Item::Item(string name,float weight,int size,bool equipable,bool consumable,rarity raridade) {

        this->name       = name;
        this->weight     = weight;
        this->size       = size;
        this->equipable  = equipable;
        this->consumable = consumable;
        this->raridade   = raridade;
    }

    string Item::getName() {
        return name;
    }

    float Item::getWeight() {
        return weight;
    }

    int Item::getSize() {
        return size;
    }

    bool Item::isEquipable() {
        return equipable;
    }

    bool Item::isConsumable() {
        return consumable;
    }

    rarity Item::getRarity() {
        return raridade;
    }

    bool Item::operator<(const Item& outro) const {
        return raridade < outro.raridade;
    }

    ostream& operator<<(ostream& os, const Item& item) {
        os << item.name << " | Peso: " << item.weight << " | Raridade: " << item.raridade;
        return os;
    }



    Weapon::Weapon(std::string name, float weight, int size, bool equipable, bool consumable, int damage, int range, int type, float attackspeed, rarity raridade)
            : Item(name, weight, size, equipable, consumable, raridade){
            this->damage      = damage;
            this->range       = range;
            this->type        = type;
            this->attackSpeed = attackspeed;
        }

    int Weapon::getDamage()         { return damage; }
    int Weapon::getRange()          { return range; }
    int Weapon::getType()           { return type; }
    float Weapon::getAttackSpeed()  { return attackSpeed; }
    void Weapon::interagir()        {}



    Armor::Armor(std::string name, float weight, int size, bool equipable, bool consumable,
            int defense, rarity raridade)
            : Item(name, weight, size, equipable, consumable, raridade) {
            this->defense = defense;
        }

    int Armor::getDefense() const { return defense; }
    void Armor::interagir()       {}



    Ingredient::Ingredient(int type,std::string name, float weight, int size, bool equipable, bool consumable)
            : Item(name, weight, size, equipable, consumable) {
                this->type=type;
        }



    void Ingredient::interagir() {
            std::cout << "Invocando item\n";
        }

    void Ingredient::setType(int x){type=x;}

    int Ingredient::getCraftType() const {
            return type;
        }



    Potion::Potion(std::string name, float weight, int size, bool equipable, bool consumable, int type)
                : Item(name, weight, size, equipable, consumable) {
                this->type = type;
            }

            

    Potion_Damage::Potion_Damage(std::string name, float weight, int size)
            : Potion(name, weight, size, false, true, 0) {
            }

            int Potion_Damage::EfeitoPocao(){
                return 0;
            }

            void Potion_Damage::interagir(){};


    Potion_Health::Potion_Health(std::string name, float weight, int size)
            : Potion(name, weight, size, false, true, 1) {}

            int Potion_Health::EfeitoPocao() {
                return 1;
            }

            void Potion_Health::interagir() {};
    

    Potion_Speed::Potion_Speed(std::string name, float weight, int size)
            : Potion(name, weight, size, false, true, 2) {}

            int Potion_Speed::EfeitoPocao() {
                return 2;
            }

            void Potion_Speed::interagir() {};

    
    Potion_Luck::Potion_Luck(std::string name, float weight, int size)
            : Potion(name, weight, size, false, true, 3) {}

            int Potion_Luck::EfeitoPocao() {
                return 3;
            }

            void Potion_Luck::interagir() {};

        
    Potion_Mult::Potion_Mult(std::string name, float weight, int size)
            : Potion(name, weight, size, false, true, 4) {}

            int Potion_Mult::EfeitoPocao() {
                return 4;
            }

            void Potion_Mult::interagir() {};
}