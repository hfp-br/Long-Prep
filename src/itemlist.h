#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "box2d/id.h"
#include "item.h"


//itemlist.h ia servir pra conseguir pegar a info dos itens e colocar junto com as infos fisicas do item, pra poder separar as duas na hora de criar o item dentro
//da engine fisica


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

#endif