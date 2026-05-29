/**
 * @file Equipament.h
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo define os pivot points do inventario/equipamentos do jogador.
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef EQUIPAMENT_H
#define EQUIPAMENT_H

#include "box2d/id.h"


//==================== CATEGORIAS DE ITEM ====================//
// define em qual slot um item pode ser equipado

enum itemCategory {

    // capacete/chapeu
    head,

    // armadura principal
    chest,

    // item de mao generico
    hand,

    // mao esquerda
    handleft,

    // mao direita
    handright,

    // cintura/cinto
    waist,

    // botas/calcados
    feet,

    // aneis, colares e itens especiais
    accessory
};


// declaracao antecipada da struct physicalObject
struct physicalObject;


//==================== SLOT DE EQUIPAMENTO ====================//
// representa um ponto do inventario onde um item pode ser equipado

struct InventoryPivotPoint {

    // posicao x do pivot na tela
    int x;

    // posicao y do pivot na tela
    int y;

    // define se o slot possui formato circular
    bool isCircle;

    // largura da area do slot
    int width;

    // altura da area do slot
    int height;

    // raio caso o slot seja circular
    int radius;

    // intensidade da forca usada para atrair itens
    float strength;

    // categoria de item aceita no slot
    itemCategory category;

    // body do item equipado atualmente
    b2BodyId equippedBodyId = b2_nullBodyId;
};

#endif