#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

class Player {
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

        
        public:
        Player(std::string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense){
            this->name = name;
            this->life = life;
            this->life_max = life_max;
            this->damage = damage;
            this->weight_capacity = weight_capacity;
            this->backpack = backpack;
            this->alive = alive;
            this->defense = defense;
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
};

#endif