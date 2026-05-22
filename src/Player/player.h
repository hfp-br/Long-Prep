#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct atributes{
	int forca;
	int constituicao;
	int destreza;
	int inteligencia;
	int sorte;
};

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
        int xp=0;
        float current_weight=0;
        int xpfornextlevel=20;
        int unspentpoints=0;
        int spentpoints[5]={0};
        float baseAttackSpeed = 1.0f;

        public:
        Player(std::string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense,atributes atributos);
        
        std::string getName() const;
        int getLife()const;
        int getLife_max()const;
        int getDamage()const;
        float getWeight_Capacity()const;
        bool isBackpack()const;
        bool isAlive()const;
        int getDefense()const;
        float getAttackSpeed()const;
        float getAttackTimer()const;
        int getLevel()const;
        int getXp()const;
        float getCurrent_weight()const;
        int getAtributoconstituicao()const;
        int getAtributodestreza()const;
        int getAtributoforca()const;
        int getAtributointeligencia()const;
        int getAtributosorte()const;
        int getxpfornextlevel()const;
        int getunspentpoints()const;
        float getBaseAttackSpeed()const;

        
        void setName(std::string n);
        void setLife(int l);
        void setLife_Max(int l);
        void setDamage(int d);
        void setWeight_Capacity(float w);
        void setBackpack(bool b);
        void setAlive(bool a);
        void setDefense(int w);
        void setAttackSpeed(float s);
        void tickAttackTimer(float dt);
        void resetAttackTimer();
        void setlevel(int x);
        void setXp(int x);
        void setcurrent_weight(float x);
        void setAtributoconstituicao(int x);
        void setAtributodestreza(int x);
        void setAtributoforca(int x);
        void setAtributointeligencia(int x);
        void setAtributosorte(int x);
        void setxpfornextlevel(int x);
        void setunspentpoints(int x);
        void setBaseAttackSpeed(float s);


};

#endif