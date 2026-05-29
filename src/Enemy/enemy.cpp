/**
 * @file enemy.cpp
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo define a classe Enemy, contendo os metodos e atributos
 * utilizados pelos inimigos do jogo Long Prep.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "enemy.h"

using namespace std;


//==================== CONSTRUTOR ====================//

// inicializa todos os atributos do inimigo
Enemy::Enemy(string name, int healthmax,int health,int defense,
             int range, float damage, float attackspeed,
             int difficulty, int xpvalue){

    this->name = name;
    this->healthmax = healthmax;
    this->health = health;
    this->defense = defense;
    this->range = range;
    this->damage = damage;
    this->attackspeed = attackspeed;
    this->difficulty = difficulty;
    this->xpvalue = xpvalue;
};


//==================== GETTERS ====================//
// retornam os atributos do inimigo

string Enemy::getName()const{
    return name;
};

int Enemy::getHealthMax()const{
    return healthmax;
};

int Enemy::getHealth()const{
    return health;
};

int Enemy::getDefense()const{
    return defense;
};

int Enemy::getRange()const{
    return range;
};

float Enemy::getDamage()const{
    return damage;
};

float Enemy::getAttackSpeed()const{
    return attackspeed;
}

// retorna o tempo acumulado desde o ultimo ataque
float Enemy::getAttackTimer()const{
    return attackTimer;
};

// retorna a dificuldade do inimigo
int Enemy::getDifficulty()const{
    return difficulty;
}

// retorna a quantidade de xp dada ao derrotar o inimigo
int Enemy::getxpvalue()const{
    return xpvalue;
}


//==================== SETTERS ====================//
// alteram os atributos do inimigo

void Enemy::setName(string nome){
    name = nome;
};

void Enemy::setHealthMax(int h){
    healthmax = h;
};

// altera a vida atual do inimigo
void Enemy::setHealth(int l) {

    // impede vida negativa
    if(l < 0)
        l = 0;

    // impede vida acima do maximo
    if(l > healthmax)
        return;

    health = l;
}

void Enemy::setDefense(int d){
    defense = d;
};

void Enemy::setRange(int r){
    range = r;
};

void Enemy::setDamage(float d){
    damage = d;
};

void Enemy::setAttackSpeed(float as){
    attackspeed = as;
};


//==================== SISTEMA DE ATAQUE ====================//

// incrementa o timer de ataque usando delta time
void Enemy::tickAttackTimer(float dt){
    attackTimer += dt;
}

// reseta o timer apos atacar
void Enemy::resetAttackTimer(){
    attackTimer = 0.0f;
}