#include "itemlist.h"
#include "item.h"
#include "raylib.h"
#include <vector>
#include <cstdlib>

Weapon espadacurtaweapon("espada curta", 0.2, 3, true, false, 5, 5, 1);
ItemData espadacurtaData = {&espadacurtaweapon};
physicalData espadacurtaPhysical = {{0}, 30, 300, 0, false,80,300};
ItemTemplate espadacurta = {&espadacurtaData, &espadacurtaPhysical};

Item cuboslimeitem("cubo slime", 2,1,false,false);
ItemData cuboslimeData = {&cuboslimeitem};
physicalData cuboslimePhysical = {{0},30,30,0,false,30,30};
ItemTemplate cuboslime = {&cuboslimeData, &cuboslimePhysical};

Potion pocaoMisteriosaPotion("pocao misterio", 1, 2, false, true, 10, 0, 3);
ItemData pocaomisteriosaData = {&pocaoMisteriosaPotion};
physicalData pocaomisteriosaPhysical = {{0},0,0,15,true,35,45};
ItemTemplate pocaomisteriosa = {&pocaomisteriosaData, &pocaomisteriosaPhysical};


void InitItemList() {
    espadacurtaPhysical.texture = LoadTexture("images/Itens/short sword.png");
    SetTextureFilter(espadacurtaPhysical.texture, TEXTURE_FILTER_POINT);

    cuboslimePhysical.texture = LoadTexture("images/Itens/Slime Cube.png");
    SetTextureFilter(cuboslimePhysical.texture, TEXTURE_FILTER_POINT);

    pocaomisteriosaPhysical.texture = LoadTexture("images/Itens/Mistery Flask.png");
    SetTextureFilter(pocaomisteriosaPhysical.texture, TEXTURE_FILTER_POINT);
}