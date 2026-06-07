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
#include <memory>

using namespace std;

//==================== CONSTRUTOR ====================//

Player::Player(string name, int life, int life_max, int damage,
               float weight_capacity, bool backpack, bool alive,
               int defense, atributes atributos)
    : Entity(name, life, life_max, damage, defense, 1.0f)
{
    this->weight_capacity = weight_capacity;
    this->backpack = backpack;
    this->alive = alive;
    this->atributos = atributos;
}

//==================== GETTERS ====================//

float Player::getWeight_Capacity() const{ return weight_capacity; }

bool Player::isBackpack() const{ return backpack; }

bool Player::isAlive() const{ return alive; }

int Player::getLevel() const{ return level; }

int Player::getXp() const{ return xp; }

float Player::getCurrent_weight() const{ return current_weight; }

int Player::getAtributoconstituicao() const{ return atributos.constituicao; }

int Player::getAtributodestreza() const{ return atributos.destreza; }

int Player::getAtributoforca() const{ return atributos.forca; }

int Player::getAtributointeligencia() const{ return atributos.inteligencia; }

int Player::getAtributosorte() const{ return atributos.sorte; }

int Player::getxpfornextlevel() const{ return xpfornextlevel; }

int Player::getunspentpoints() const{ return unspentpoints; }

float Player::getBaseAttackSpeed() const{ return baseAttackSpeed; }

int Player::getContadorSkill() const { return contadorSkill; }

//==================== SETTERS ====================//

void Player::setWeight_Capacity(float w){ weight_capacity = w; }

void Player::setBackpack(bool b){ backpack = b; }

void Player::setAlive(bool a){ alive = a; }

void Player::setlevel(int x){ level = x; }

void Player::setXp(int x){ xp = x; }

void Player::setcurrent_weight(float x){ current_weight = x; }

void Player::setAtributoconstituicao(int x){ atributos.constituicao = x; }

void Player::setAtributodestreza(int x){ atributos.destreza = x; }

void Player::setAtributoforca(int x){ atributos.forca = x; }

void Player::setAtributointeligencia(int x){ atributos.inteligencia = x; }

void Player::setAtributosorte(int x){ atributos.sorte = x; }

void Player::setxpfornextlevel(int x){ xpfornextlevel = x; }

void Player::setunspentpoints(int x){ unspentpoints = x; }

void Player::setContadorSkill(int c){ contadorSkill = c; }

void Player::setBaseAttackSpeed(float s){
    baseAttackSpeed = (s > 0) ? s : 1.0f;
}

void Guerreiro:: usarHabilidade(){
    setDamage(getDamage()+getLevel()/2);
}

void Guerreiro::desfazerHabilidade(){
    setDamage(getDamage() - getLevel()/2);
}

void Mago:: usarHabilidade(){
    setAtributosorte(getAtributosorte()+getAtributointeligencia());
}

void Mago::desfazerHabilidade(){
    setAtributosorte(getAtributosorte()-getAtributointeligencia());
}

void Curandeiro :: usarHabilidade(){
    setLife(getLifeMax()*(getAtributoconstituicao()/10));
}

void Curandeiro::desfazerHabilidade(){
}

void Ladrao :: usarHabilidade(){
    setAttackSpeed(getAttackSpeed()/1.5);
}

void Ladrao::desfazerHabilidade(){
    setAttackSpeed(getAttackSpeed()*1.5);
}

std::unique_ptr<Player> PlayerFactory::criarPlayer(int classeEscolhida)
{
    if(classeEscolhida == 1){
        atributes atributos{3, 0, 0, 1, 5};
        return std::make_unique<Guerreiro>("hero", 100, 100, 5, 10.0f, true, true, 0, atributos);
    }

    if(classeEscolhida == 2){
        atributes atributos{0, 0, 0, 4, 5};
        return std::make_unique<Mago>("hero", 100, 100, 5, 10.0f, true, true, 0, atributos);
    }

    if(classeEscolhida == 3){
        atributes atributos{0, 5, 0, 1, 5};
        return std::make_unique<Curandeiro>("hero", 100, 100, 5, 10.0f, true, true, 0, atributos);
    }

    if(classeEscolhida == 4){
        atributes atributos{0, 0, 3, 1, 5};
        return std::make_unique<Ladrao>("hero", 100, 100, 5, 10.0f, true, true, 0, atributos);
    }

    return nullptr;
}