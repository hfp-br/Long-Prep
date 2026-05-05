#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

typedef struct{
	int forca;
	int constituicao;
	int destreza;
	int inteligencia;
	int sorte;
} atributes;

class Player final{
    private:
        std::string name;
        int life;
        int life_max;
        int damage;
        float weight_capacity;
        bool backpack;
        bool alive;
        int defense;
        float attackSpeed = 1.0f;
        float attackTimer = 0.0f;
        atributes atributos;
        int level=1;
        int xp;
        float current_weight;
        int xpfornextlevel=20;
        int unspentpoints;
        int spentpoints[5];
        float baseAttackSpeed = 1.0f;

        public:
        Player(std::string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense,atributes atributos){
            this->name = name;
            this->life = life;
            this->life_max = life_max;
            this->damage = damage;
            this->weight_capacity = weight_capacity;
            this->backpack = backpack;
            this->alive = alive;
            this->defense = defense;
            this->atributos=atributos;
        }
        
        std::string getName()           { return name; }
        int getLife()                   { return life; }
        int getLife_max()               { return life_max; }
        int getDamage()                 { return damage; }
        float getWeight_Capacity()      { return weight_capacity; }
        bool isBackpack()               { return backpack; }
        bool isAlive()                  { return alive; }
        int getDefense()           { return defense; }
        float getAttackSpeed()          { return attackSpeed; }
        float getAttackTimer()          { return attackTimer; }
        int getLevel(){return level;};
        int getXp(){return xp;};
        float getCurrent_weight(){return current_weight;};
        int getAtributoconstituicao(){return atributos.constituicao;};
        int getAtributodestreza(){return atributos.destreza;};
        int getAtributoforca(){return atributos.forca;};
        int getAtributointeligencia(){return atributos.inteligencia;};
        int getAtributosorte(){return atributos.sorte;};
        int getxpfornextlevel(){return xpfornextlevel;};
        int getunspentpoints(){return unspentpoints;};
        float getBaseAttackSpeed() { return baseAttackSpeed; }

        
        void setName(std::string n)     { name = n; }
        void setLife(int l) {
                if(l < 0) l = 0;
                if(l > life_max) return;
                life = l;
            }
        void setLife_Max(int l)         { life_max = l; }
        void setDamage(int d)           { damage = d; }
        void setWeight_Capacity(float w){ weight_capacity = w; }
        void setBackpack(bool b)        { backpack = b; }
        void setAlive(bool a)           { alive = a; }
        void setDefense(int w)    { defense = w; }
        void setAttackSpeed(float s) { 
            attackSpeed = (s > 0) ? s : 1.0f; 
        }
        void tickAttackTimer(float dt)  { attackTimer += dt; }
        void resetAttackTimer()         { attackTimer = 0.0f; }
        void setlevel(int x){level=x;};
        void setXp(int x){xp=x;};
        void setcurrent_weight(float x){current_weight=x;};
        void setAtributoconstituicao(int x){atributos.constituicao=x;};
        void setAtributodestreza(int x){atributos.destreza=x;};
        void setAtributoforca(int x){atributos.forca=x;};
        void setAtributointeligencia(int x){atributos.inteligencia=x;};
        void setAtributosorte(int x){atributos.sorte=x;};
        void setxpfornextlevel(int x){xpfornextlevel=x;};
        void setunspentpoints(int x){unspentpoints=x;};
        void setBaseAttackSpeed(float s) { baseAttackSpeed = (s > 0) ? s : 1.0f; }


};

#endif