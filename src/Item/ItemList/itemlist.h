#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "Equipament.h"
#include "raylib.h"
#include "box2d/id.h"
#include "item.h"

void InitItemList();

struct physicalData {
    Texture2D texture;
    float width;
    float height;
    float radius;
    bool isCircle;
    float visualWidth;
    float visualHeight;
    itemCategory categoria;
    bool isClicked;
};

struct ItemData {
    RPG::Item* item;
};

struct ItemTemplate {
    ItemData* itemData;
    physicalData* itemPhysical;
};

struct physicalObject {
    ItemTemplate templateData;
    physicalData wallData;
    bool isWall;
    bool isGrabbed = false;
    bool isEquipped = false;
    bool wasEquipped = false;
    b2BodyId bodyId;
    b2ShapeId shapeId;
};

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
// acessórios
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