#ifndef EQUIPAMENT_H
#define EQUIPAMENT_H
#include "raylib.h"
#include "box2d/id.h"
#include <string.h>

enum Category{head, chest, hand,waist, feet, accessory};

struct InventoryPivotPoint{
    int x;
    int y;
    bool isCircle;
    int width;
    int height;
    int radius;
    float strength;
    Category category;
};


#endif