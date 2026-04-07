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
    Item* item;
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

extern ItemTemplate espadacurta;
extern ItemTemplate espadalonga;
extern ItemTemplate arco;
extern ItemTemplate lança;
extern ItemTemplate cuboslime;
extern ItemTemplate coletecouro;
extern ItemTemplate capacete;
extern ItemTemplate botas;
extern ItemTemplate cintura;
extern ItemTemplate anel;
extern ItemTemplate amuleto;
extern ItemTemplate pocaomisteriosa;
extern ItemTemplate pocaocura;
extern ItemTemplate pocaodano;

#endif