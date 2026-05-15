#include <iostream>
#include <string>
#include <random>
#include <stdexcept>
using namespace std;

enum weaponType { sword = 1, polearm = 2, bow = 3 }; // enumeração para escolher o tipo de arma da classe weapon
enum potionType { support = 1, aggressive = 2, mystery = 3 }; // enumeração para escolher o tipo de poção da classe potion
enum amount { small = 1, medium = 2, big = 3 };

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

class Item : public IInteragivel {

    private:                // Aqui estão as variáveis privadas da classe Item que não devem ser acessadas por qualquer um

        string name;        // Esse é o nome do item
        float weight;       // Esse é o peso do item
        int size;           // Esse é o tamanho do item
        bool equipable;     // Esse é um booleano que indica se o item pode ser equipado ou não
        bool consumable;    // Esse é um booleano que indica se o item pode ser consumido ou não

    public:                 // Aqui estão as funções públicas da classe Item que podem ser acessadas por qualquer um

        // CORRIGIDO: construtor deve ter o mesmo nome da classe (Item, não CraftItem)
        Item(string name, float weight, int size, bool equipable, bool consumable) {
            this->name = name;
            this->weight = weight;
            this->size = size;
            this->equipable = equipable;
            this->consumable = consumable;
        }

        // Aqui eu deixei as funções relacionadas a pegar alguma informação do item

        string getName()    { return name; }        // função para pegar o nome do item
        float getWeight()   { return weight; }      // função para pegar o peso do item
        int getSize()       { return size; }        // função para pegar o tamanho do item
        bool isEquipable()  { return equipable; }   // função para saber se é equipável o item
        bool isConsumable() { return consumable; }  // função para saber se é consumível o item

        // Aqui eu deixei as funções relacionadas a atribuir algum valor para o item

        void setName(string n) {    // função para atribuir um nome para o item
            if (n.empty()) {
                throw invalid_argument("Peso nao pode ser negativo");
            }
            if (n.length() > 20) {
                throw invalid_argument("Ultrapassou o limite de 20 caracteres");
                return;
            }
            name = n;
        }

        void setWeight(float w) {   // função para atribuir um peso para o item
            if (w < 0) {
                cout << "Erro: Peso nao pode ser negativo" << endl;
                return;
            }
            weight = w;
        }

        void setSize(int s) {       // função para atribuir um tamanho para o item
            if (s < 0) {
                cout << "Erro: Tamanho nao pode ser negativo" << endl;
                return;
            }
            size = s;
        }

        void setEquipable(bool e) { // função para atribuir se o item é equipável ou não
            equipable = e;
        }

        void setConsumable(bool c) { // função para atribuir se o item é consumível ou não
            consumable = c;
        }

        virtual void interagir() = 0;

        virtual ~Item() {}

}; // classe do item

class Weapon final : public Item{

    private:
        int damage;
        int range;
        int type;

    public:
        // CORRIGIDO: construtor deve ter o mesmo nome da classe (Weapon, não CraftWeapon)
        // CORRIGIDO: inicialização da classe base deve usar o nome correto (Item, não CraftItem)
        Weapon(string name, float weight, int size, bool equipable, bool consumable, int damage, int range, int type)
            : Item(name, weight, size, equipable, consumable) {
            this->damage = damage;
            this->range = range;
            this->type = type;
        }

        int getDamage() { return damage; }  // função para pegar o dano da arma
        int getRange()  { return range; }   // função para pegar o alcance da arma
        int getType()   { return type; }    // função para pegar o tipo da arma

        void setDamage(int d) { // função para atribuir um dano para a arma
            if (d < 0) {
                cout << "Erro: Dano nao pode ser negativo" << endl;
                return;
            }
            damage = d;
        }

        void setRange(int r) { // função para atribuir um alcance para a arma
            if (r < 0) {
                cout << "Erro: O alcance nao pode ser negativo" << endl;
                return;
            }
            range = r;
        }

        void setType(int t) { // função para atribuir o tipo de arma usando Enum
            if (t != sword && t != polearm && t != bow) {
                cout << "Erro: O tipo de arma nao existe" << endl;
                return;
            }
            type = t;
        }

        
        void interagir() override {
            cout << "Atacando com arma\n";
        }

}; // classe das armas derivada do item

class Armor final : public Item {
private:
    int defense;

public:
    Armor(string name, float weight, int size, bool equipable, bool consumable, int defense)
        : Item(name, weight, size, equipable, consumable) {
        this->defense = defense;
    }


    int getDefense() const { return defense; }

    void setDefense(int d) { defense = d; }

    void interagir() override {
        cout << "Equipando armadura\n";
    }
};

class Ingredient final : public Item, public ICraftavel {
private:
    int type;

public:
    Ingredient(int type, string name, float weight, int size, bool equipable, bool consumable)
        : Item(name, weight, size, equipable, consumable) {
        this->type = type;
    }

    int getCraftType() const override {
        return type;
    }

    void interagir() override {
        cout << "Ingrediente usado no craft\n";
    }
};


class Potion: public Item {

    private:
        int type;    // variavel para definir o tipo de poção, usando um Enum

    public:
        // CORRIGIDO: construtor deve ter o mesmo nome da classe (Potion, não CraftPotion)
        // CORRIGIDO: inicialização da classe base deve usar o nome correto (Item, não CraftItem)
        Potion(string name, float weight, int size, bool equipable, bool consumable, int type)
            : Item(name, weight, size, equipable, consumable) {
            this->type = type;
        }

        virtual int EfeitoPocao()=0;

        void interagir()=0;

        
}; // classe das poções
    
class Potion_Damage final: public Potion {
    public:
        Potion_Damage(string name, float weight, int size)
        : Potion(name, weight, size, false, true, 0) {}

        int EfeitoPocao() override {
            return 0;
        }

        void interagir() override {};

    private:
};

class Potion_Health final: public Potion {
    public:
        Potion_Health(string name, float weight, int size)
        : Potion(name, weight, size, false, true, 1) {}

        int EfeitoPocao() override {
            return 1;
        }

        void interagir() override {};

    private:
};

class Potion_Speed final: public Potion {
    public:
        Potion_Speed(string name, float weight, int size)
        : Potion(name, weight, size, false, true, 2) {}

        int EfeitoPocao() override {
            return 2;
        }

        void interagir() override {};

    private:
};

class Potion_Luck final: public Potion {
    public:
        Potion_Luck(string name, float weight, int size)
        : Potion(name, weight, size, false, true, 3) {}

        int EfeitoPocao() override {
            return 3;
        }

        void interagir() override {};

    private:
};

class Potion_Mult final: public Potion {
    public:
        Potion_Mult(string name, float weight, int size)
        : Potion(name, weight, size, false, true, 4) {}

        int EfeitoPocao() override {
            return 4;
        }

        void interagir() override {};

    private:
};
