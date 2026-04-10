#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include "enemy.h"
#include "item.h"
#include "itemlist.h"
#include "Equipament.h"
#include "player.h"
#include <asm-generic/errno.h>
#include <concepts>
#include <raylib.h>
#include <box2d/box2d.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <time.h>
#include "enemylist.h"
#define scale 10
using namespace std;




typedef enum GameStage{menu,config,inventory,run};
GameStage currentgamestage;
const int screenWidth = 1280*1.5;
const int screenHeight = 720*1.5;
bool MousePressed = false;
physicalObject* GrabbedObject = nullptr;
Player player("hero", 100, 100, 5, 10.0f, true, true, 0);

void BattleManager(float dt, Player& player, Enemy& inimigo){
    player.tickAttackTimer(dt);
    inimigo.tickAttackTimer(dt);

    if(inimigo.getAttackTimer() > inimigo.getAttackSpeed()){
        inimigo.resetAttackTimer();
        int dano = max(0, (int)inimigo.getDamage() - player.getDefense());
        player.setLife(player.getLife() - dano);
        cout << "Inimigo atacou! HP player: " << player.getLife() << endl;
    }

    if(player.getAttackTimer() > player.getAttackSpeed()){
        player.resetAttackTimer();
        int dano = max(0, player.getDamage() - inimigo.getDefense());
        inimigo.setHealth(inimigo.getHealth() - dano);
        cout << "Player atacou! HP inimigo: " << inimigo.getHealth() << endl;
    }
}

void StatusUpdater(physicalObject& body){
    if(body.isEquipped && !body.wasEquipped){
        Item* item = body.templateData.itemData->item;
        
        Weapon* w = dynamic_cast<Weapon*>(item);
        if(w) player.setDamage(player.getDamage() + w->getDamage());
        if(w) player.setAttackSpeed(w->getAttackSpeed());
        
        Armor* a = dynamic_cast<Armor*>(item);
        if(a) player.setDefense(player.getDefense() + a->getDefense());
    }
    
    if(!body.isEquipped && body.wasEquipped){
        Item* item = body.templateData.itemData->item;
        
        Weapon* w = dynamic_cast<Weapon*>(item);
        if(w) player.setDamage(player.getDamage() - w->getDamage());
        if(w) player.setAttackSpeed(1);
        
        Armor* a = dynamic_cast<Armor*>(item);
        if(a) player.setDefense(player.getDefense() - a->getDefense());
    }

    body.wasEquipped = body.isEquipped;
}

//gerador rapido de paredes
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
        Item.shapeId = b2CreatePolygonShape(bodyId, &bodyshapeDef, &bodyBox); // só uma vez
    } else {
        b2Circle circle;
        circle.center = {0.0f, 0.0f};
        circle.radius = templ.itemPhysical->radius/scale;
        b2ShapeDef ballshapeDef = b2DefaultShapeDef();
        ballshapeDef.filter.categoryBits = CAT_ITEM;
        ballshapeDef.filter.maskBits = CAT_PAREDE | CAT_ITEM;
        ballshapeDef.density = 1.0f;
        ballshapeDef.density = 1.0f;
        Item.shapeId = b2CreateCircleShape(bodyId, &ballshapeDef, &circle); // só uma vez
    }

    Item.isWall = false;
    Item.isGrabbed = false;
    Item.templateData.itemPhysical = templ.itemPhysical;
    Item.templateData.itemData = templ.itemData;
    Item.bodyId = bodyId;
    return Item;
}

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
        }
    }
    
    if(GrabbedObject == &body){
        b2Vec2 direction = {mousePoint.x - pos.x, mousePoint.y - pos.y};
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

void PivotChecker(physicalObject& body, InventoryPivotPoint& ponto){
    if(GrabbedObject == &body) return;

    if(body.templateData.itemPhysical->categoria == ponto.category && body.templateData.itemData->item->isEquipable()==true){
        b2Vec2 itemPos = b2Body_GetPosition(body.bodyId);
        float itemX = itemPos.x * scale;
        float itemY = itemPos.y * scale;
        float pontoX = ponto.x + ponto.width / 2.0f;
        float pontoY = ponto.y + ponto.height / 2.0f;
        float distance = sqrt(pow(pontoX - itemX, 2) + pow(pontoY - itemY, 2));

        if(distance >= 100){
            if(ponto.equippedItem == &body){
                ponto.equippedItem = nullptr;
            }
            body.isEquipped = false;
            b2Body_SetGravityScale(body.bodyId, 1.0f);
            return;
        }

        if(ponto.equippedItem != nullptr && ponto.equippedItem != &body) return;

        ponto.equippedItem = &body;
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
}

void spawnRandomItems(b2WorldId world, std::vector<physicalObject>& TotalItems) {
    float cx = screenWidth / 2.0f;
    float cy = screenHeight / 2.0f;

    // lista de todos os itens
    std::vector<ItemTemplate*> todosItens = {
        // espadas
        //&espadacurta, &espadacurtaUC, &espadamedia, &espadamediaEP, &espadalonga,
        // facas
        //&facapequena, &facapequenaUC, &facarara, &facaEP, &facalend,
        // arcos
        //&arcopeq, &arcopequUC, &arcorar, &arcoEP, &arcolend,
        // capacetes
        //&capacetecomum, &capaceteUC, &capaceterare, &capaceteEP, &capacetelegend,
        // peitorais
        //&coletecomum, &coleteUC, &coterare, &coteEP, &cotelegend,
        // cinturas
        //&cintocomum, &cintoUC, &cintorare, &cintoEP, &cintolend,
        // botas
        //&botascomum, &botasUC, &botasrare, &botasEP, &botaslegend,
        // acessórios
        //&anelocomum, &aneloUC, &anelorare, &aneloEP, &anelolend
    };

    int colunas = 8;
    float espacoX = 150.0f;
    float espacoY = 200.0f;
    float startX = cx - (colunas / 2.0f) * espacoX;
    float startY = 0;

    for(int i = 0; i < (int)todosItens.size(); i++){
        float x = startX + (i % colunas) * espacoX;
        float y = startY + (i / colunas) * espacoY;
        TotalItems.push_back(ItemGenerator(world, *todosItens[i], x, y, b2_dynamicBody));
    }
}


struct InventoryContext {
    Texture2D openbackpackTex;
    Texture2D equipamentTab;
    Texture2D backgroundtexture;
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
};

InventoryContext inv;

void inventory_init() {
    inv.openbackpackTex = LoadTexture("images/open backpack.png");
    inv.equipamentTab   = LoadTexture("images/tab.png");
    inv.backgroundimage = LoadImage("images/fundo.png");
    ImageFormat(&inv.backgroundimage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    inv.backgroundtexture = LoadTextureFromImage(inv.backgroundimage);
    ImageBlurGaussian(&inv.backgroundimage, 10);
    Color* pixels = LoadImageColors(inv.backgroundimage);
    UpdateTexture(inv.backgroundtexture, pixels);
    UnloadImageColors(pixels);
    
    
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 80};
    inv.world = b2CreateWorld(&worldDef);
    
    spawnRandomItems(inv.world, inv.TotalItems);
    inv.backpackScale   = 0.75f;
    inv.backpackCenterX = screenWidth / 2.0f - 10;
    inv.backpackCenterY = screenHeight / 2.0f - 25;
    inv.backpackW       = inv.openbackpackTex.width / 1.5f * inv.backpackScale;
    inv.backpackH       = inv.openbackpackTex.height * inv.backpackScale;
    
    inv.BackpackWalls.push_back(WallGenerator(inv.world, inv.backpackCenterX, inv.backpackCenterY + inv.backpackH*0.38f, inv.backpackW*0.95f, 10, b2_staticBody));
    inv.BackpackWalls.push_back(WallGenerator(inv.world, inv.backpackCenterX - inv.backpackW*0.46f, inv.backpackCenterY, 10, inv.backpackH*0.75f, b2_staticBody));
    inv.BackpackWalls.push_back(WallGenerator(inv.world, inv.backpackCenterX + inv.backpackW*0.46f, inv.backpackCenterY, 10, inv.backpackH*0.75f, b2_staticBody));
    
    // itens
    //inv.TotalItems.push_back(ItemGenerator(inv.world, cuboslime, screenWidth/2, screenHeight/2-400, b2_dynamicBody));
    
    
    // slots
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+450, screenHeight/2-200, false, 25,25,0,10, head});
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+450, screenHeight/2-75,  false, 25,25,0,10, chest});
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+450, screenHeight/2+25,  false, 25,25,0,10, waist});
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+600, screenHeight/2-125, false, 25,25,0,10, hand});
    inv.SlotsEquipamentos.push_back((InventoryPivotPoint){screenWidth/2+300, screenHeight/2-125, false, 25,25,0,10, hand});
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
                    
                    DrawText(TextFormat("Dano: %d",   player.getDamage()),  10, 10, 20, RED);
                    DrawText(TextFormat("Defesa: %d", player.getDefense()), 10, 35, 20, BLUE);
                    DrawText("SPACE para iniciar run", 10, 60, 20, DARKGRAY);
                    
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
        
        
        struct RunContext {
            int faseAtual = 0;
            int contadorfases = 0;
            Enemy* inimigo = nullptr;
        };
        
        RunContext runc;
        
        std::vector<Enemy*> tier1 = {&Regular, &Fast, &Tank};
        std::vector<Enemy*> tier2 = {&Juggernaut, &Archer, &Ninja};
        std::vector<Enemy*> tier3 = {&Colossus, &Knight, &Defender};
        std::vector<Enemy*> tier4 = {&Dragon};
        
        Enemy* getRandomEnemy(int fase) {
            if(fase == 50)return &Dragon;
            else if((fase % 10)==0)return tier3[GetRandomValue(0, tier3.size()-1)];
            else if((fase % 5)==0)return tier2[GetRandomValue(0, tier2.size()-1)];
            else return tier1[GetRandomValue(0, tier1.size()-1)];
        }
        
        void run_init() {
            runc.faseAtual++;
            runc.inimigo = getRandomEnemy(runc.faseAtual);
            runc.inimigo->setHealth(runc.inimigo->getHealthMax());
            runc.inimigo->resetAttackTimer();
            player.resetAttackTimer();
        }
        
        void inventory_update(float dt) {
            b2World_Step(inv.world, dt, 4);
            
            for(physicalObject& body : inv.TotalItems){
                grab(body);
                StatusUpdater(body);
                
                b2Vec2 pos = b2Body_GetPosition(body.bodyId);
                float jumpeffect = GetRandomValue(-70, -20);
                if(jumpeffect == -70) jumpeffect = -150;
                
                if(pos.y*scale >= screenHeight) b2Body_SetLinearVelocity(body.bodyId, {0, jumpeffect});
                if(pos.y*scale <= 0)            b2Body_SetLinearVelocity(body.bodyId, {0, -jumpeffect});
                if(pos.x*scale >= screenWidth)  b2Body_SetLinearVelocity(body.bodyId, {jumpeffect, 0});
                if(pos.x*scale <= 0)            b2Body_SetLinearVelocity(body.bodyId, {-jumpeffect, 0});
                
                for(InventoryPivotPoint& ponto : inv.SlotsEquipamentos)
                PivotChecker(body, ponto);
        }
        
            if(IsKeyPressed(KEY_SPACE)){
                run_init();
                currentgamestage = run;
            }
        }

        void run_update(float dt) {
            if(runc.inimigo == nullptr) return;
            
            BattleManager(dt, player, *runc.inimigo);
            
            if(player.getLife() <= 0){
                runc.faseAtual = 0;
                player.setLife(player.getLife_max());
                currentgamestage = menu;
                return;
            }
            
    if(runc.inimigo->getHealth() <= 0){
        currentgamestage = inventory;
        return;
    }

    if(IsKeyPressed(KEY_ESCAPE)){
        currentgamestage = inventory;
    }
}

void run_draw() {
    if(runc.inimigo == nullptr) return;

    ClearBackground(BLACK);
    DrawText(TextFormat("Fase: %d",       runc.faseAtual),                  10, 10,  20, YELLOW);
    DrawText(TextFormat("Inimigo: %s",    runc.inimigo->getName().c_str()), 10, 35,  25, WHITE);
    DrawText(TextFormat("HP Player: %d",  player.getLife()),                 10, 70,  30, GREEN);
    DrawText(TextFormat("HP Inimigo: %d", runc.inimigo->getHealth()),        10, 110, 30, RED);
    DrawText(TextFormat("Dano: %d",       player.getDamage()),               10, 150, 20, WHITE);
    DrawText(TextFormat("Defesa: %d",     player.getDefense()),              10, 175, 20, WHITE);
    DrawText(TextFormat("Attack Speed: %.1f", player.getAttackSpeed()),      10, 200, 20, WHITE);
    DrawText("ESC para voltar ao inventario", 10, screenHeight-30, 20, DARKGRAY);
}
                    
                    
int main() {
    const int screenWidth  = 1280*1.5;
    const int screenHeight = 720*1.5;
    
    InitWindow(screenWidth, screenHeight, "long prep");
    SetTargetFPS(60);
    InitItemList();
    
    currentgamestage = inventory;
    inventory_init();
    
    while(!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        switch(currentgamestage) {
            case menu:                            break;
            case inventory: inventory_update(dt); break;
            case run:       run_update(dt);       break;
            case config:                          break;
        }
        
        BeginDrawing();
        
        switch(currentgamestage) {
            case menu:                          break;
            case inventory: inventory_draw();   break;
            case run:       run_draw();         break;
            case config:                        break;
        }

        EndDrawing();
    }

    b2DestroyWorld(inv.world);
    CloseWindow();
    return 0;
}