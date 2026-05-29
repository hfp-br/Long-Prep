/**
 * @file itemlist.h
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo define a separacao de structs dos itens do Long Prep.
 * Como o projeto utiliza Raylib para renderizacao e Box2D para fisica,
 * foi decidido separar os dados fisicos, visuais e praticos dos itens.
 * 
 * Dados praticos: status, dano, vida, peso, categoria, etc.
 * Dados visuais: textura e tamanho desenhado na tela.
 * Dados fisicos: formato e corpo usado pela Box2D.
 *
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "Equipament.h"
#include "raylib.h"
#include "box2d/id.h"
#include "item.h"


//==================== FUNCOES ====================//

// carrega as texturas e inicializa os templates dos itens
void InitItemList();


//==================== DADOS FISICOS/VISUAIS ====================//

struct physicalData {

    // textura usada para desenhar o item
    Texture2D texture;

    // largura usada na fisica
    float width;

    // altura usada na fisica
    float height;

    // raio usado caso o item seja circular
    float radius;

    // define se o corpo fisico sera circulo ou retangulo
    bool isCircle;

    // largura visual usada na renderizacao
    float visualWidth;

    // altura visual usada na renderizacao
    float visualHeight;

    // categoria do item
    itemCategory categoria;

    // indica se o item foi clicado pelo mouse
    bool isClicked;
};


//==================== DADOS PRATICOS DO ITEM ====================//

struct ItemData {

    // ponteiro para o item real usado pelo sistema do RPG
    RPG::Item* item;
};


//==================== TEMPLATE DO ITEM ====================//

struct ItemTemplate {

    // dados praticos do item
    ItemData* itemData;

    // dados fisicos e visuais do item
    physicalData* itemPhysical;
};


//==================== OBJETO FISICO INSTANCIADO ====================//

struct physicalObject {

    // template usado para criar o item
    ItemTemplate templateData;

    // dados usados caso o objeto seja uma parede
    physicalData wallData;

    // define se o objeto e uma parede
    bool isWall;

    // indica se o objeto esta sendo segurado pelo mouse
    bool isGrabbed = false;

    // indica se o objeto esta equipado
    bool isEquipped = false;

    // guarda se o objeto estava equipado anteriormente
    bool wasEquipped = false;

    // identificador unico do item
    int itemId = -1;

    // id do corpo fisico na Box2D
    b2BodyId bodyId;

    // id da forma fisica na Box2D
    b2ShapeId shapeId;
};


//==================== TEMPLATES GLOBAIS DOS ITENS ====================//
// extern permite acessar os templates definidos no itemlist.cpp

// espadas
extern ItemTemplate espadacurta;
extern ItemTemplate espadacurtaUC;
extern ItemTemplate espadamedia;
extern ItemTemplate espadamediaEP;
extern ItemTemplate espadalonga;

// facas
extern ItemTemplate facapequena;
extern ItemTemplate facapequenaUC;
extern ItemTemplate facarara;
extern ItemTemplate facaEP;
extern ItemTemplate facalend;

// arcos
extern ItemTemplate arcopeq;
extern ItemTemplate arcopequUC;
extern ItemTemplate arcorar;
extern ItemTemplate arcoEP;
extern ItemTemplate arcolend;

// capacetes
extern ItemTemplate capacetecomum;
extern ItemTemplate capaceteUC;
extern ItemTemplate capaceterare;
extern ItemTemplate capaceteEP;
extern ItemTemplate capacetelegend;

// peitorais
extern ItemTemplate coletecomum;
extern ItemTemplate coleteUC;
extern ItemTemplate coterare;
extern ItemTemplate coteEP;
extern ItemTemplate cotelegend;

// cinturas
extern ItemTemplate cintocomum;
extern ItemTemplate cintoUC;
extern ItemTemplate cintorare;
extern ItemTemplate cintoEP;
extern ItemTemplate cintolend;

// botas
extern ItemTemplate botascomum;
extern ItemTemplate botasUC;
extern ItemTemplate botasrare;
extern ItemTemplate botasEP;
extern ItemTemplate botaslegend;

// acessorios
extern ItemTemplate anelocomum;
extern ItemTemplate aneloUC;
extern ItemTemplate anelorare;
extern ItemTemplate aneloEP;
extern ItemTemplate anelolend;

// ingredientes
extern ItemTemplate ingredientBase;
extern ItemTemplate ingredienteDano;
extern ItemTemplate ingredienteVida;
extern ItemTemplate ingredienteSpeed;
extern ItemTemplate ingredienteLuck;
extern ItemTemplate ingredienteMult;

// pocoes
extern ItemTemplate pocaoDano;
extern ItemTemplate pocaoVida;
extern ItemTemplate pocaoSpeed;
extern ItemTemplate pocaoLuck;
extern ItemTemplate pocaoMult;

#endif