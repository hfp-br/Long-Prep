/**
 * @file Entity.cpp
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br)
 * @brief Este arquivo preenche os atributos e metodos da classe Entity,
 * utilizada como classe base para jogadores e inimigos.
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "Entity.h"

using namespace std;

//==================== CONSTRUTOR ====================//

// inicializa todos os atributos da entidade
Entity::Entity(string name, int life, int lifeMax, int damage, int defense, float attackSpeed){
    this->name = name;
    this->life = life;
    this->lifeMax = lifeMax;
    this->damage = damage;
    this->defense = defense;
    this->attackSpeed = attackSpeed;
};


//==================== GETTERS ====================//

// retorna o nome da entidade
string Entity::getName() const {
    return name;
};

// retorna a vida atual
int Entity::getLife() const {
    return life;
};

// retorna a vida maxima
int Entity::getLifeMax() const {
    return lifeMax;
};

// retorna o dano atual
int Entity::getDamage() const {
    return damage;
};

// retorna a defesa atual
int Entity::getDefense() const {
    return defense;
};

// retorna a velocidade de ataque
float Entity::getAttackSpeed() const {
    return attackSpeed;
};

// retorna o timer acumulado de ataque
float Entity::getAttackTimer() const {
    return attackTimer;
};


//==================== SETTERS ====================//

// altera o nome da entidade
void Entity::setName(std::string n){
    name = n;
};

// altera a vida atual
void Entity::setLife(int l){
    life = l;
};

// altera a vida maxima
void Entity::setLifeMax(int l){
    lifeMax = l;
};

// altera o dano atual
void Entity::setDamage(int d){
    damage = d;
};

// altera a defesa atual
void Entity::setDefense(int d){
    defense = d;
};

// altera a velocidade de ataque
void Entity::setAttackSpeed(float s){
    attackSpeed = s;
};


//==================== SISTEMA DE ATAQUE ====================//

// acumula tempo no timer de ataque
void Entity::tickAttackTimer(float dt){
    attackTimer += dt;
};

// reseta o timer apos realizar um ataque
void Entity::resetAttackTimer(){
    attackTimer = 0.0f;
};