/**
 * @file enemy.h
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo define os atributos e metodos da classe Enemy,
 * utilizada para representar os inimigos do jogo Long Prep.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "raylib.h"


//==================== CLASSE ENEMY ====================//

class Enemy final{

    private:

        // nome do inimigo
        std::string name;

        // vida maxima do inimigo
        int healthmax;

        // vida atual do inimigo
        int health;

        // valor de defesa usado na reducao de dano
        int defense;

        // alcance de ataque do inimigo
        int range;

        // dano causado por ataque
        float damage;

        // velocidade entre ataques
        float attackspeed;

        // contador de tempo para controlar cooldown de ataque
        float attackTimer = 0.0f;

        // dificuldade/tier do inimigo
        int difficulty;

        // xp dado ao derrotar o inimigo
        int xpvalue;
    
    public:

        //==================== CONSTRUTOR ====================//

        // cria um inimigo com todos os atributos definidos
        Enemy(std::string name,
              int healthmax,
              int health,
              int defense,
              int range,
              float damage,
              float attackspeed,
              int difficulty,
              int xpvalue);


        //==================== GETTERS ====================//

        // retorna o nome do inimigo
        std::string getName()const;

        // retorna a vida maxima
        int getHealthMax()const;

        // retorna a vida atual
        int getHealth()const;

        // retorna a defesa
        int getDefense()const;

        // retorna o alcance
        int getRange()const;

        // retorna o dano
        float getDamage()const;

        // retorna a velocidade de ataque
        float getAttackSpeed()const;

        // retorna o timer de ataque
        float getAttackTimer()const;

        // retorna a dificuldade do inimigo
        int getDifficulty()const;

        // retorna o xp dado ao derrotar o inimigo
        int getxpvalue()const;


        //==================== SETTERS ====================//

        // altera o nome
        void setName(std::string nome);

        // altera a vida maxima
        void setHealthMax(int h);

        // altera a vida atual
        void setHealth(int l);

        // altera a defesa
        void setDefense(int d);

        // altera o alcance
        void setRange(int r);

        // altera o dano
        void setDamage(float d);

        // altera a velocidade de ataque
        void setAttackSpeed(float as);


        //==================== SISTEMA DE ATAQUE ====================//

        // incrementa o timer de ataque usando delta time
        void tickAttackTimer(float dt);

        // reseta o timer apos um ataque
        void resetAttackTimer();

};


//==================== COMPONENTE DE INIMIGO ====================//
// estrutura usada para juntar o inimigo com suas texturas

typedef struct {

    // dados do inimigo
    Enemy Inimigo;

    // textura padrao/parado
    Texture2D texturaP;

    // textura tomando dano
    Texture2D texturaD;

    // textura atacando
    Texture2D texturaA;

    // escala usada para desenhar o inimigo
    float scale;

    // offset horizontal da sprite
    int offsetX;

    // offset vertical da sprite
    int offsetY;

} InimigoComp;

#endif