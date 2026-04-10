#include <iostream>
#include <string>
using namespace std;

class Enemy{
    private:
        string name;
        int healthmax;
        int health;
        int defense;
        int range;
        float damage;
        float attackspeed;
    
    public:
        Enemy(string name, int healthmax,int health,int defence, int range, int damage, int attackspeed){
            this->name;
            this->healthmax;
            this->defense;
            this->range;
            this->damage;
            this->attackspeed;
        };

        string getName(){return name;};
        int getHealthMax(){return healthmax;};
        int getHealth(){return health;};
        int getDefense(){return defense;};
        int getRange(){return range;};
        float getDamage(){return damage;};
        float getAttackSpeed(){return attackspeed;};

        string setName(string nome){name=nome;};
        int setHealthMax(int h){healthmax=h;};
        int setHeath(int h){health=h;};
        int setDefense(int d){defense=d;};
        int setRange(int r){range=r;};
        float setDamage(float d){damage=d;};
        float setAttackSpeed(float as){attackspeed=as;};
};