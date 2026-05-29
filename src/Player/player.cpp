/**
 * @file player.cpp
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo preenche as funcoes de todos os metodos e atributos do player.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "player.h"

using namespace std;


//==================== CONSTRUTOR ====================//

// cria o jogador com seus atributos iniciais
Player::Player(string name, int life, int life_max, int damage, float weight_capacity, bool backpack, bool alive, int defense,atributes atributos){

            // define os dados basicos do jogador
            this->name = name;
            this->life = life;
            this->life_max = life_max;
            this->damage = damage;
            this->weight_capacity = weight_capacity;
            this->backpack = backpack;
            this->alive = alive;
            this->defense = defense;

            // define os atributos principais do jogador
            this->atributos=atributos;
        }
        

//==================== GETTERS ====================//

// retorna o nome do jogador
string Player::getName()const{ return name; }

// retorna a vida atual
int Player::getLife()const{ return life; }

// retorna a vida maxima
int Player::getLife_max()const{ return life_max; }

// retorna o dano base
int Player::getDamage()const{ return damage; }

// retorna a capacidade maxima de peso
float Player::getWeight_Capacity()const{ return weight_capacity; }

// verifica se o jogador possui mochila
bool Player::isBackpack()const{ return backpack; }

// verifica se o jogador esta vivo
bool Player::isAlive()const{ return alive; }

// retorna a defesa do jogador
int Player::getDefense()const{ return defense; }

// retorna a velocidade de ataque atual
float Player::getAttackSpeed()const{ return attackSpeed; }

// retorna o tempo acumulado desde o ultimo ataque
float Player::getAttackTimer()const{ return attackTimer; }

// retorna o nivel atual
int Player::getLevel()const{return level;};

// retorna o xp atual
int Player::getXp()const{return xp;};

// retorna o peso atual carregado
float Player::getCurrent_weight()const{return current_weight;};

// retorna o atributo constituicao
int Player::getAtributoconstituicao()const{return atributos.constituicao;};

// retorna o atributo destreza
int Player::getAtributodestreza()const{return atributos.destreza;};

// retorna o atributo forca
int Player::getAtributoforca()const{return atributos.forca;};

// retorna o atributo inteligencia
int Player::getAtributointeligencia()const{return atributos.inteligencia;};

// retorna o atributo sorte
int Player::getAtributosorte()const{return atributos.sorte;};

// retorna a quantidade de xp necessaria para o proximo nivel
int Player::getxpfornextlevel()const{return xpfornextlevel;};

// retorna os pontos ainda nao gastos
int Player::getunspentpoints()const{return unspentpoints;};

// retorna a velocidade de ataque base
float Player::getBaseAttackSpeed() const{ return baseAttackSpeed; }

// retorna a classe do jogador
int Player::getClasse() const{ return classe; }


//==================== SETTERS ====================//

// altera o nome do jogador
void Player::setName(std::string n)     { name = n; }

// altera a vida atual do jogador
void Player::setLife(int l) {

        // impede que a vida fique negativa
        if(l < 0) l = 0;

        // impede que a vida ultrapasse a vida maxima
        if(l > life_max) return;

        life = l;
    }

// altera a vida maxima
void Player::setLife_Max(int l)         { life_max = l; }

// altera o dano base
void Player::setDamage(int d)           { damage = d; }

// altera a capacidade maxima de peso
void Player::setWeight_Capacity(float w){ weight_capacity = w; }

// define se o jogador possui mochila
void Player::setBackpack(bool b)        { backpack = b; }

// define se o jogador esta vivo
void Player::setAlive(bool a)           { alive = a; }

// altera a defesa do jogador
void Player::setDefense(int w)    { defense = w; }

// altera a velocidade de ataque atual
void Player::setAttackSpeed(float s) { 

    // impede velocidade de ataque invalida
    attackSpeed = (s > 0) ? s : 1.0f; 
}

// aumenta o timer de ataque com base no delta time
void Player::tickAttackTimer(float dt)  { attackTimer += dt; }

// reseta o timer de ataque apos atacar
void Player::resetAttackTimer()         { attackTimer = 0.0f; }

// altera o nivel do jogador
void Player::setlevel(int x){level=x;};

// altera o xp atual
void Player::setXp(int x){xp=x;};

// altera o peso atual carregado
void Player::setcurrent_weight(float x){current_weight=x;};

// altera o atributo constituicao
void Player::setAtributoconstituicao(int x){atributos.constituicao=x;};

// altera o atributo destreza
void Player::setAtributodestreza(int x){atributos.destreza=x;};

// altera o atributo forca
void Player::setAtributoforca(int x){atributos.forca=x;};

// altera o atributo inteligencia
void Player::setAtributointeligencia(int x){atributos.inteligencia=x;};

// altera o atributo sorte
void Player::setAtributosorte(int x){atributos.sorte=x;};

// altera o xp necessario para o proximo nivel
void Player::setxpfornextlevel(int x){xpfornextlevel=x;};

// altera os pontos ainda nao gastos
void Player::setunspentpoints(int x){unspentpoints=x;};

// altera a velocidade de ataque base
void Player::setBaseAttackSpeed(float s) { 

    // impede velocidade base invalida
    baseAttackSpeed = (s > 0) ? s : 1.0f; 
}

// altera a classe do jogador
void Player::setClasse(int x){classe = x;};