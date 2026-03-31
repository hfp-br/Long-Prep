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
    Category categoria;
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
    b2BodyId bodyId;
    b2ShapeId shapeId;
};

extern ItemTemplate espadacurta;
extern ItemTemplate cuboslime;
extern ItemTemplate pocaomisteriosa;

#endif