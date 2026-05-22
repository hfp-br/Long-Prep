#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include "raylib.h"

class Enemy final{
    private:
        std::string name;
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
        Enemy(std::string name, int healthmax,int health,int defense, int range, float damage, float attackspeed,int difficulty, int xpvalue);

        std::string getName()const;
        int getHealthMax()const;
        int getHealth()const;
        int getDefense()const;
        int getRange()const;
        float getDamage()const;
        float getAttackSpeed()const;
        float getAttackTimer()const;
        int getDifficulty()const;
        int getxpvalue()const;

        void setName(std::string nome);
        void setHealthMax(int h);
        void setHealth(int l);
        void setDefense(int d);
        void setRange(int r);
        void setDamage(float d);
        void setAttackSpeed(float as);
        void tickAttackTimer(float dt);
        void resetAttackTimer();

};

typedef struct {
    Enemy Inimigo;
    Texture2D texturaP;
    Texture2D texturaD;
    Texture2D texturaA;
    float scale;
    int offsetX;
    int offsetY;
} InimigoComp;

#endif