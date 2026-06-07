/**
 * @file enemylist.h
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo inicializa a funcao que carrega as texturas dos inimigos
 * e declara os componentes globais dos inimigos para serem utilizados em outros arquivos.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef ENEMYLIST_H
#define ENEMYLIST_H

#include "enemy.h"


//==================== FUNCOES ====================//

// carrega todas as texturas dos inimigos
void InitEnemyList();


//==================== COMPONENTES DOS INIMIGOS ====================//
// extern permite utilizar as variaveis globais definidas no enemylist.cpp

// inimigo comum
extern InimigoComp RegularComp;

// inimigo rapido
extern InimigoComp FastComp;

// inimigo tanque
extern InimigoComp TankComp;

// inimigo pesado
extern InimigoComp JuggernautComp;

// inimigo ranged
extern InimigoComp ArcherComp;

// inimigo furtivo/rapido
extern InimigoComp NinjaComp;

// inimigo gigante
extern InimigoComp ColossusComp;

// inimigo cavaleiro defensivo
extern InimigoComp KnightComp;

// inimigo focado em defesa
extern InimigoComp DefenderComp;

// boss final
extern InimigoComp DragonComp;

#endif