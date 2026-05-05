#include "itemlist.h"
#include "Equipament.h"
#include "item.h"
#include "raylib.h"
#include <vector>
#include <cstdlib>

// ===== ESPADAS ===== 
Weapon espadacurtaweapon("Espada Curta", 0.4f, 2, true, false, 5, 3, sword, 1.0f, common);
ItemData espadacurtaData = {&espadacurtaweapon};
physicalData espadacurtaPhysical = {{0}, 25, 200, 0, false, 65, 200, handright};
ItemTemplate espadacurta = {&espadacurtaData, &espadacurtaPhysical};

Weapon espadacurtaUCweapon("Espada Curta Reforçada", 0.4f, 2, true, false, 8, 3, sword, 0.95f, uncommon);
ItemData espadacurtaUCData = {&espadacurtaUCweapon};
physicalData espadacurtaUCPhysical = {{0}, 22, 250, 0, false, 62, 250, handright};
ItemTemplate espadacurtaUC = {&espadacurtaUCData, &espadacurtaUCPhysical};

Weapon espadamediaweapon("Espada Media", 0.5f, 3, true, false, 12, 5, sword, 0.85f, rare);
ItemData espadamediaData = {&espadamediaweapon};
physicalData espadamediaPhysical = {{0}, 22, 250, 0, false, 62, 250, handright};
ItemTemplate espadamedia = {&espadamediaData, &espadamediaPhysical};

Weapon espadamediaEPweapon("Espada Media Encantada", 0.55f, 3, true, false, 17, 5, sword, 0.8f, epic);
ItemData espadamediaEPData = {&espadamediaEPweapon};
physicalData espadamediaEPPhysical = {{0}, 32, 300, 0, false, 72, 300, handright};
ItemTemplate espadamediaEP = {&espadamediaEPData, &espadamediaEPPhysical};

Weapon espadalongaweapon("Espada Longa", 0.9f, 4, true, false, 22, 7, sword, 0.7f, legendary);
ItemData espadalongaData = {&espadalongaweapon};
physicalData espadalongaPhysical = {{0}, 30, 350, 0, false, 110, 350, handright};
ItemTemplate espadalonga = {&espadalongaData, &espadalongaPhysical};

// ===== FACAS =====
Weapon facapequenaweapon("Faca Pequena", 0.6f, 1, true, false, 3, 2, sword, 0.5f, common);
ItemData facapequenaData = {&facapequenaweapon};
physicalData facapequenaPhysical = {{0}, 24, 150, 0, false, 34, 150, handleft};
ItemTemplate facapequena = {&facapequenaData, &facapequenaPhysical};

Weapon facapequenaUCweapon("Faca Afiada", 0.6f, 1, true, false, 3, 2, sword, 0.5f, uncommon);
ItemData facapequenaUCData = {&facapequenaUCweapon};
physicalData facapequenaUCPhysical = {{0}, 24, 150, 0, false, 34, 150, handleft};
ItemTemplate facapequenaUC = {&facapequenaUCData, &facapequenaUCPhysical};

Weapon facarararweapon("Faca Serrilhada", 0.7f, 2, true, false, 8, 3, sword, 0.4f, rare);
ItemData facarararData = {&facarararweapon};
physicalData facarararPhysical = {{0}, 38, 170, 0, false, 58, 200, handleft};
ItemTemplate facarara = {&facarararData, &facarararPhysical};

Weapon facaEPweapon("Faca Envenenada", 0.75f, 2, true, false, 13, 3, sword, 0.35f, epic);
ItemData facaEPData = {&facaEPweapon};
physicalData facaEPPhysical = {{0}, 38, 170, 0, false, 58, 200, handleft};
ItemTemplate facaEP = {&facaEPData, &facaEPPhysical};

Weapon facalendweapon("Faca Sombria", 1, 2, true, false, 18, 4, sword, 0.3f, legendary);
ItemData facalendData = {&facalendweapon};
physicalData facalendPhysical = {{0}, 32, 220, 0, false, 62, 220, handleft};
ItemTemplate facalend = {&facalendData, &facalendPhysical};

// ===== ARCOS =====
Weapon arcopequweapon("Arco Simples", 0.4f, 3, true, false, 6, 15, bow, 1.2f, common);
ItemData arcopequData = {&arcopequweapon};
physicalData arcopequPhysical = {{0}, 180*0.7, 152*0.7, 0, false, 180*0.7, 152*0.7, handright};
ItemTemplate arcopeq = {&arcopequData, &arcopequPhysical};

Weapon arcopequUCweapon("Arco Reforçado", 0.45f, 3, true, false, 9, 16, bow, 1.1f, uncommon);
ItemData arcopequUCData = {&arcopequUCweapon};
physicalData arcopequUCPhysical = {{0}, 180*0.7, 152*0.7, 0, false, 180*0.7, 152*0.7, handright};
ItemTemplate arcopequUC = {&arcopequUCData, &arcopequUCPhysical};

Weapon arcorarweapon("Arco Élfico", 0.5f, 4, true, false, 14, 20, bow, 1.0f, rare);
ItemData arcorarData = {&arcorarweapon};
physicalData arcorarPhysical = {{0}, 54, 280, 0, false, 54, 280, handright};
ItemTemplate arcorar = {&arcorarData, &arcorarPhysical};

Weapon arcoEPweapon("Arco das Sombras", 0.55f, 4, true, false, 20, 22, bow, 0.9f, epic);
ItemData arcoEPData = {&arcoEPweapon};
physicalData arcoEPPhysical = {{0}, 54, 280, 0, false, 54, 280, handright};
ItemTemplate arcoEP = {&arcoEPData, &arcoEPPhysical};

Weapon arcolendweapon("Arco Dracônico", 0.7f, 5, true, false, 28, 25, bow, 0.8f, legendary);
ItemData arcolendData = {&arcolendweapon};
physicalData arcolendPhysical = {{0}, 134, 260, 0, false, 134, 300, handright};
ItemTemplate arcolend = {&arcolendData, &arcolendPhysical};

// ===== CAPACETES =====
Armor capacetecomumArmor("Capacete de Ferro", 0.8f, 2, true, false, 3, common);
ItemData capacetecomumData = {&capacetecomumArmor};
physicalData capacetecomumPhysical = {{0}, 100*0.8, 124*0.8, 0, false, 60*0.8, 144*0.8, head};
ItemTemplate capacetecomum = {&capacetecomumData, &capacetecomumPhysical};

Armor capaceteUCArmor("Capacete Rebitado", 0.9f, 2, true, false, 6, uncommon);
ItemData capaceteUCData = {&capaceteUCArmor};
physicalData capaceteUCPhysical = {{0}, 100*0.8, 124*0.8, 0, false, 120*0.8, 144*0.8, head};
ItemTemplate capaceteUC = {&capaceteUCData, &capaceteUCPhysical};

Armor capaceterareArmor("Capacete de Aço", 1.2f, 3, true, false, 13, rare);
ItemData capaceterareData = {&capaceterareArmor};
physicalData capaceterarePhysical = {{0}, 80*0.8, 164*0.8, 0, false, 65*0.8, 164*0.8, head};
ItemTemplate capaceterare = {&capaceterareData, &capaceterarePhysical};

Armor capaceteEPArmor("Capacete Encantado", 1.4f, 3, true, false, 15, epic);
ItemData capaceteEPData = {&capaceteEPArmor};
physicalData capaceteEPPhysical = {{0}, 80*0.8, 164*0.8, 0, false, 130*0.8, 164*0.8, head};
ItemTemplate capaceteEP = {&capaceteEPData, &capaceteEPPhysical};

Armor capacetelegendArmor("Elmo do Dragão", 2.0f, 4, true, false, 25, legendary);
ItemData capacetelegendData = {&capacetelegendArmor};
physicalData capacetelegendPhysical = {{0}, 100*0.8, 112*0.8, 0, false, 140*0.8, 172*0.8, head};
ItemTemplate capacetelegend = {&capacetelegendData, &capacetelegendPhysical};

// ===== PEITORAIS =====
Armor coletecomumArmor("Colete de Couro", 0.5f, 3, true, false, 5, common);
ItemData coletecomumData = {&coletecomumArmor};
physicalData coletecomumPhysical = {{0}, 110, 157*1.1, 0, false, 80, 157*1.1, chest};
ItemTemplate coletecomum = {&coletecomumData, &coletecomumPhysical};

Armor coleteUCArmor("Colete Reforçado", 0.7f, 3, true, false, 14, uncommon);
ItemData coleteUCData = {&coleteUCArmor};
physicalData coleteUCPhysical = {{0}, 110, 157*1.1, 0, false, 160, 157*1.1, chest};
ItemTemplate coleteUC = {&coleteUCData, &coleteUCPhysical};

Armor coterareArmor("Cota de Malha", 1.5f, 4, true, false, 25, rare);
ItemData coterareData = {&coterareArmor};
physicalData coterarePhysical = {{0}, 110, 162*1.1, 0, false, 85, 162*1.1, chest};
ItemTemplate coterare = {&coterareData, &coterarePhysical};

Armor coteEPArmor("Cota Encantada", 1.8f, 4, true, false, 45, epic);
ItemData coteEPData = {&coteEPArmor};
physicalData coteEPPhysical = {{0}, 110, 162*1.1, 0, false, 170, 162*1.1, chest};
ItemTemplate coteEP = {&coteEPData, &coteEPPhysical};

Armor cotelegendArmor("Armadura do Caos", 3.0f, 5, true, false, 45, legendary);
ItemData cotelegendData = {&cotelegendArmor};
physicalData cotelegendPhysical = {{0}, 115, 144*1.1, 0, false, 175, 194*1.1, chest};
ItemTemplate cotelegend = {&cotelegendData, &cotelegendPhysical};

// ===== CINTURAS =====
Armor cintocomumArmor("Cinto de Couro", 0.4f, 1, true, false, 1, common);
ItemData cintocomumData = {&cintocomumArmor};
physicalData cintocomumPhysical = {{0}, 190*0.6, 30*0.6, 0, false, 100*0.6, 70*0.6, waist};
ItemTemplate cintocomum = {&cintocomumData, &cintocomumPhysical};

Armor cintoUCArmor("Cinto Reforçado", 0.4f, 1, true, false, 2, uncommon);
ItemData cintoUCData = {&cintoUCArmor};
physicalData cintoUCPhysical = {{0}, 190*0.6, 30*0.6, 0, false, 200*0.6, 70*0.6, waist};
ItemTemplate cintoUC = {&cintoUCData, &cintoUCPhysical};

Armor cintorareArmor("Cinto de Escamas", 0.5f, 2, true, false, 6, rare);
ItemData cintorareData = {&cintorareArmor};
physicalData cintorarePhysical = {{0}, 200*0.6, 50*0.6, 0, false, 105*0.6, 57*0.6, waist};
ItemTemplate cintorare = {&cintorareData, &cintorarePhysical};

Armor cintoEPArmor("Cinto do Guardião", 0.7f, 2, true, false, 7, epic);
ItemData cintoEPData = {&cintoEPArmor};
physicalData cintoEPPhysical = {{0}, 200*0.6, 50*0.6, 0, false, 210*0.6, 57*0.6, waist};
ItemTemplate cintoEP = {&cintoEPData, &cintoEPPhysical};

Armor cintolendArmor("Cinto da Morte", 1.0f, 3, true, false, 10, legendary);
ItemData cintolendData = {&cintolendArmor};
physicalData cintolendPhysical = {{0}, 200*0.6, 37*0.6, 0, false, 220*0.6, 107*0.6, waist};
ItemTemplate cintolend = {&cintolendData, &cintolendPhysical};

// ===== BOTAS =====
Armor botascomumArmor("Botas de Couro", 0.4f, 2, true, false, 1, common);
ItemData botascomumData = {&botascomumArmor};
physicalData botascomumPhysical = {{0}, 100*0.7, 115*0.7, 0, false, 65*0.7, 115*0.7, feet};
ItemTemplate botascomum = {&botascomumData, &botascomumPhysical};

Armor botasUCArmor("Botas Reforçadas", 0.4f, 2, true, false, 3, uncommon);
ItemData botasUCData = {&botasUCArmor};
physicalData botasUCPhysical = {{0}, 100*0.7, 115*0.7, 0, false, 130*0.7, 115*0.7, feet};
ItemTemplate botasUC = {&botasUCData, &botasUCPhysical};

Armor botasrareArmor("Botas de Ferro", 0.8f, 3, true, false, 6, rare);
ItemData botasrareData = {&botasrareArmor};
physicalData botasrarePhysical = {{0}, 120*0.7, 123*0.7, 0, false, 701*0.7, 123*0.7, feet};
ItemTemplate botasrare = {&botasrareData, &botasrarePhysical};

Armor botasEPArmor("Botas de Aço", 1.0f, 3, true, false, 8, epic);
ItemData botasEPData = {&botasEPArmor};
physicalData botasEPPhysical = {{0}, 120*0.7, 123*0.7, 0, false, 140*0.7, 123*0.7, feet};
ItemTemplate botasEP = {&botasEPData, &botasEPPhysical};

Armor botaslegendArmor("Botas do Vento", 1.5f, 4, true, false, 20, legendary);
ItemData botaslegendData = {&botaslegendArmor};
physicalData botaslegendPhysical = {{0}, 130*0.7, 164*0.7, 0, false, 130*0.7, 164*0.7, feet};
ItemTemplate botaslegend = {&botaslegendData, &botaslegendPhysical};

// ===== ACESSÓRIOS =====
Armor anelocomumArmor("Anel de Bronze", 0.4f, 1, true, false, 1, common);
ItemData anelocomumData = {&anelocomumArmor};
physicalData anelocomumPhysical = {{0}, 70, 27, 0, false, 70, 27, accessory};
ItemTemplate anelocomum = {&anelocomumData, &anelocomumPhysical};

Armor aneloUCArmor("Anel de Prata", 0.4f, 1, true, false, 2, uncommon);
ItemData aneloUCData = {&aneloUCArmor};
physicalData aneloUCPhysical = {{0}, 70, 32, 0, false, 70, 32, accessory};
ItemTemplate aneloUC = {&aneloUCData, &aneloUCPhysical};

Armor anelorareArmor("Anel de Safira", 0.4f, 1, true, false, 4, rare);
ItemData anelorareData = {&anelorareArmor};
physicalData anelorarePhysical = {{0}, 75, 31, 0, false, 75, 31, accessory};
ItemTemplate anelorare = {&anelorareData, &anelorarePhysical};

Armor aneloEPArmor("Anel de Rubi", 0.4f, 1, true, false, 7, epic);
ItemData aneloEPData = {&aneloEPArmor};
physicalData aneloEPPhysical = {{0}, 75, 40, 0, false, 75, 40, accessory};
ItemTemplate aneloEP = {&aneloEPData, &aneloEPPhysical};

Armor anelolendArmor("Anel do Abismo", 0.4f, 1, true, false, 10, legendary);
ItemData anelolendData = {&anelolendArmor};
physicalData anelolendPhysical = {{0}, 80, 65, 0, false, 80, 65, accessory};
ItemTemplate anelolend = {&anelolendData, &anelolendPhysical};

// ===== INGREDIENTES =====
Ingredient ingredientBaseIng(5,"Base de pocao",0.2,1,false,true);
ItemData ingredientBaseData = {&ingredientBaseIng};
physicalData ingredientBasePhysical = {{0},50,100,0,false,50,100};
ItemTemplate ingredientBase = {&ingredientBaseData,&ingredientBasePhysical};

Ingredient ingredienteDanoIng(0,"Lodo da morte",0.4,1,false,true);
ItemData ingredienteDanoData = {&ingredienteDanoIng};
physicalData ingredienteDanoPhysical = {{0},100,100,50,true,100,100};
ItemTemplate ingredienteDano = {&ingredienteDanoData,&ingredienteDanoPhysical};

Ingredient ingredienteVidaIng(1,"Ervas de menta",0.4,1,false,true);
ItemData ingredienteVidaData = {&ingredienteVidaIng};
physicalData ingredienteVidaPhysical = {{0},50,90,0,false,75,90};
ItemTemplate ingredienteVida = {&ingredienteVidaData,&ingredienteVidaPhysical};

Ingredient ingredienteSpeedIng(2,"Pena de Aguia",0.4,1,false,true);
ItemData ingredienteSpeedData = {&ingredienteSpeedIng};
physicalData ingredienteSpeedPhysical = {{0},25,100,0,false,25,100};
ItemTemplate ingredienteSpeed = {&ingredienteSpeedData,&ingredienteSpeedPhysical};

Ingredient ingredienteLuckIng(3,"Trevo 4 folhas",0.4,1,false,true);
ItemData ingredienteLuckData = {&ingredienteLuckIng};
physicalData ingredienteLuckPhysical = {{0},90,90,45,true,100,100};
ItemTemplate ingredienteLuck = {&ingredienteLuckData,&ingredienteLuckPhysical};

Ingredient ingredienteMultIng(4,"Estrela do Alem",0.4,1,false,true);
ItemData ingredienteMultData = {&ingredienteMultIng};
physicalData ingredienteMultPhysical = {{0},75,75,50,true,100,100};
ItemTemplate ingredienteMult = {&ingredienteMultData,&ingredienteMultPhysical};

// ===== POCOES =====
Potion_Damage pocaoDanoPoc("Base de pocao",0.2,1);
ItemData pocaoDanoData = {&pocaoDanoPoc};
physicalData pocaoDanoPhysical = {{0},50,100,0,false,50,100};
ItemTemplate pocaoDano = {&pocaoDanoData,&pocaoDanoPhysical};

Potion_Health pocaoVidaPoc("Base de pocao",0.2,1);
ItemData pocaoVidaData = {&pocaoVidaPoc};
physicalData pocaoVidaPhysical = {{0},50,100,0,false,50,100};
ItemTemplate pocaoVida = {&pocaoVidaData,&pocaoVidaPhysical};

Potion_Speed pocaoSpeedPoc("Base de pocao",0.2,1);
ItemData pocaoSpeedData = {&pocaoSpeedPoc};
physicalData pocaoSpeedPhysical = {{0},50,100,0,false,50,100};
ItemTemplate pocaoSpeed = {&pocaoSpeedData,&pocaoSpeedPhysical};

Potion_Luck pocaoLuckPoc("Base de pocao",0.2,1);
ItemData pocaoLuckData = {&pocaoLuckPoc};
physicalData pocaoLuckPhysical = {{0},50,100,0,false,50,100};
ItemTemplate pocaoLuck = {&pocaoLuckData,&pocaoLuckPhysical};

Potion_Mult pocaoMultPoc("Base de pocao",0.2,1);
ItemData pocaoMultData = {&pocaoMultPoc};
physicalData pocaoMultPhysical = {{0},50,100,0,false,50,100};
ItemTemplate pocaoMult = {&pocaoMultData,&pocaoMultPhysical};


void InitItemList() {
    // ===== ESPADAS =====
    espadacurtaPhysical.texture    = LoadTexture("images/Itens/short sword.png");
    espadacurtaUCPhysical.texture  = LoadTexture("images/Itens/medium sword.png");
    espadamediaPhysical.texture    = LoadTexture("images/Itens/medium sword.png");
    espadamediaEPPhysical.texture  = LoadTexture("images/Itens/long sword.png");
    espadalongaPhysical.texture    = LoadTexture("images/Itens/dragon claymore.png");

    // ===== FACAS =====
    facapequenaPhysical.texture    = LoadTexture("images/Itens/knife.png");
    facapequenaUCPhysical.texture  = LoadTexture("images/Itens/knife.png");
    facarararPhysical.texture      = LoadTexture("images/Itens/dagger.png");
    facaEPPhysical.texture         = LoadTexture("images/Itens/dagger.png");
    facalendPhysical.texture       = LoadTexture("images/Itens/dragon dagger.png");

    // ===== ARCOS =====
    arcopequPhysical.texture       = LoadTexture("images/Itens/small bow.png");
    arcopequUCPhysical.texture     = LoadTexture("images/Itens/small bow.png");
    arcorarPhysical.texture        = LoadTexture("images/Itens/bow.png");
    arcoEPPhysical.texture         = LoadTexture("images/Itens/bow.png");
    arcolendPhysical.texture       = LoadTexture("images/Itens/dragon bow.png");

    // ===== CAPACETES =====
    capacetecomumPhysical.texture  = LoadTexture("images/Itens/leather helmet.png");
    capaceteUCPhysical.texture     = LoadTexture("images/Itens/leather helmet.png");
    capaceterarePhysical.texture   = LoadTexture("images/Itens/chain helmet.png");
    capaceteEPPhysical.texture     = LoadTexture("images/Itens/chain helmet.png");
    capacetelegendPhysical.texture = LoadTexture("images/Itens/dragon helmet.png");

    // ===== PEITORAIS =====
    coletecomumPhysical.texture    = LoadTexture("images/Itens/leather chestplate.png");
    coleteUCPhysical.texture       = LoadTexture("images/Itens/leather chestplate.png");
    coterarePhysical.texture       = LoadTexture("images/Itens/chain chestplate.png");
    coteEPPhysical.texture         = LoadTexture("images/Itens/chain chestplate.png");
    cotelegendPhysical.texture     = LoadTexture("images/Itens/dragon chestplate.png");

    // ===== CINTURAS =====
    cintocomumPhysical.texture     = LoadTexture("images/Itens/leather belt.png");
    cintoUCPhysical.texture        = LoadTexture("images/Itens/leather belt.png");
    cintorarePhysical.texture      = LoadTexture("images/Itens/iron belt.png");
    cintoEPPhysical.texture        = LoadTexture("images/Itens/iron belt.png");
    cintolendPhysical.texture      = LoadTexture("images/Itens/dragon belt.png");

    // ===== BOTAS =====
    botascomumPhysical.texture     = LoadTexture("images/Itens/leather boots.png");
    botasUCPhysical.texture        = LoadTexture("images/Itens/leather boots.png");
    botasrarePhysical.texture      = LoadTexture("images/Itens/chain boots.png");
    botasEPPhysical.texture        = LoadTexture("images/Itens/chain boots.png");
    botaslegendPhysical.texture    = LoadTexture("images/Itens/dragon boots.png");

    // ===== ACESSÓRIOS =====
    anelocomumPhysical.texture     = LoadTexture("images/Itens/copper ring.png");
    aneloUCPhysical.texture        = LoadTexture("images/Itens/silver ring.png");
    anelorarePhysical.texture      = LoadTexture("images/Itens/sapphire ring.png");
    aneloEPPhysical.texture        = LoadTexture("images/Itens/ruby ring.png");
    anelolendPhysical.texture      = LoadTexture("images/Itens/dragon ring.png");

    // ===== INGREDIENTES ======
    ingredientBasePhysical.texture   = LoadTexture("images/Itens/pocao vazia.png");
    ingredienteDanoPhysical.texture  = LoadTexture("images/Itens/ingredientedano.png");
    ingredienteVidaPhysical.texture  = LoadTexture("images/Itens/ingredientevida.png");
    ingredienteSpeedPhysical.texture = LoadTexture("images/Itens/ingredientespeed.png");
    ingredienteLuckPhysical.texture  = LoadTexture("images/Itens/ingredienteSorte.png");
    ingredienteMultPhysical.texture  = LoadTexture("images/Itens/ingredientemult.png");
    
    // ===== POCOES =====
    pocaoDanoPhysical.texture = LoadTexture("images/Itens/pocao dano.png");
    pocaoVidaPhysical.texture = LoadTexture("images/Itens/pocao vida.png");
    pocaoSpeedPhysical.texture = LoadTexture("images/Itens/pocao velocidade.png");
    pocaoLuckPhysical.texture = LoadTexture("images/Itens/pocao sorte.png");
    pocaoMultPhysical.texture = LoadTexture("images/Itens/pocao mult.png");

    // ===== FILTRO EM TODOS =====
    SetTextureFilter(espadacurtaPhysical.texture,    TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(espadacurtaUCPhysical.texture,  TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(espadamediaPhysical.texture,    TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(espadamediaEPPhysical.texture,  TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(espadalongaPhysical.texture,    TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(facapequenaPhysical.texture,    TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(facapequenaUCPhysical.texture,  TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(facarararPhysical.texture,      TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(facaEPPhysical.texture,         TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(facalendPhysical.texture,       TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(arcopequPhysical.texture,       TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(arcopequUCPhysical.texture,     TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(arcorarPhysical.texture,        TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(arcoEPPhysical.texture,         TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(arcolendPhysical.texture,       TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(capacetecomumPhysical.texture,  TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(capaceteUCPhysical.texture,     TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(capaceterarePhysical.texture,   TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(capaceteEPPhysical.texture,     TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(capacetelegendPhysical.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(coletecomumPhysical.texture,    TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(coleteUCPhysical.texture,       TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(coterarePhysical.texture,       TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(coteEPPhysical.texture,         TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(cotelegendPhysical.texture,     TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(cintocomumPhysical.texture,     TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(cintoUCPhysical.texture,        TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(cintorarePhysical.texture,      TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(cintoEPPhysical.texture,        TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(cintolendPhysical.texture,      TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(botascomumPhysical.texture,     TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(botasUCPhysical.texture,        TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(botasrarePhysical.texture,      TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(botasEPPhysical.texture,        TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(botaslegendPhysical.texture,    TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(anelocomumPhysical.texture,     TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(aneloUCPhysical.texture,        TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(anelorarePhysical.texture,      TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(aneloEPPhysical.texture,        TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(anelolendPhysical.texture,      TEXTURE_FILTER_BILINEAR);
}