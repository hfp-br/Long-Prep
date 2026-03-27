#ifndef EQUIPAMENT_H
#define EQUIPAMENT_H
#include "raylib.h"
#include "box2d/id.h"

struct InventoryPivotPoint{
    int x;
    int y;
    bool isCircle;
    int width;
    int height;
    int radius;
    float strength;
};


#endif