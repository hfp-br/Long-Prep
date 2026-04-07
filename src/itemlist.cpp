#include "itemlist.h"
#include "Equipament.h"
#include "item.h"
#include "raylib.h"
#include <vector>
#include <cstdlib>

Weapon espadacurtaweapon("espada curta", 0.2, 3, true, false, 5, 5, 1);
ItemData espadacurtaData = {&espadacurtaweapon};
physicalData espadacurtaPhysical = {{0}, 30, 300, 0, false,80,300,hand};
ItemTemplate espadacurta = {&espadacurtaData, &espadacurtaPhysical};

Item cuboslimeitem("cubo slime", 2,1,false,false);
ItemData cuboslimeData = {&cuboslimeitem};
physicalData cuboslimePhysical = {{0},30,30,0,false,30,30};
ItemTemplate cuboslime = {&cuboslimeData, &cuboslimePhysical};

Potion pocaoMisteriosaPotion("pocao misterio", 1, 2, false, true, 10, 0, 3);
ItemData pocaomisteriosaData = {&pocaoMisteriosaPotion};
physicalData pocaomisteriosaPhysical = {{0},0,0,15,true,35,45,accessory};
ItemTemplate pocaomisteriosa = {&pocaomisteriosaData, &pocaomisteriosaPhysical};

Armor coletecouroArmor("colete de couro",0.5,3,true,false,5);
ItemData coletecouroData = {&coletecouroArmor};
physicalData coletecouroPhyisical = {{0},110,165,0,false,125,190,chest};
ItemTemplate coletecouro = {&coletecouroData,&coletecouroPhyisical};

Weapon espadalongatweapon("espada longa", 0.1, 5, true, false, 12, 8, 1);
ItemData espadalongatData = {&espadalongatweapon};
physicalData espadalongaPhysical = {{0}, 30, 380, 0, false, 80, 400, hand};
ItemTemplate espadalonga = {&espadalongatData, &espadalongaPhysical};

Weapon arcoweapon("arco", 0.5, 4, true, false, 8, 20, 3);
ItemData arcoData = {&arcoweapon};
physicalData arcoPhysical = {{0}, 20, 120, 0, false, 100, 300, hand};
ItemTemplate arco = {&arcoData, &arcoPhysical};

Weapon lançaweapon("lança", 0.4, 6, true, false, 10, 15, 2);
ItemData lançaData = {&lançaweapon};
physicalData lançaPhysical = {{0}, 10, 225, 0, false, 30, 450, hand};
ItemTemplate lança = {&lançaData, &lançaPhysical};

Armor capaceteArmor("capacete de ferro", 0.2, 2, true, false, 7);
ItemData capaceteData = {&capaceteArmor};
physicalData capacetePhysical = {{0}, 80, 80, 0, false, 90, 120, head};
ItemTemplate capacete = {&capaceteData, &capacetePhysical};

Armor botasArmor("botas de couro", 0.5, 2, true, false, 2);
ItemData botasData = {&botasArmor};
physicalData botasPhysical = {{0}, 80, 60, 0, false, 90, 70, feet};
ItemTemplate botas = {&botasData, &botasPhysical};

Armor cinturaArmor("cinto de ferro", 0.4, 2, true, false, 3);
ItemData cinturaData = {&cinturaArmor};
physicalData cinturaPhysical = {{0}, 100, 30, 0, false, 110, 40, waist};
ItemTemplate cintura = {&cinturaData, &cinturaPhysical};

Armor anelacessoryArmor("anel magico", 1, 1, true, false, 1);
ItemData anelData = {&anelacessoryArmor};
physicalData anelPhysical = {{0}, 0, 0, 20, true, 60, 30, accessory};
ItemTemplate anel = {&anelData, &anelPhysical};

Potion pocaocuraPotion("pocao de cura", 0.5, 1, false, true, 25, 0, 1);
ItemData pocaocuraData = {&pocaocuraPotion};
physicalData pocaocuraPhysical = {{0}, 0, 0, 15, true, 35, 45, accessory};
ItemTemplate pocaocura = {&pocaocuraData, &pocaocuraPhysical};

Potion pocaodanoPotion("pocao de dano", 0.5, 1, false, true, 0, 20, 2);
ItemData pocaodanoData = {&pocaodanoPotion};
physicalData pocaodanoPhysical = {{0}, 0, 0, 15, true, 35, 45, accessory};
ItemTemplate pocaodano = {&pocaodanoData, &pocaodanoPhysical};

Item amuletoitem("amuleto antigo", 1, 1, true, false);
ItemData amuletoData = {&amuletoitem};
physicalData amuletoPhysical = {{0}, 20, 20, 20, true, 60, 60, accessory};
ItemTemplate amuleto = {&amuletoData, &amuletoPhysical};

void InitItemList() {
    espadacurtaPhysical.texture = LoadTexture("images/Itens/short sword.png");
    SetTextureFilter(espadacurtaPhysical.texture, TEXTURE_FILTER_POINT);

    cuboslimePhysical.texture = LoadTexture("images/Itens/Slime Cube.png");
    SetTextureFilter(cuboslimePhysical.texture, TEXTURE_FILTER_POINT);

    pocaomisteriosaPhysical.texture = LoadTexture("images/Itens/Mistery Flask.png");
    SetTextureFilter(pocaomisteriosaPhysical.texture, TEXTURE_FILTER_POINT);

    coletecouroPhyisical.texture = LoadTexture("images/Itens/leathervest.png");
    SetTextureFilter(coletecouroPhyisical.texture, TEXTURE_FILTER_POINT);

    espadalongaPhysical.texture = LoadTexture("images/Itens/long sword.png");
    SetTextureFilter(espadalongaPhysical.texture, TEXTURE_FILTER_POINT);

    arcoPhysical.texture = LoadTexture("images/Itens/bow.png");
    SetTextureFilter(arcoPhysical.texture, TEXTURE_FILTER_POINT);

    lançaPhysical.texture = LoadTexture("images/Itens/spear.png");
    SetTextureFilter(lançaPhysical.texture, TEXTURE_FILTER_POINT);

    capacetePhysical.texture = LoadTexture("images/Itens/iron helmet.png");
    SetTextureFilter(capacetePhysical.texture, TEXTURE_FILTER_POINT);

    botasPhysical.texture = LoadTexture("images/Itens/boots.png");
    SetTextureFilter(botasPhysical.texture, TEXTURE_FILTER_POINT);

    cinturaPhysical.texture = LoadTexture("images/Itens/skull belt.png");
    SetTextureFilter(cinturaPhysical.texture, TEXTURE_FILTER_POINT);

    anelPhysical.texture = LoadTexture("images/Itens/ring.png");
    SetTextureFilter(anelPhysical.texture, TEXTURE_FILTER_POINT);

    amuletoPhysical.texture = LoadTexture("images/Itens/collar.png");
    SetTextureFilter(amuletoPhysical.texture, TEXTURE_FILTER_POINT);

    pocaocuraPhysical.texture = LoadTexture("images/Itens/health potion.png");
    SetTextureFilter(pocaocuraPhysical.texture, TEXTURE_FILTER_POINT);

    pocaodanoPhysical.texture = LoadTexture("images/Itens/damage potion.png");
    SetTextureFilter(pocaodanoPhysical.texture, TEXTURE_FILTER_POINT);
}