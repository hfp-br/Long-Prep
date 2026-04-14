
#ifndef EQUIPAMENT_H
#define EQUIPAMENT_H
#include "raylib.h"
#include "box2d/id.h"
#include "item.h"

enum itemCategory { head, chest, hand,handleft,handright, waist, feet, accessory };

struct physicalObject;

struct InventoryPivotPoint {
    int x;
    int y;
    bool isCircle;
    int width;
    int height;
    int radius;
    float strength;
    itemCategory category;
    b2BodyId equippedBodyId = b2_nullBodyId;
};

#endif