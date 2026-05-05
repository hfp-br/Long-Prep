#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <string>
using namespace std;

class Enemy final{
    private:
        string name;
        int healthmax;
        int health;
        int defense;
        int range;
        float damage;
        float attackspeed;
        float attackTimer = 0.0f;
        int difficulty;
        int xpvalue;
    
    public:
        Enemy(string name, int healthmax,int health,int defense, int range, int damage, float attackspeed,int difficulty, int xpvalue){
            this->name = name;
            this->healthmax = healthmax;
            this->health = health;
            this->defense = defense;
            this->range = range;
            this->damage = damage;
            this->attackspeed = attackspeed;
            this->difficulty=difficulty;
            this->xpvalue=xpvalue;
        };

        string getName(){return name;};
        int getHealthMax(){return healthmax;};
        int getHealth(){return health;};
        int getDefense(){return defense;};
        int getRange(){return range;};
        float getDamage(){return damage;};
        float getAttackSpeed(){ return attackspeed; }
        float getAttackTimer(){ return attackTimer; }
        int getDifficulty(){return difficulty;}
        int getxpvalue(){ return xpvalue; }

        void setName(string nome){name=nome;};
        void setHealthMax(int h){healthmax=h;};
        void setHealth(int l) {
                if(l < 0) l = 0;
                if(l > healthmax) return;
                health=l;
            }
        void setDefense(int d){defense=d;};
        void setRange(int r){range=r;};
        void setDamage(float d){damage=d;};
        void setAttackSpeed(float as){attackspeed=as;};
        void tickAttackTimer(float dt){ attackTimer += dt; }
        void resetAttackTimer(){ attackTimer = 0.0f; }

};

#endif