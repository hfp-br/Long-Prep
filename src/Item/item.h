#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

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

namespace RPG {
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
        Item(std::string name, float weight, int size, bool equipable, bool consumable, rarity raridade = common);

        std::string getName();
        float getWeight();
        int getSize();
        bool isEquipable();
        bool isConsumable();
        rarity getRarity();

        bool operator<(const Item& outro) const;

        friend std::ostream& operator<<(std::ostream& os, const Item& item);

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
            int damage, int range, int type, float attackspeed, rarity raridade = common);

        int getDamage();
        int getRange();
        int getType();
        float getAttackSpeed();

        virtual void interagir() override;
    };

    class Armor final : public Item {
    private:
        int defense;

    public:
        Armor(std::string name, float weight, int size, bool equipable, bool consumable,
            int defense, rarity raridade = common);

        int getDefense() const;
        virtual void interagir();
    };

    class Ingredient final : public Item, public ICraftavel{
        private:
            int type;
        
        public:
            Ingredient(int type,std::string name, float weight, int size, bool equipable, bool consumable);

        void interagir() override;

        void setType(int x);

        int getCraftType() const override;
    };


    class Potion: public Item {

        private:
            int type;

        public:
            Potion(std::string name, float weight, int size, bool equipable, bool consumable, int type);

            virtual int EfeitoPocao()=0;

            void interagir()=0;

            
    }; // classe das poções
        
    class Potion_Damage final: public Potion {
        public:
            Potion_Damage(std::string name, float weight, int size);

            int EfeitoPocao() override;

            void interagir() override;

        private:
    };

    class Potion_Health final: public Potion {
        public:
            Potion_Health(std::string name, float weight, int size);

            int EfeitoPocao() override;

            void interagir() override;

        private:
    };

    class Potion_Speed final: public Potion {
        public:
            Potion_Speed(std::string name, float weight, int size);

            int EfeitoPocao() override;

            void interagir() override;

        private:
    };

    class Potion_Luck final: public Potion {
        public:
            Potion_Luck(std::string name, float weight, int size);

            int EfeitoPocao() override;

            void interagir() override;

        private:
    };

    class Potion_Mult final: public Potion {
        public:
            Potion_Mult(std::string name, float weight, int size);

            int EfeitoPocao() override;

            void interagir() override;

        private:
    };
}
#endif