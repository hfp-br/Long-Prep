/**
 * @file Entity.h
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo define os atributos e metodos da classe Entity,
 * utilizada como classe base para jogadores e inimigos.
 * @version 0.1
 * @date 2026-05-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>

//==================== ENTITY ====================//

// classe base para todas as entidades vivas do jogo
class Entity {
private:

    // nome da entidade
    std::string name;

    // vida atual
    int life;

    // vida maxima
    int lifeMax;

    // dano base
    int damage;

    // defesa base
    int defense;

    // velocidade entre ataques
    float attackSpeed = 1.0f;

    // tempo acumulado desde o ultimo ataque
    float attackTimer = 0.0f;

public:

    // cria uma entidade com todos os atributos definidos
    Entity(std::string name,
           int life,
           int lifeMax,
           int damage,
           int defense,
           float attackSpeed);

    // destrutor virtual para permitir heranca
    virtual ~Entity() = default;


    //==================== GETTERS ====================//

    // retorna o nome da entidade
    std::string getName() const;

    // retorna a vida atual
    int getLife() const;

    // retorna a vida maxima
    int getLifeMax() const;

    // retorna o dano base
    int getDamage() const;

    // retorna a defesa base
    int getDefense() const;

    // retorna a velocidade de ataque
    float getAttackSpeed() const;

    // retorna o timer de ataque
    float getAttackTimer() const;


    //==================== SETTERS ====================//

    // altera o nome da entidade
    void setName(std::string n);

    // altera a vida atual
    void setLife(int l);

    // altera a vida maxima
    void setLifeMax(int l);

    // altera o dano base
    void setDamage(int d);

    // altera a defesa base
    void setDefense(int d);

    // altera a velocidade de ataque
    void setAttackSpeed(float s);


    //==================== SISTEMA DE ATAQUE ====================//

    // acumula tempo no timer de ataque
    void tickAttackTimer(float dt);

    // reseta o timer de ataque
    void resetAttackTimer();
};

#endif