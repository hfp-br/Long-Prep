/**
 * @file item.h
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo define todos os metodos e atributos dos itens do Long Prep.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

// categorias de colisao usadas pelo box2d
#define CAT_PAREDE        0x0001
#define CAT_ITEM          0x0002
#define CAT_ITEMSEGURADO  0x0004


//==================== ENUMS DOS ITENS ====================//

// tipos de arma disponiveis
enum weaponType { sword = 1, polearm = 2, bow = 3 };

// tipos gerais de pocao
enum potionType { support = 1, aggressive = 2, mystery = 3 };

// tamanhos/quantidades de itens
enum amount { small = 1, medium = 2, big = 3 };

// raridade dos itens
enum rarity { common, uncommon, rare, epic, legendary };


//==================== INTERFACES ====================//

// interface para objetos que podem ser usados/interagidos
class IInteragivel {
public:
    // metodo obrigatorio para interacao com o item
    virtual void interagir() = 0;

    // destrutor virtual para permitir polimorfismo seguro
    virtual ~IInteragivel() = default;
};


// interface para objetos que podem ser usados em craft
class ICraftavel {
public:
    // retorna o tipo de craft do objeto
    virtual int getCraftType() const = 0;

    // destrutor virtual para permitir polimorfismo seguro
    virtual ~ICraftavel() = default;
};


namespace RPG {

    //==================== ITEM BASE ====================//

    // classe abstrata base de todos os itens
    class Item : public IInteragivel{
    private:
        std::string name;
        float weight;
        int size;
        bool equipable;
        bool consumable;
        rarity raridade;

    public:
        // destrutor virtual para deletar itens derivados corretamente
        virtual ~Item() = default;

        // construtor principal do item
        Item(std::string name, float weight, int size, bool equipable, bool consumable, rarity raridade = common);

        // retorna o nome do item
        std::string getName();

        // retorna o peso do item
        float getWeight();

        // retorna o tamanho ocupado pelo item
        int getSize();

        // verifica se o item pode ser equipado
        bool isEquipable();

        // verifica se o item pode ser consumido
        bool isConsumable();

        // retorna a raridade do item
        rarity getRarity();

        // compara itens pela raridade
        bool operator<(const Item& outro) const;

        // permite imprimir o item usando cout
        friend std::ostream& operator<<(std::ostream& os, const Item& item);

        // metodo abstrato de interacao
        virtual void interagir() = 0;
    };


    //==================== WEAPON ====================//

    // classe final para armas
    class Weapon final : public Item {
    private:
        int damage;
        int range;
        int type;
        float attackSpeed;

    public:
        // construtor da arma
        Weapon(std::string name, float weight, int size, bool equipable, bool consumable,
            int damage, int range, int type, float attackspeed, rarity raridade = common);

        // retorna o dano da arma
        int getDamage();

        // retorna o alcance da arma
        int getRange();

        // retorna o tipo da arma
        int getType();

        // retorna a velocidade de ataque da arma
        float getAttackSpeed();

        // implementa a interacao da arma
        virtual void interagir() override;
    };


    //==================== ARMOR ====================//

    // classe final para armaduras
    class Armor final : public Item {
    private:
        int defense;

    public:
        // construtor da armadura
        Armor(std::string name, float weight, int size, bool equipable, bool consumable,
            int defense, rarity raridade = common);

        // retorna a defesa da armadura
        int getDefense() const;

        // implementa a interacao da armadura
        virtual void interagir();
    };


    //==================== INGREDIENT ====================//

    // classe final para ingredientes usados em craft
    class Ingredient final : public Item, public ICraftavel{
    private:
        int type;
        
    public:
        // construtor do ingrediente
        Ingredient(int type,std::string name, float weight, int size, bool equipable, bool consumable);

        // implementa a interacao do ingrediente
        void interagir() override;

        // altera o tipo de craft do ingrediente
        void setType(int x);

        // retorna o tipo de craft do ingrediente
        int getCraftType() const override;
    };


    //==================== POTION BASE ====================//

    // classe abstrata base para pocoes
    class Potion: public Item {
    private:
        int type;

    public:
        // construtor da pocao base
        Potion(std::string name, float weight, int size, bool equipable, bool consumable, int type);

        // retorna o codigo do efeito da pocao
        virtual int EfeitoPocao()=0;

        // metodo abstrato de interacao da pocao
        void interagir()=0;
    };


    //==================== POTION DAMAGE ====================//

    // pocao de dano
    class Potion_Damage final: public Potion {
    public:
        // construtor da pocao de dano
        Potion_Damage(std::string name, float weight, int size);

        // retorna o efeito da pocao
        int EfeitoPocao() override;

        // implementa a interacao da pocao
        void interagir() override;
    };


    //==================== POTION HEALTH ====================//

    // pocao de vida
    class Potion_Health final: public Potion {
    public:
        // construtor da pocao de vida
        Potion_Health(std::string name, float weight, int size);

        // retorna o efeito da pocao
        int EfeitoPocao() override;

        // implementa a interacao da pocao
        void interagir() override;
    };


    //==================== POTION SPEED ====================//

    // pocao de velocidade
    class Potion_Speed final: public Potion {
    public:
        // construtor da pocao de velocidade
        Potion_Speed(std::string name, float weight, int size);

        // retorna o efeito da pocao
        int EfeitoPocao() override;

        // implementa a interacao da pocao
        void interagir() override;
    };


    //==================== POTION LUCK ====================//

    // pocao de sorte
    class Potion_Luck final: public Potion {
    public:
        // construtor da pocao de sorte
        Potion_Luck(std::string name, float weight, int size);

        // retorna o efeito da pocao
        int EfeitoPocao() override;

        // implementa a interacao da pocao
        void interagir() override;
    };


    //==================== POTION MULT ====================//

    // pocao multiplicadora
    class Potion_Mult final: public Potion {
    public:
        // construtor da pocao multiplicadora
        Potion_Mult(std::string name, float weight, int size);

        // retorna o efeito da pocao
        int EfeitoPocao() override;

        // implementa a interacao da pocao
        void interagir() override;
    };
}

#endif