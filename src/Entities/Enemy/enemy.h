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

#include "raylib.h"
#include "../Entity.h"

//==================== CLASSE ENEMY ====================//

class Enemy : public Entity {
private:

    // alcance de ataque do inimigo
    int range;

    // dificuldade/tier do inimigo
    int difficulty;

    // xp dado ao derrotar o inimigo
    int xpvalue;

public:

    // cria um inimigo com todos os atributos definidos
    Enemy(std::string name, int healthmax, int health, int defense, int range, int damage, float attackspeed, int difficulty, int xpvalue);

    // retorna o alcance
    int getRange() const;

    // retorna a dificuldade do inimigo
    int getDifficulty() const;

    // retorna o xp dado ao derrotar o inimigo
    int getxpvalue() const;

    // altera o alcance
    void setRange(int r);
};


//==================== COMPONENTE DE INIMIGO ====================//

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