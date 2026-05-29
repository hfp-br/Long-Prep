/**
 * @file item.cpp
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo atribui as funcoes de todos os atributos e metodos dos itens do Long Prep. 
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "item.h"
using namespace std;

namespace RPG{

    //==================== ITEM BASE ====================//

    // construtor da classe base item
    Item::Item(string name,float weight,int size,bool equipable,bool consumable,rarity raridade) {

        // define os atributos principais do item
        this->name       = name;
        this->weight     = weight;
        this->size       = size;
        this->equipable  = equipable;
        this->consumable = consumable;
        this->raridade   = raridade;
    }

    // retorna o nome do item
    string Item::getName() {
        return name;
    }

    // retorna o peso do item
    float Item::getWeight() {
        return weight;
    }

    // retorna o tamanho ocupado pelo item
    int Item::getSize() {
        return size;
    }

    // verifica se o item pode ser equipado
    bool Item::isEquipable() {
        return equipable;
    }

    // verifica se o item pode ser consumido
    bool Item::isConsumable() {
        return consumable;
    }

    // retorna a raridade do item
    rarity Item::getRarity() {
        return raridade;
    }

    // compara dois itens pela raridade
    bool Item::operator<(const Item& outro) const {
        return raridade < outro.raridade;
    }

    // permite imprimir um item usando cout
    ostream& operator<<(ostream& os, const Item& item) {
        os << item.name << " | Peso: " << item.weight << " | Raridade: " << item.raridade;
        return os;
    }



    //==================== WEAPON ====================//

    // construtor da arma
    Weapon::Weapon(std::string name, float weight, int size, bool equipable, bool consumable, int damage, int range, int type, float attackspeed, rarity raridade)
            : Item(name, weight, size, equipable, consumable, raridade){

            // define os atributos especificos da arma
            this->damage      = damage;
            this->range       = range;
            this->type        = type;
            this->attackSpeed = attackspeed;
        }

    // retorna o dano da arma
    int Weapon::getDamage()         { return damage; }

    // retorna o alcance da arma
    int Weapon::getRange()          { return range; }

    // retorna o tipo da arma
    int Weapon::getType()           { return type; }

    // retorna a velocidade de ataque da arma
    float Weapon::getAttackSpeed()  { return attackSpeed; }

    // metodo polimorfico de interacao da arma
    void Weapon::interagir()        {}



    //==================== ARMOR ====================//

    // construtor da armadura
    Armor::Armor(std::string name, float weight, int size, bool equipable, bool consumable,
            int defense, rarity raridade)
            : Item(name, weight, size, equipable, consumable, raridade) {

            // define a defesa da armadura
            this->defense = defense;
        }

    // retorna a defesa da armadura
    int Armor::getDefense() const { return defense; }

    // metodo polimorfico de interacao da armadura
    void Armor::interagir()       {}



    //==================== INGREDIENT ====================//

    // construtor do ingrediente
    Ingredient::Ingredient(int type,std::string name, float weight, int size, bool equipable, bool consumable)
            : Item(name, weight, size, equipable, consumable) {

                // define o tipo de craft do ingrediente
                this->type=type;
        }

    // interacao do ingrediente
    void Ingredient::interagir() {
            std::cout << "Invocando item\n";
        }

    // altera o tipo de craft do ingrediente
    void Ingredient::setType(int x){type=x;}

    // retorna o tipo de craft do ingrediente
    int Ingredient::getCraftType() const {
            return type;
        }



    //==================== POTION BASE ====================//

    // construtor da pocao base
    Potion::Potion(std::string name, float weight, int size, bool equipable, bool consumable, int type)
                : Item(name, weight, size, equipable, consumable) {

                // define o tipo da pocao
                this->type = type;
            }



    //==================== POTION DAMAGE ====================//

    // construtor da pocao de dano
    Potion_Damage::Potion_Damage(std::string name, float weight, int size)
            : Potion(name, weight, size, false, true, 0) {
            }

            // retorna o codigo do efeito da pocao de dano
            int Potion_Damage::EfeitoPocao(){
                return 0;
            }

            // metodo polimorfico de interacao da pocao
            void Potion_Damage::interagir(){};



    //==================== POTION HEALTH ====================//

    // construtor da pocao de vida
    Potion_Health::Potion_Health(std::string name, float weight, int size)
            : Potion(name, weight, size, false, true, 1) {}

            // retorna o codigo do efeito da pocao de vida
            int Potion_Health::EfeitoPocao() {
                return 1;
            }

            // metodo polimorfico de interacao da pocao
            void Potion_Health::interagir() {};
    


    //==================== POTION SPEED ====================//

    // construtor da pocao de velocidade
    Potion_Speed::Potion_Speed(std::string name, float weight, int size)
            : Potion(name, weight, size, false, true, 2) {}

            // retorna o codigo do efeito da pocao de velocidade
            int Potion_Speed::EfeitoPocao() {
                return 2;
            }

            // metodo polimorfico de interacao da pocao
            void Potion_Speed::interagir() {};

    

    //==================== POTION LUCK ====================//

    // construtor da pocao de sorte
    Potion_Luck::Potion_Luck(std::string name, float weight, int size)
            : Potion(name, weight, size, false, true, 3) {}

            // retorna o codigo do efeito da pocao de sorte
            int Potion_Luck::EfeitoPocao() {
                return 3;
            }

            // metodo polimorfico de interacao da pocao
            void Potion_Luck::interagir() {};

        

    //==================== POTION MULT ====================//

    // construtor da pocao multiplicadora
    Potion_Mult::Potion_Mult(std::string name, float weight, int size)
            : Potion(name, weight, size, false, true, 4) {}

            // retorna o codigo do efeito da pocao multiplicadora
            int Potion_Mult::EfeitoPocao() {
                return 4;
            }

            // metodo polimorfico de interacao da pocao
            void Potion_Mult::interagir() {};
}