#include "enemy.h"
using namespace std;

Enemy::Enemy(string name, int healthmax,int health,int defense, int range, float damage, float attackspeed,int difficulty, int xpvalue){
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

        string Enemy::getName()const{return name;};
        int Enemy::getHealthMax()const{return healthmax;};
        int Enemy::getHealth()const{return health;};
        int Enemy::getDefense()const{return defense;};
        int Enemy::getRange()const{return range;};
        float Enemy::getDamage()const{return damage;};
        float Enemy::getAttackSpeed()const{ return attackspeed; }
        float Enemy::getAttackTimer()const{ return attackTimer; }
        int Enemy::getDifficulty()const{return difficulty;}
        int Enemy::getxpvalue()const{ return xpvalue; }

        void Enemy::setName(string nome){name=nome;};
        void Enemy::setHealthMax(int h){healthmax=h;};
        void Enemy::setHealth(int l) {
                if(l < 0) l = 0;
                if(l > healthmax) return;
                health=l;
            }
        void Enemy::setDefense(int d){defense=d;};
        void Enemy::setRange(int r){range=r;};
        void Enemy::setDamage(float d){damage=d;};
        void Enemy::setAttackSpeed(float as){attackspeed=as;};
        void Enemy::tickAttackTimer(float dt){ attackTimer += dt; }
        void Enemy::resetAttackTimer(){ attackTimer = 0.0f; }