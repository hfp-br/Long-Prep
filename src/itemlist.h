#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "box2d/id.h"
#include "item.h"

struct physicalData {
    float width;
    float height;
    float radius;
    bool isCircle;
};

struct ItemData {
    Item* item;
};

struct ItemTemplate {
    ItemData* itemData;
    physicalData itemPhysical;
};

struct physicalObject {
    ItemTemplate templateData;
    b2BodyId bodyId;
};

extern ItemTemplate espadacurta;

#endif