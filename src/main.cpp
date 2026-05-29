/**
 * @file main.cpp
 * @author Heitor Farias Piza (hpiza@alunos.utfpr.edu.br) e Felipe de Ornellas Tonin (felipetonin@alunos.utfpr.edu.br)
 * @brief Este arquivo mantem o funcionamento do jogo, sendo responsavel pelo sistema de crafting, combate, inventario, leveling, physics rendering, rendering, etc...
 * @version 0.1
 * @date 2026-05-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include "enemy.h"
#include "item.h"
#include "itemlist.h"
#include "Equipament.h"
#include "player.h"
#include <asm-generic/errno.h>
#include <raylib.h>
#include <box2d/box2d.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include "enemylist.h"
#include "saveManager.h"
#define scale 10
using namespace std;
using namespace RPG;



enum GameStage{menu,config,inventory,run};
GameStage currentgamestage;
const int screenWidth = 1280*1.5;
const int screenHeight = 720*1.5;
bool MousePressed = false;
physicalObject* GrabbedObject = nullptr;
Player player("hero", 100, 100, 5, 10.0f, true, true, 0,(atributes){0,0,0,1,5});
int bonuspocaomult=1;
int bonuspocaodano=0;
int bonuspocaospeed=0;
int bonuspocaosorte=0;
RPG::Ingredient* ingrediente1 = nullptr;
RPG::Ingredient* ingrediente2 = nullptr;
int ingredienteTipo1 = -1;
int ingredienteTipo2 = -1;
bool craftPendente = false;
int craftT1 = -1, craftT2 = -1;
b2BodyId craftBodyT1 = b2_nullBodyId;
b2BodyId craftBodyT2 = b2_nullBodyId;
static Font FonteBonita;


void StatusUpdater(physicalObject& body){

    // aplica bonus dos equipamentos quando o item e equipado
    if(body.isEquipped && !body.wasEquipped){
        RPG::Item* item = body.templateData.itemData->item;
        
        // usa dynamic_cast pra descobrir se o item equipado e uma arma
        RPG::Weapon* w = dynamic_cast<RPG::Weapon*>(item);
        if(w){
            player.setDamage(player.getDamage() + w->getDamage());
            float base = w->getAttackSpeed();  //No dia 29/05 as 01:28, esta linha e a linha 67, incrivel
            player.setBaseAttackSpeed(base);
            player.setAttackSpeed(max(0.1f, base - player.getAtributodestreza() * 0.05f - bonuspocaospeed));
        }
        RPG::Armor* a = dynamic_cast<RPG::Armor*>(item);
        if(a) player.setDefense(player.getDefense() + a->getDefense());
    }

    if(!body.isEquipped && body.wasEquipped){
        RPG::Item* item = body.templateData.itemData->item;
        
        RPG::Weapon* w = dynamic_cast<RPG::Weapon*>(item);
        if(w){
            player.setDamage(player.getDamage() - w->getDamage()); // subtrai
            player.setBaseAttackSpeed(1.0f);
            player.setAttackSpeed(1.0f);
        }   
        RPG::Armor* a = dynamic_cast<RPG::Armor*>(item);
        if(a) player.setDefense(player.getDefense() - a->getDefense());
    }

    body.wasEquipped = body.isEquipped;
}

// gerador rapido de paredes fisicas do inventario
physicalObject WallGenerator(b2WorldId world, float xP, float yP,float width, float height, enum b2BodyType type){ 
    b2BodyDef bodyDef = b2DefaultBodyDef(); //definebody 
    bodyDef.position = {(xP)/scale, (yP)/scale}; //define posicao inicial 
    bodyDef.type = type;
    b2BodyId bodyId = b2CreateBody(world, &bodyDef); //cria o "perfil" no mundo 
    b2Polygon bodyBox = b2MakeBox((width/2)/scale, (height/2)/scale); //cria uma caixa com o tamanho definido 
    b2ShapeDef bodyshapeDef = b2DefaultShapeDef(); //coloca o formato como quadrado padrao do box2d 
    bodyshapeDef.filter.categoryBits = CAT_PAREDE;
    bodyshapeDef.filter.maskBits = CAT_ITEM | CAT_ITEMSEGURADO;
    b2CreatePolygonShape(bodyId, &bodyshapeDef, &bodyBox); //aplica o formato e a caixa em um poligono 
    physicalObject Parede;
    Parede.isWall = true;
    Parede.wallData = {(Texture2D){1},(float)width, (float)height, 0, false};
    Parede.bodyId = bodyId;
    return Parede;
}

// cria item fisico no mundo usando template
physicalObject ItemGenerator(b2WorldId world, ItemTemplate& templ, float xP, float yP, enum b2BodyType type){ 
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = {(xP)/scale, (yP)/scale};
    bodyDef.type = type;
    physicalObject Item;
    b2BodyId bodyId = b2CreateBody(world, &bodyDef);
    
    if(!templ.itemPhysical->isCircle){
        b2Polygon bodyBox = b2MakeBox((templ.itemPhysical->width/2)/scale, (templ.itemPhysical->height/2)/scale);
        b2ShapeDef bodyshapeDef = b2DefaultShapeDef();
        bodyshapeDef.filter.categoryBits = CAT_ITEM;
        bodyshapeDef.filter.maskBits = CAT_PAREDE | CAT_ITEM;
        bodyshapeDef.density = 1.0f;
        Item.shapeId = b2CreatePolygonShape(bodyId, &bodyshapeDef, &bodyBox);
    } else {
        b2Circle circle;
        circle.center = {0.0f, 0.0f};
        circle.radius = templ.itemPhysical->radius/scale;
        b2ShapeDef ballshapeDef = b2DefaultShapeDef();
        ballshapeDef.filter.categoryBits = CAT_ITEM;
        ballshapeDef.filter.maskBits = CAT_PAREDE | CAT_ITEM;
        ballshapeDef.density = 1.0f;
        ballshapeDef.density = 1.0f;
        Item.shapeId = b2CreateCircleShape(bodyId, &ballshapeDef, &circle);
    }

    Item.isWall = false;
    Item.isGrabbed = false;
    Item.templateData.itemPhysical = templ.itemPhysical;
    Item.templateData.itemData = templ.itemData;
    Item.bodyId = bodyId;
    return Item;
}

// contexto geral do inventario
// guarda texturas, mundo fisico, itens e slots
struct InventoryContext {
    Texture2D openbackpackTex;
    Texture2D equipamentTab;
    Texture2D backgroundtexture;
    Texture2D accessoryslot;
    Texture2D trash;
    Texture2D bar1;
    Texture2D painel1;
    Image backgroundimage;
    
    b2WorldId world;
    
    std::vector<physicalObject> BackpackWalls;
    std::vector<physicalObject> TotalItems;
    std::vector<InventoryPivotPoint> SlotsEquipamentos;
    
    float backpackScale;
    float backpackCenterX;
    float backpackCenterY;
    float backpackW;
    float backpackH;
    float trashTimer = 0.0f;
    bool itemOnTrash = false;
};

InventoryContext inv;
bool spawnedThisGame = false;


// sistema de crafting usando clique direito nos ingredientes
void PotionCrafter(physicalObject& body){
    RPG::Item* item = body.templateData.itemData->item;
    ICraftavel* craftavel = dynamic_cast<ICraftavel*>(item);
    if(!craftavel) return;

    int tipo = craftavel->getCraftType();

    b2Vec2 mousePoint = {(float)GetMouseX() / scale, (float)GetMouseY() / scale};
    if(!IsMouseButtonPressed(1)) return;
    if(!b2Shape_TestPoint(body.shapeId, mousePoint)) return;


    // primeiro ingrediente selecionado
    if(ingredienteTipo1 == -1){
        ingredienteTipo1 = tipo;
        craftBodyT1 = body.bodyId;
        return;
    }
    if(ingredienteTipo1 == tipo) return;

    ingredienteTipo2 = tipo;
    craftBodyT2 = body.bodyId;
    craftT1 = ingredienteTipo1;
    craftT2 = ingredienteTipo2;
    ingredienteTipo1 = -1;
    ingredienteTipo2 = -1;

    if(craftT2 == 5){ 
        int tmp = craftT1; craftT1 = craftT2; craftT2 = tmp;
        b2BodyId tmpId = craftBodyT1; craftBodyT1 = craftBodyT2; craftBodyT2 = tmpId;
    }
    if(craftT1 == 5) craftPendente = true;
}

// sistema de arrastar item usando fisica ao inves de teleportar
void grab(physicalObject& body){
    b2Vec2 mousePoint = {(float)GetMouseX() / scale, (float)GetMouseY() / scale};
    b2Vec2 pos = b2Body_GetPosition(body.bodyId);

    b2Rot rot = b2Body_GetRotation(body.bodyId);
    float angle = b2Rot_GetAngle(rot);
    
    if(IsMouseButtonUp(0)){
        b2Filter filter = b2Shape_GetFilter(body.shapeId);
        filter.maskBits = CAT_ITEM | CAT_PAREDE;
        b2Shape_SetFilter(body.shapeId, filter);

        if(GrabbedObject == &body){
            GrabbedObject = nullptr;
            body.isGrabbed=false;
        }

        if(body.isEquipped==true){
            b2Filter filter = b2Shape_GetFilter(body.shapeId);
            filter.maskBits = 0;
            b2Shape_SetFilter(body.shapeId, filter);
        }
    }
    
    if(GrabbedObject == nullptr && b2Shape_TestPoint(body.shapeId, mousePoint)){
        if(IsMouseButtonDown(0)){
            GrabbedObject = &body;
            
            if(body.isEquipped){
                for(InventoryPivotPoint& ponto : inv.SlotsEquipamentos){
                    if(B2_ID_EQUALS(ponto.equippedBodyId, body.bodyId)){
                        ponto.equippedBodyId = b2_nullBodyId;
                    }
                }
                body.isEquipped = false;
                b2Body_SetGravityScale(body.bodyId, 1.0f);
            }
        }
    }
    
    if(GrabbedObject == &body){
        b2Vec2 direction = {mousePoint.x - pos.x, mousePoint.y - pos.y};

        // calcula direcao do mouse e aplica velocidade proporcional ao peso
        float velocidade = 1.0f / body.templateData.itemData->item->getWeight() * 10.0f;
        b2Vec2 speed = {
            direction.x * velocidade,
            direction.y * velocidade
        };
        body.isGrabbed=true;
        b2Filter filter = b2Shape_GetFilter(body.shapeId);
        filter.maskBits = CAT_ITEM;
        b2Shape_SetFilter(body.shapeId, filter);

        b2Body_SetLinearVelocity(body.bodyId, speed);
        
        if(IsKeyDown(KEY_A)){
            b2Body_SetAngularVelocity(body.bodyId, 0);
            angle -= 4 * DEG2RAD;
            b2Rot newRot = b2MakeRot(angle);
            b2Body_SetTransform(body.bodyId,pos,newRot);
        }
        if(IsKeyDown(KEY_D)){
            b2Body_SetAngularVelocity(body.bodyId, 0);
            angle += 4 * DEG2RAD;
            b2Rot newRot = b2MakeRot(angle);
            b2Body_SetTransform(body.bodyId,pos,newRot);
        }
    }
}

// verifica se item esta perto o suficiente do slot de equipamento
void PivotChecker(physicalObject& body, InventoryPivotPoint& ponto){
    if(GrabbedObject == &body) return;
    if(body.isEquipped && !B2_ID_EQUALS(ponto.equippedBodyId, body.bodyId)) return;

    itemCategory cat = body.templateData.itemPhysical->categoria;
    bool compativel = (cat == ponto.category) ||
                  (ponto.category == handright && cat == handleft) ||
                  (ponto.category == handleft  && cat == handright) ||
                  (ponto.category == handright && cat == hand) ||
                  (ponto.category == handleft  && cat == hand);

    if(!compativel || !body.templateData.itemData->item->isEquipable()) return;

    b2Vec2 itemPos = b2Body_GetPosition(body.bodyId);
    float itemX = itemPos.x * scale;
    float itemY = itemPos.y * scale;
    float pontoX = ponto.x + ponto.width / 2.0f;
    float pontoY = ponto.y + ponto.height / 2.0f;
    float distance = sqrt(pow(pontoX - itemX, 2) + pow(pontoY - itemY, 2));

    if(distance >= 100){
        if(B2_ID_EQUALS(ponto.equippedBodyId, body.bodyId)){
            ponto.equippedBodyId = b2_nullBodyId;
        }
        body.isEquipped = false;
        b2Body_SetGravityScale(body.bodyId, 1.0f);
        return;
    }

    bool slotLivre = B2_IS_NULL(ponto.equippedBodyId) || 
                     B2_ID_EQUALS(ponto.equippedBodyId, body.bodyId);
    if(!slotLivre) return;

    ponto.equippedBodyId = body.bodyId;
    body.isEquipped = true;
    b2Body_SetAngularVelocity(body.bodyId, 0);

    if(distance < 10.0f){
        b2Body_SetLinearVelocity(body.bodyId, {0, 0});
        b2Body_SetGravityScale(body.bodyId, 0.0f);
        return;
    }

    float dirX = (pontoX - itemX) / distance;
    float dirY = (pontoY - itemY) / distance;
    b2Vec2 speed = {dirX * distance * 0.5f, dirY * distance * 0.5f};
    b2Body_SetLinearVelocity(body.bodyId, speed);
}

struct RunContext {
    int faseAtual = 0;
    int contadorfases = 0;
    InimigoComp* inimigo = nullptr;
    std::vector<b2BodyId> itensEquipadosIds;

    int playerHitsRestantes = 0;
    int enemyHitsRestantes = 0;

    bool turnoEmAndamento = false;
    bool Playerjaatacou = false;
    bool Enemyjaatacou = false;
    bool turnoInimigo = false;
    float timerPlayerAtacou = 0.0f;
    float timerEnemyAtacou  = 0.0f;
    const float duracaoFrameAtaque = 0.35f;
    Texture2D hitEffectTex;
    float hitEffectTimer   = 0.0f;
    const float hitEffectDuracao = 0.25f;
};
        
RunContext runc;

// controla o combate entre player e inimigo
void BattleManager(float dt,Player& player, Enemy& inimigo, bool PlayerAtacar){
    player.tickAttackTimer(dt);
    inimigo.tickAttackTimer(dt);
 
    // tick dos timers de frame de animacao — zeram os flags depois do tempo visivel
    if (runc.timerPlayerAtacou > 0.0f) {
        runc.timerPlayerAtacou -= dt;
        if (runc.timerPlayerAtacou <= 0.0f) runc.Playerjaatacou = false;
    }
    if (runc.timerEnemyAtacou > 0.0f) {
        runc.timerEnemyAtacou -= dt;
        if (runc.timerEnemyAtacou <= 0.0f) runc.Enemyjaatacou = false;
    }
 
    // tick do efeito de hit do player
    if (runc.hitEffectTimer > 0.0f) runc.hitEffectTimer -= dt;
 
    // inicia o turno do player
    if (!runc.turnoEmAndamento && PlayerAtacar) {
        runc.playerHitsRestantes = max(1, (int)(1.0f / player.getAttackSpeed()));
        runc.enemyHitsRestantes = max(1, (int)(1.0f / inimigo.getAttackSpeed()));
 
        runc.turnoEmAndamento = true;
        runc.turnoInimigo = false;
 
        runc.Playerjaatacou = false;
        runc.Enemyjaatacou = false;
        runc.timerPlayerAtacou = 0.0f;
        runc.timerEnemyAtacou  = 0.0f;
 
        player.resetAttackTimer();
        inimigo.resetAttackTimer();
    }
 
    if (!runc.turnoEmAndamento) return;
 
    if (!runc.turnoInimigo) {
        if (player.getAttackTimer() >= 0.25f) {
            int dano = max(0, player.getDamage() + player.getAtributoforca() + bonuspocaodano - inimigo.getDefense());
 
            inimigo.setHealth(inimigo.getHealth() - dano);
 
            runc.Playerjaatacou = true;
            runc.Enemyjaatacou = false;
            runc.timerPlayerAtacou = runc.duracaoFrameAtaque;
            runc.timerEnemyAtacou  = 0.0f;
 
            // dispara o efeito de hit sobre o inimigo
            runc.hitEffectTimer = runc.hitEffectDuracao;
 
            runc.playerHitsRestantes--;
            player.resetAttackTimer();
 
            if (inimigo.getHealth() <= 0) {
                runc.turnoEmAndamento = false;
                return;
            }
 
            if (runc.playerHitsRestantes <= 0) {
                runc.turnoInimigo = true;
                inimigo.resetAttackTimer();
            }
        }
 
        return;
    }
 
    if (runc.turnoInimigo) {
        if (inimigo.getAttackTimer() >= 0.35f) {
            float def = (float)(player.getDefense() + player.getAtributoconstituicao());
            float reducao = def / (def + 33.3f);
 
            int dano = max(1, (int)(inimigo.getDamage() * (1.0f - reducao)));
 
            player.setLife(player.getLife() - dano);
 
            runc.Enemyjaatacou = true;
            runc.Playerjaatacou = false;
            runc.timerEnemyAtacou  = runc.duracaoFrameAtaque;
            runc.timerPlayerAtacou = 0.0f;
 
            runc.enemyHitsRestantes--;
            inimigo.resetAttackTimer();
 
            if (player.getLife() <= 0) {
                runc.turnoEmAndamento = false;
                return;
            }
 
            if (runc.enemyHitsRestantes <= 0) {
                runc.turnoEmAndamento = false;
                runc.turnoInimigo = false;
                // nao zeramos Playerjaatacou/Enemyjaatacou aqui — os timers cuidam disso
            }
        }
        return;
    }
}

std::vector<InimigoComp*> tier1 = {&RegularComp, &FastComp, &TankComp};
std::vector<InimigoComp*> tier2 = {&JuggernautComp, &ArcherComp, &NinjaComp};
std::vector<InimigoComp*> tier3 = {&ColossusComp, &KnightComp, &DefenderComp};
std::vector<InimigoComp*> tier4 = {&DragonComp};

// fases especiais geram inimigos mais fortes
InimigoComp* getRandomEnemy(int fase) {
    if(fase % 50 == 0 && fase > 0)return &DragonComp;
    else if((fase % 10)==0 && fase > 0)return tier3[GetRandomValue(0, tier3.size()-1)];
    else if((fase % 5)==0 &&  fase > 0)return tier2[GetRandomValue(0, tier2.size()-1)];
    else return tier1[GetRandomValue(0, tier1.size()-1)];
}


// retorna lista com todos os templates de item do jogo
std::vector<ItemTemplate*> getTodosItensDoJogo() {
        return {
            &espadacurta, &espadacurtaUC, &espadamedia, &espadamediaEP, &espadalonga,
            &facapequena, &facapequenaUC, &facarara, &facaEP, &facalend,
            &arcopeq, &arcopequUC, &arcorar, &arcoEP, &arcolend,
            &capacetecomum, &capaceteUC, &capaceterare, &capaceteEP, &capacetelegend,
            &coletecomum, &coleteUC, &coterare, &coteEP, &cotelegend,
            &cintocomum, &cintoUC, &cintorare, &cintoEP, &cintolend,
            &botascomum, &botasUC, &botasrare, &botasEP, &botaslegend,
            &anelocomum, &aneloUC, &anelorare, &aneloEP, &anelolend,

            &ingredientBase, &ingredienteDano, &ingredienteVida,
            &ingredienteSpeed, &ingredienteLuck, &ingredienteMult,

            &pocaoDano, &pocaoVida, &pocaoSpeed, &pocaoLuck, &pocaoMult
        };
    }

// spawna itens aleatorios baseado na dificuldade atual
void spawnRandomItems(b2WorldId world, std::vector<physicalObject>& TotalItems, int dificuldade) {
    std::vector<ItemTemplate*> todosItens = {
        &espadacurta, &espadacurtaUC, &espadamedia, &espadamediaEP, &espadalonga,
        &facapequena, &facapequenaUC, &facarara, &facaEP, &facalend,
        &arcopeq, &arcopequUC, &arcorar, &arcoEP, &arcolend,
        &capacetecomum, &capaceteUC, &capaceterare, &capaceteEP, &capacetelegend,
        &coletecomum, &coleteUC, &coterare, &coteEP, &cotelegend,
        &cintocomum, &cintoUC, &cintorare, &cintoEP, &cintolend,
        &botascomum, &botasUC, &botasrare, &botasEP, &botaslegend,
        &anelocomum, &aneloUC, &anelorare, &aneloEP, &anelolend
    };

    std::vector<ItemTemplate*> itensDisponiveis;
    for(ItemTemplate* item : todosItens){
    if(dificuldade == 5){
        itensDisponiveis.push_back(item);
    } else if(dificuldade == 4){
        if(item->itemData->item->getRarity() == 4){
            itensDisponiveis.push_back(item);
        }
    } else {
        if(item->itemData->item->getRarity() <= dificuldade){
            itensDisponiveis.push_back(item);
        }
    }
}
    int quantidadeSpawn = 1 * bonuspocaomult;
    for(int i = 0; i < quantidadeSpawn; i++){
        int idx = GetRandomValue(0, itensDisponiveis.size()-1);
        TotalItems.push_back(ItemGenerator(world, *itensDisponiveis[idx],
            screenWidth/2 + GetRandomValue(-200, 200),
            screenHeight/2 - 300,
            b2_dynamicBody));
    }
}

void spawnIngredients(b2WorldId world, std::vector<physicalObject>& TotalItems){
    std::vector<ItemTemplate*> todosIngredientes = {&ingredientBase,&ingredientBase,&ingredientBase,&ingredienteDano,&ingredienteVida,&ingredienteSpeed,&ingredienteLuck,&ingredienteMult};
    int quantidadeSpawn = 1 * bonuspocaomult;
    for(int i=0; i<quantidadeSpawn; i++){
        int idx = GetRandomValue(0, 7);
        TotalItems.push_back(ItemGenerator(world, *todosIngredientes[idx],
            screenWidth/2 + GetRandomValue(-200, 200),
            screenHeight/2 - 300,
            b2_dynamicBody));
    }
}

// inicializa sistema de inventario e mundo fisico
void inventory_init() {
    inv.openbackpackTex = LoadTexture("images/open backpack.png");
    inv.equipamentTab   = LoadTexture("images/tab.png");
    inv.backgroundimage = LoadImage("images/fundo.png");
    inv.accessoryslot = LoadTexture("images/inventory slot.png");
    inv.trash = LoadTexture("images/lixo.png");
    inv.bar1 = LoadTexture("images/bar 1.png");
    inv.painel1 = LoadTexture("images/painel.png");
    FonteBonita = LoadFontEx("Fonts/Fonte.ttf", 32, NULL, 0);
    SetTextureFilter(FonteBonita.texture, TEXTURE_FILTER_POINT);

    ImageFormat(&inv.backgroundimage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    inv.backgroundtexture = LoadTextureFromImage(inv.backgroundimage);
    ImageBlurGaussian(&inv.backgroundimage, 10);
    Color* pixels = LoadImageColors(inv.backgroundimage);
    UpdateTexture(inv.backgroundtexture, pixels);
    UnloadImageColors(pixels);
    
    
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 80};
    inv.world = b2CreateWorld(&worldDef);
    
    if(spawnedThisGame==false){
        spawnedThisGame=true;
        spawnRandomItems(inv.world, inv.TotalItems, 0);
        spawnRandomItems(inv.world, inv.TotalItems, 0);
        spawnRandomItems(inv.world, inv.TotalItems, 0);
    }

    inv.backpackScale   = 0.75f;
    inv.backpackCenterX = screenWidth / 2.0f - 10;
    inv.backpackCenterY = screenHeight / 2.0f - 25;
    inv.backpackW       = inv.openbackpackTex.width / 1.5f * inv.backpackScale;
    inv.backpackH       = inv.openbackpackTex.height * inv.backpackScale;
    
    inv.BackpackWalls.push_back(WallGenerator(inv.world, inv.backpackCenterX, inv.backpackCenterY + inv.backpackH*0.38f, inv.backpackW*0.95f, 10, b2_staticBody));
    inv.BackpackWalls.push_back(WallGenerator(inv.world, inv.backpackCenterX - inv.backpackW*0.46f, inv.backpackCenterY, 10, inv.backpackH*0.75f, b2_staticBody));
    inv.BackpackWalls.push_back(WallGenerator(inv.world, inv.backpackCenterX + inv.backpackW*0.46f, inv.backpackCenterY, 10, inv.backpackH*0.75f, b2_staticBody));
    
    
    // slots
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+450, screenHeight/2-200, false, 25,25,0,10, head});
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+450, screenHeight/2-75,  false, 25,25,0,10, chest});
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+450, screenHeight/2+25,  false, 25,25,0,10, waist});
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+600, screenHeight/2-125, false, 25,25,0,10, handright});
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+300, screenHeight/2-125, false, 25,25,0,10, handleft});
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+450, screenHeight/2+125, false, 25,25,0,10, feet});
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+575, screenHeight/2+50,  false, 25,25,0,10, accessory});
}

void inventory_draw() {
    ClearBackground(BLACK);
    DrawTexture(inv.backgroundtexture, 0, 0, WHITE);
    DrawTextureEx(inv.equipamentTab,
(Vector2){screenWidth/2 - (float)(inv.equipamentTab.width/4) + 420,
    screenHeight/2 - (float)(inv.equipamentTab.height/4) - 50},
    0, 0.6f, WHITE);
    DrawTextureEx(inv.openbackpackTex,
        (Vector2){screenWidth/2 - (float)(inv.openbackpackTex.width/4) - 150,
            screenHeight/2 - (float)(inv.openbackpackTex.height/4) - 150},
            0, inv.backpackScale, WHITE);
            
    DrawTextureEx(inv.accessoryslot,(Vector2){screenWidth/2+540, screenHeight/2+25},0,0.1,WHITE);
    DrawTextureEx(inv.trash, (Vector2){50,screenHeight-250}, 20, 0.4, WHITE);
    DrawTextureEx(inv.bar1, (Vector2){screenWidth/2+660,screenHeight/2-200}, 0, 0.2, WHITE);
    DrawTextureEx(inv.bar1, (Vector2){screenWidth/2+660,screenHeight/2-150}, 0, 0.2, WHITE);
    DrawTextureEx(inv.bar1, (Vector2){screenWidth/2+660,screenHeight/2-100}, 0, 0.2, WHITE);
    DrawTextureEx(inv.bar1, (Vector2){screenWidth/2+660,screenHeight/2-50}, 0, 0.2, WHITE);
    DrawTextureEx(inv.bar1, (Vector2){screenWidth/2+660,screenHeight/2}, 0, 0.2, WHITE);
    DrawTextureEx(inv.bar1, (Vector2){screenWidth/2+660,screenHeight/2+50}, 0, 0.2, WHITE);
    DrawTextureEx(inv.bar1, (Vector2){screenWidth/2+660,screenHeight/2+100}, 0, 0.2, WHITE);
    DrawTextureEx(inv.bar1, (Vector2){screenWidth/2+660,screenHeight/2+150}, 0, 0.2, WHITE);
    DrawTexturePro(inv.painel1,(Rectangle){0,0,1280,444},(Rectangle){0,screenHeight/2,1280/4,444/4},(Vector2){-1270,screenHeight/3},0,WHITE);
    DrawTextEx(FonteBonita,TextFormat("Fase Atual: %d",    runc.faseAtual),(Vector2){1320, screenHeight/3-140},30,3,(Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Dano: %d",    player.getDamage() + player.getAtributoforca() + bonuspocaodano),(Vector2){screenWidth/2+670, screenHeight/2-198},25,5,(Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Defesa: %d",  player.getDefense() + player.getAtributoconstituicao()),(Vector2){screenWidth/2+670, screenHeight/2-148},25,5,(Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Atk Spd: %.1f", player.getAttackSpeed()-bonuspocaospeed),(Vector2){screenWidth/2+670, screenHeight/2-98},25,4,(Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Forca:%d",player.getAtributoforca()),(Vector2){screenWidth/2+670, screenHeight/2-48},25,5,(Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Destreza:%d",player.getAtributodestreza()),(Vector2){screenWidth/2+670, screenHeight/2+4},25,3,(Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Vitalidade:%d",player.getAtributoconstituicao()),(Vector2){screenWidth/2+670, screenHeight/2+54},25,3,(Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Intelecto:%d",player.getAtributointeligencia()),(Vector2){screenWidth/2+670, screenHeight/2+104},25,3,(Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Peso: %.1f/%.1f",player.getCurrent_weight(),player.getWeight_Capacity()),(Vector2){screenWidth/2+670, screenHeight/2+154},20,5,(Color){45, 26, 14, 255});
    //DrawTextEx(FonteBonita,TextFormat("Sorte: %d",player.getAtributosorte()+bonuspocaosorte),(Vector2){screenWidth/2+670, screenHeight/2+200},25,5,(Color){45, 26, 14, 255});

    if(player.getunspentpoints()>0){
        for(int i=0;i<4;i++){
            DrawText(TextFormat("+"),  screenWidth/2+833, screenHeight/2-45+(i*50), 25, (Color){45, 26, 14, 255});
            //DrawRectangleRec((Rectangle){screenWidth/2+830, screenHeight/2-45+((float)i*50),15,15}, GREEN);
        }
    }

    // desenha todos os itens fisicos do inventario
    for(const physicalObject& body : inv.TotalItems){
        b2Rot rot = b2Body_GetRotation(body.bodyId);
        b2Vec2 pos = b2Body_GetPosition(body.bodyId);
        float x = pos.x * scale;
        float y = pos.y * scale;
        float angle = b2Rot_GetAngle(rot) * RAD2DEG;
        
        DrawTexturePro(
    body.templateData.itemPhysical->texture,
    (Rectangle){0, 0, (float)body.templateData.itemPhysical->texture.width,
    (float)body.templateData.itemPhysical->texture.height},
    (Rectangle){x, y, body.templateData.itemPhysical->visualWidth,
        body.templateData.itemPhysical->visualHeight},
        (Vector2){body.templateData.itemPhysical->visualWidth/2,
            body.templateData.itemPhysical->visualHeight/2},
            angle, WHITE
        );
    }
}
        
void run_init() {
    runc.itensEquipadosIds.clear();
    for(physicalObject& body : inv.TotalItems){
        if(body.isEquipped){
            runc.itensEquipadosIds.push_back(body.bodyId);
        }
    }
    
    runc.hitEffectTex = LoadTexture("images/attackSlash.png");
    runc.faseAtual++;
    runc.inimigo = getRandomEnemy(runc.faseAtual);
    runc.inimigo->Inimigo.setHealth(runc.inimigo->Inimigo.getHealthMax());
    runc.inimigo->Inimigo.resetAttackTimer();
    player.resetAttackTimer();
    runc.playerHitsRestantes = 0;
    runc.enemyHitsRestantes = 0;
    runc.turnoEmAndamento = false;
    runc.turnoInimigo = false;
    runc.Playerjaatacou = false;
    runc.Enemyjaatacou = false;
}

int descobrirSlotDoItem(physicalObject& item) {
    for (int i = 0; i < inv.SlotsEquipamentos.size(); i++) {
        if (B2_ID_EQUALS(inv.SlotsEquipamentos[i].equippedBodyId, item.bodyId)) {
            return i;
        }
    }

    return -1;
}

int descobrirItemId(const physicalObject& obj) {
    std::vector<ItemTemplate*> todosItens = getTodosItensDoJogo();

    for (int i = 0; i < todosItens.size(); i++) {
        if (obj.templateData.itemData == todosItens[i]->itemData &&
            obj.templateData.itemPhysical == todosItens[i]->itemPhysical) {
            return i;
        }
    }

    return -1;
}

void iniciarSaveManager() {
    try {
        SaveManager::getInstance();
        cout << "SaveManager iniciado com sucesso\n";
    } catch (const exception& erro) {
        cout << "Erro: " << erro.what() << "\n";
    }
}

// salva dados principais do jogo no sqlite
void SalvarJogo(){
    try {
        //Salva fase
        SaveManager::getInstance().salvarFase(runc.faseAtual);
        cout << "fase salva com sucesso";

        //Salva player
        SaveManager::getInstance().salvarPlayer(player,bonuspocaomult,bonuspocaosorte,bonuspocaospeed,bonuspocaodano,player.getunspentpoints());
        cout << "player salvo" << endl;

        //Limpa Itens
        SaveManager::getInstance().limparItens();
        
        //Salva Itens
        for (int i = 0; i < inv.TotalItems.size(); i++) {
            int itemId = descobrirItemId(inv.TotalItems[i]);

            if (itemId == -1) {
                cout << "item nao encontrado na lista de templates\n";
                continue;
            }

            int slotIndex = descobrirSlotDoItem(inv.TotalItems[i]);

            SaveManager::getInstance().salvarItens(i,itemId,inv.TotalItems[i],false);
        }
        cout << "itens salvos";

    } catch (const exception& erro) {
        cout << "erro ao salvar jogo: " << erro.what() << endl;
    }
}

void CarregarJogo(){
    try {
        //Carrega fase
        runc.faseAtual = SaveManager::getInstance().carregarFase();
        cout << "fase carregada: " << runc.faseAtual;

        //Carrega Player
        player.setDamage(5);
        player.setDefense(0);
        player.setAttackSpeed(1.0f);
        player.setBaseAttackSpeed(1.0f);
        SaveManager::getInstance().carregarPlayer(player,bonuspocaomult,bonuspocaosorte,bonuspocaospeed,bonuspocaodano);

        //Carrega Itens
        for (InventoryPivotPoint& ponto : inv.SlotsEquipamentos) {
            ponto.equippedBodyId = b2_nullBodyId;
        }
        std::vector<ItemTemplate*> todosItens = getTodosItensDoJogo();
        std::vector<ItemSaveData> itensSalvos = SaveManager::getInstance().carregarItens();
        
        for (physicalObject& item : inv.TotalItems) {
            if (b2Body_IsValid(item.bodyId)) {
                b2DestroyBody(item.bodyId);
            }
        }

        inv.TotalItems.clear();
        
        // recria itens do save usando templates salvos
        for (const ItemSaveData& itemSalvo : itensSalvos) {
            if (itemSalvo.deveriaApagar) {
                continue;
            }
        
            if (itemSalvo.itemId < 0 || itemSalvo.itemId >= todosItens.size()) {
                cout << "itemId invalido no save: " << itemSalvo.itemId << endl;
                continue;
            }
        
            physicalObject novoItem = ItemGenerator(
                inv.world,*todosItens[itemSalvo.itemId],itemSalvo.posX * scale,itemSalvo.posY * scale,b2_dynamicBody
            );
        
            b2Body_SetTransform(novoItem.bodyId,{itemSalvo.posX, itemSalvo.posY},b2MakeRot(itemSalvo.rotation)
            );
        
            novoItem.isEquipped = false;
            novoItem.wasEquipped = false;
        
            inv.TotalItems.push_back(novoItem);
        }
        
        spawnedThisGame = true;
    } catch(const exception& erro){
        cout << "erro ao carregar jogo: " << erro.what() << endl;
    }
}

void inventory_update(float dt) {
    b2World_Step(inv.world, dt, 4);
    
    
    if(IsKeyPressed(KEY_A)){runc.faseAtual--;}
    if(IsKeyPressed(KEY_D)){runc.faseAtual++;}
    
    if(IsKeyDown(KEY_I)){spawnRandomItems(inv.world, inv.TotalItems, 5);}
    if(IsKeyDown(KEY_K)){spawnIngredients(inv.world, inv.TotalItems);}
    if(IsKeyPressed(KEY_L)){
        player.setXp(player.getXp()-player.getxpfornextlevel());
        player.setunspentpoints(player.getunspentpoints()+1);
        player.setlevel(player.getLevel()+1);
        player.setxpfornextlevel(player.getxpfornextlevel()*1.5);

        cout << "LEVEL UP" << endl;
    }
    if (IsKeyPressed(KEY_S)) {
        SalvarJogo();
    }

    if (IsKeyPressed(KEY_H)) {
        CarregarJogo();
    }
    if(IsKeyPressed(KEY_C)){
        inv.TotalItems.erase(
            std::remove_if(inv.TotalItems.begin(), inv.TotalItems.end(),
            [](physicalObject& obj){
                if(!obj.isEquipped){
                    b2DestroyBody(obj.bodyId);
                    return true;
                }
                return false;
            }),
            inv.TotalItems.end()
        );
    }
    
    // calcula peso atual do inventario
    float pesoTotal=0;
    for(physicalObject& body : inv.TotalItems){
        if(!body.isEquipped){
            pesoTotal += body.templateData.itemData->item->getWeight();
        }
    }
    player.setcurrent_weight(pesoTotal);

    // sistema de distribuicao de pontos de atributo
    if(player.getunspentpoints()>0){
        Rectangle Mousepos = {(float)GetMouseX(),(float)GetMouseY(),5,5};
        for(int i=0;i<4;i++){
            if(CheckCollisionRecs(Mousepos, (Rectangle){screenWidth/2+830, screenHeight/2-45+((float)i*50),15,15})==true){
                if(IsMouseButtonPressed(MouseButton(0))){
                    player.setAtributosorte(player.getAtributosorte()+player.getLevel());
                    if(i==0){player.setAtributoforca(player.getAtributoforca()+1);}
                    if(i==1){player.setAtributodestreza(player.getAtributodestreza()+1);}
                    if(i==2){player.setAtributoconstituicao(player.getAtributoconstituicao()+1);}
                    if(i==3){player.setAtributointeligencia(player.getAtributointeligencia()+1);}
                    player.setunspentpoints(player.getunspentpoints()-1);
                    break;
                }
            }
        }
    }

    for(physicalObject& body : inv.TotalItems){
        grab(body);
        StatusUpdater(body);
        PotionCrafter(body);

        b2Vec2 pos = b2Body_GetPosition(body.bodyId);
        float jumpeffect = GetRandomValue(-70, -20);
        if(jumpeffect == -70) jumpeffect = -150;
        
        if(pos.y*scale >= screenHeight) b2Body_SetLinearVelocity(body.bodyId, {0, jumpeffect});
        if(pos.y*scale <= 0)            b2Body_SetLinearVelocity(body.bodyId, {0, -jumpeffect});
        if(pos.x*scale >= screenWidth)  b2Body_SetLinearVelocity(body.bodyId, {jumpeffect, 0});
        if(pos.x*scale <= 0)            b2Body_SetLinearVelocity(body.bodyId, {-jumpeffect, 0});
        
        Rectangle trashRect = {50, (float)screenHeight-250, inv.trash.width*0.4f, inv.trash.height*0.4f};

        // sistema de lixeira com timer segurando item em cima
        if(body.isGrabbed){
            b2Vec2 pos = b2Body_GetPosition(body.bodyId);
            float itemX = pos.x * scale;
            float itemY = pos.y * scale;
            
            bool sobreLixo = CheckCollisionPointRec({itemX, itemY}, trashRect);
            
            if(sobreLixo){
                inv.trashTimer += dt;
                inv.itemOnTrash = true;
            } else {
                inv.trashTimer = 0.0f;
                inv.itemOnTrash = false;
            }
            
            if(inv.trashTimer >= 2.0f){
                inv.trashTimer = 0.0f;
                inv.itemOnTrash = false;
                GrabbedObject = nullptr;
                body.isGrabbed = false;
                body.isEquipped = false;
                body.wasEquipped = false;
                b2DestroyBody(body.bodyId);
                inv.TotalItems.erase(
                    std::remove_if(inv.TotalItems.begin(), inv.TotalItems.end(),
                        [&body](const physicalObject& obj){
                            return B2_ID_EQUALS(obj.bodyId, body.bodyId);
                        }),
                    inv.TotalItems.end()
                );
                break;
            }
        }

        for(InventoryPivotPoint& ponto : inv.SlotsEquipamentos){
            PivotChecker(body, ponto);
        }
    }

    if(craftPendente){
        craftPendente = false;

        // aplica efeito da pocao craftada
        switch(craftT2){
            case 0: bonuspocaodano  = bonuspocaodano + 5 * player.getAtributointeligencia(); break;
            case 1: player.setLife(min(player.getLife_max(), player.getLife()+25+(10*player.getAtributointeligencia()))); break;
            case 2: bonuspocaospeed = bonuspocaospeed+player.getAtributointeligencia() / 15.0f; break;
            case 3: bonuspocaosorte = bonuspocaosorte+player.getAtributointeligencia() * 2; break;
            case 4: bonuspocaomult  = bonuspocaomult + 1 + player.getAtributointeligencia() / 5; break;
        }

        ItemTemplate* pocaoTemplate = nullptr;
        if(craftT2==0) pocaoTemplate = &pocaoDano;
        if(craftT2==1) pocaoTemplate = &pocaoVida;
        if(craftT2==2) pocaoTemplate = &pocaoSpeed;
        if(craftT2==3) pocaoTemplate = &pocaoLuck;
        if(craftT2==4) pocaoTemplate = &pocaoMult;
        if(pocaoTemplate) inv.TotalItems.push_back(ItemGenerator(inv.world, *pocaoTemplate, screenWidth/2, screenHeight/2-300, b2_dynamicBody));

        std::vector<b2BodyId> paraDestruir = {craftBodyT1, craftBodyT2};
        inv.TotalItems.erase(
            std::remove_if(inv.TotalItems.begin(), inv.TotalItems.end(),
                [&](physicalObject& obj){
                    for(b2BodyId id : paraDestruir)
                        if(B2_ID_EQUALS(obj.bodyId, id)) return true;
                    return false;
                }),
            inv.TotalItems.end()
        );
        for(b2BodyId id : paraDestruir) b2DestroyBody(id);

        craftBodyT1 = b2_nullBodyId;
        craftBodyT2 = b2_nullBodyId;
    }


        if(IsKeyPressed(KEY_SPACE)){
            run_init();
            currentgamestage = run;
        }
    }

void run_update(float dt) {
    if(runc.inimigo == nullptr) return;

    Rectangle mouseRec = (Rectangle){(float)GetMouseX(),(float)GetMouseY(),5,5};

    bool playerAtacar = CheckCollisionRecs(mouseRec,(Rectangle){940, screenHeight/2+365, 320, 100}) && IsMouseButtonPressed(0);

    BattleManager(dt, player, runc.inimigo->Inimigo, playerAtacar);
    
    if(player.getLife() <= 0){
    runc.faseAtual = 0;
    player.setLife(player.getLife_max());
    player.setDamage(5);
    player.setDefense(0);
    player.setAttackSpeed(1);

    for(physicalObject& body : inv.TotalItems){
        if(body.isEquipped){
            body.isEquipped = false;
            body.wasEquipped = false;
            b2Body_SetGravityScale(body.bodyId, 1.0f);
        }
    }

    for(b2BodyId id : runc.itensEquipadosIds){
        inv.TotalItems.erase(
            std::remove_if(inv.TotalItems.begin(), inv.TotalItems.end(),
                [id](const physicalObject& obj){
                    return B2_ID_EQUALS(obj.bodyId, id);
                }),
            inv.TotalItems.end()
        );
    }

    for(InventoryPivotPoint& ponto : inv.SlotsEquipamentos)
    ponto.equippedBodyId = b2_nullBodyId;
    runc.itensEquipadosIds.clear();

    if(player.getCurrent_weight()<player.getWeight_Capacity()){
        spawnRandomItems(inv.world, inv.TotalItems, 0);
    }

    std::vector<b2BodyId> pocoesParaDestruir;
    inv.TotalItems.erase(
        std::remove_if(inv.TotalItems.begin(), inv.TotalItems.end(),
            [&pocoesParaDestruir](physicalObject& obj){
                RPG::Potion* p = dynamic_cast<RPG::Potion*>(obj.templateData.itemData->item);
                if(p){
                    pocoesParaDestruir.push_back(obj.bodyId);
                    return true;
                }
                return false;
            }),
        inv.TotalItems.end()
    );
    for(b2BodyId id : pocoesParaDestruir) b2DestroyBody(id);

    bonuspocaomult=1;
    bonuspocaodano=0;
    bonuspocaospeed=0;
    bonuspocaosorte=0;

    runc.inimigo = nullptr;
    currentgamestage = inventory;
    return;
}
            
    if(runc.inimigo->Inimigo.getHealth() <= 0){
        player.setXp(player.getXp()+runc.inimigo->Inimigo.getxpvalue());

        if(player.getXp()>=player.getxpfornextlevel()){
            player.setXp(player.getXp()-player.getxpfornextlevel());
            player.setunspentpoints(player.getunspentpoints()+1);
            player.setlevel(player.getLevel()+1);
            player.setxpfornextlevel(player.getxpfornextlevel()*1.5);

            cout << "LEVEL UP" << endl;
        }

        int dif = runc.inimigo->Inimigo.getDifficulty();
        int quantidade = 1;
        if(dif == 1) quantidade = 1;
        if(dif == 2) quantidade = 2;
        if(dif == 3) quantidade = 3;
        if(dif == 4) quantidade = 1;
        
        for(int i=0; i<quantidade; i++){
            if(player.getCurrent_weight()<player.getWeight_Capacity()){
                spawnRandomItems(inv.world, inv.TotalItems, dif);
            }
        }

        int random = GetRandomValue(1, 100);
            if (random < (25+player.getAtributosorte() + bonuspocaosorte)){
                spawnIngredients(inv.world, inv.TotalItems);
            }

        std::vector<b2BodyId> pocoesParaDestruir;
        inv.TotalItems.erase(
            std::remove_if(inv.TotalItems.begin(), inv.TotalItems.end(),
                [&pocoesParaDestruir](physicalObject& obj){
                    RPG::Potion* p = dynamic_cast<RPG::Potion*>(obj.templateData.itemData->item);
                    if(p){
                        pocoesParaDestruir.push_back(obj.bodyId);
                        return true;
                    }
                    return false;
                }),
            inv.TotalItems.end()
        );
        for(b2BodyId id : pocoesParaDestruir) b2DestroyBody(id);

        bonuspocaomult=1;
        bonuspocaodano=0;
        bonuspocaospeed=0;
        bonuspocaosorte=0;

        runc.inimigo = nullptr;
        currentgamestage = inventory;
        return;
    }
}

void run_draw() {
    if(runc.inimigo == nullptr) return;

    ClearBackground(BLACK);
    DrawTexture(inv.backgroundtexture, 0, 0, WHITE);
    
    if(runc.Playerjaatacou==true){
        DrawTextureEx(runc.inimigo->texturaD, Vector2{screenWidth/2-(float)(runc.inimigo->texturaP.width/2)+300,screenHeight/2-(float)(runc.inimigo->texturaP.height/2)}, 0, 1, WHITE);
    } else if(runc.Enemyjaatacou==true){
        DrawTextureEx(runc.inimigo->texturaA, Vector2{screenWidth/2-(float)(runc.inimigo->texturaP.width/2)+300,screenHeight/2-(float)(runc.inimigo->texturaP.height/2)}, 0, 1, WHITE);
    } else{
        DrawTextureEx(runc.inimigo->texturaP, Vector2{screenWidth/2-(float)(runc.inimigo->texturaP.width/2)+300,screenHeight/2-(float)(runc.inimigo->texturaP.height/2)}, 0, 1, WHITE);
    }

    if(runc.hitEffectTimer > 0.0f && runc.hitEffectTex.id != 0){
        float progresso = runc.hitEffectTimer / runc.hitEffectDuracao;
        unsigned char alpha = (unsigned char)(progresso * 255);
        float escala = 1.0f + (1.0f - progresso) * 0.5f;
        float cx = screenWidth/2 + 300;
        float cy = screenHeight/2;
        float w  = runc.hitEffectTex.width  * escala;
        float h  = runc.hitEffectTex.height * escala;
        DrawTextureEx(runc.hitEffectTex,(Vector2){screenWidth/2,screenHeight/2-200},0,1.5,WHITE);
    }

    DrawTexturePro(inv.painel1,(Rectangle){0,445,1280,1024},(Rectangle){0,screenHeight/2,1280/2,1024/2},(Vector2){-100,screenHeight/4},0,WHITE);
    DrawTexturePro(inv.painel1,(Rectangle){0,0,1280,444},(Rectangle){0,screenHeight/2,1280/4,444/4},(Vector2){-940,screenHeight/2-900},0,WHITE);
    DrawTexturePro(inv.painel1,(Rectangle){0,0,1280,444},(Rectangle){0,screenHeight/2,1280/4,444/4},(Vector2){-1420,screenHeight/2-900},0,WHITE);
    DrawTextEx(FonteBonita,TextFormat("Atacar"),(Vector2){1030,screenHeight/2+400},  40,2, (Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Habilidades"),(Vector2){1465,screenHeight/2+400},  40,2, (Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Fase: %d",runc.faseAtual),(Vector2){365,282},  30,3, (Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("%s",runc.inimigo->Inimigo.getName().c_str()), (Vector2){365,330},  40,5, (Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("HP Player: %d",player.getLife()),(Vector2){160,390},  30,5, (Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Dano Player: %d",player.getDamage()+player.getAtributoforca()+bonuspocaodano),(Vector2){160,430}, 30,5, (Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Defesa Player: %d",player.getDefense()),(Vector2){160,470}, 30,5, (Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("HP Inimigo: %d",runc.inimigo->Inimigo.getHealth()),(Vector2){160,550}, 30,5, (Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Dano Inimigo: %.1f",runc.inimigo->Inimigo.getDamage()),(Vector2){160,590}, 30,5, (Color){45, 26, 14, 255});
    DrawTextEx(FonteBonita,TextFormat("Defesa Inimigo: %d",runc.inimigo->Inimigo.getDefense()),(Vector2){160,630}, 30,5, (Color){45, 26, 14, 255});
}

void menu_init(){
    iniciarSaveManager();
}

void menu_update(){
    inventory_init();
    currentgamestage=inventory;
}

void menu_draw(){
}


void config_update(){
    
}

void config_draw(){

}

                    
int main() {
    const int screenWidth  = 1280*1.5;
    const int screenHeight = 720*1.5;
    
    InitWindow(screenWidth, screenHeight, "long prep");
    SetTargetFPS(60);
    InitItemList();
    InitEnemyList();
    currentgamestage = menu;
    menu_init();
    
    while(!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        switch(currentgamestage) {
            case menu:      menu_update();        break;
            case inventory: inventory_update(dt); break;
            case run:       run_update(dt);       break;
            case config:    config_update();      break;
        }
        
        BeginDrawing();
        
        switch(currentgamestage) {
            case menu:      menu_draw();        break;
            case inventory: inventory_draw();   break;
            case run:       run_draw();         break;
            case config:    config_draw();      break;
        }

        EndDrawing();
    }

    b2DestroyWorld(inv.world);
    CloseWindow();
    return 0;
}