#include "player.h"

using namespace std;

Player::Player(std::string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense,atributes atributos){
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
        
		string Player::getName()const{ return name; }
        int Player::getLife()const{ return life; }
        int Player::getLife_max()const{ return life_max; }
        int Player::getDamage()const{ return damage; }
        float Player::getWeight_Capacity()const{ return weight_capacity; }
        bool Player::isBackpack()const{ return backpack; }
        bool Player::isAlive()const{ return alive; }
        int Player::getDefense()const{ return defense; }
        float Player::getAttackSpeed()const{ return attackSpeed; }
        float Player::getAttackTimer()const{ return attackTimer; }
        int Player::getLevel()const{return level;};
        int Player::getXp()const{return xp;};
        float Player::getCurrent_weight()const{return current_weight;};
        int Player::getAtributoconstituicao()const{return atributos.constituicao;};
        int Player::getAtributodestreza()const{return atributos.destreza;};
        int Player::getAtributoforca()const{return atributos.forca;};
        int Player::getAtributointeligencia()const{return atributos.inteligencia;};
        int Player::getAtributosorte()const{return atributos.sorte;};
        int Player::getxpfornextlevel()const{return xpfornextlevel;};
        int Player::getunspentpoints()const{return unspentpoints;};
        float Player::getBaseAttackSpeed() const{ return baseAttackSpeed; }

        
        void Player::setName(std::string n)     { name = n; }
        void Player::setLife(int l) {
                if(l < 0) l = 0;
                if(l > life_max) return;
                life = l;
            }
        void Player::setLife_Max(int l)         { life_max = l; }
        void Player::setDamage(int d)           { damage = d; }
        void Player::setWeight_Capacity(float w){ weight_capacity = w; }
        void Player::setBackpack(bool b)        { backpack = b; }
        void Player::setAlive(bool a)           { alive = a; }
        void Player::setDefense(int w)    { defense = w; }
        void Player::setAttackSpeed(float s) { 
            attackSpeed = (s > 0) ? s : 1.0f; 
        }
        void Player::tickAttackTimer(float dt)  { attackTimer += dt; }
        void Player::resetAttackTimer()         { attackTimer = 0.0f; }
        void Player::setlevel(int x){level=x;};
        void Player::setXp(int x){xp=x;};
        void Player::setcurrent_weight(float x){current_weight=x;};
        void Player::setAtributoconstituicao(int x){atributos.constituicao=x;};
        void Player::setAtributodestreza(int x){atributos.destreza=x;};
        void Player::setAtributoforca(int x){atributos.forca=x;};
        void Player::setAtributointeligencia(int x){atributos.inteligencia=x;};
        void Player::setAtributosorte(int x){atributos.sorte=x;};
        void Player::setxpfornextlevel(int x){xpfornextlevel=x;};
        void Player::setunspentpoints(int x){unspentpoints=x;};
        void Player::setBaseAttackSpeed(float s) { baseAttackSpeed = (s > 0) ? s : 1.0f; }