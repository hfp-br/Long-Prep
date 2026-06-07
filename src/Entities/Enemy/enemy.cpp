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
Enemy::Enemy(std::string name,
             int healthmax,
             int health,
             int defense,
             int range,
             int damage,
             float attackspeed,
             int difficulty,
             int xpvalue)
    : Entity(name, health, healthmax, damage, defense, attackspeed)
{
    this->range = range;
    this->difficulty = difficulty;
    this->xpvalue = xpvalue;
}


//==================== GETTERS ====================//
// retornam os atributos do inimigo

int Enemy::getRange()const{
    return range;
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

void Enemy::setRange(int r){
    range = r;
};