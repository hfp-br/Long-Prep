#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include "item.h"
#include "itemlist.h"
#include <asm-generic/errno.h>
#include <raylib.h>
#include <box2d/box2d.h>
#include <cmath>
#include <iostream>
#include <vector>

#define scale 10

bool MousePressed = false;
physicalObject* GrabbedObject = nullptr;

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
        }
    }
    
    if(GrabbedObject == nullptr && b2Shape_TestPoint(body.shapeId, mousePoint)){
        if(IsMouseButtonDown(0)){
            GrabbedObject = &body;
        }
    }
    
    if(GrabbedObject == &body){
        b2Vec2 direction = {mousePoint.x - pos.x, mousePoint.y - pos.y};
        b2Vec2 speed = {direction.x * (body.templateData.itemData->item->getWeight()*10), direction.y * (body.templateData.itemData->item->getWeight()*10)};
        
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

int main()
{
    //seta o tamanho da tela
    const int screenWidth = 1280*1.5;
    const int screenHeight = 720*1.5;
    
    
    //nome da janela e FPS
    InitWindow(screenWidth, screenHeight, "long prep");
    SetTargetFPS(60);
    InitItemList();
    
    Texture2D openbackpackTex = LoadTexture("images/open backpack.png");
    Texture2D equipamentTab = LoadTexture("images/tab.png");
    Image backgroundimage = LoadImage("images/fundo.png");
    ImageFormat(&backgroundimage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Texture2D backgroundtexture = LoadTextureFromImage(backgroundimage);

    if(true){
        ImageBlurGaussian(&backgroundimage, 10);
    }

    Color *pixels = LoadImageColors(backgroundimage); 
    UpdateTexture(backgroundtexture, pixels);
    UnloadImageColors(pixels);

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 20};
    b2WorldId world = b2CreateWorld(&worldDef);
    
    float backpackCenterX = screenWidth / 2.0f-10;
    float backpackCenterY = screenHeight / 2.0f-25;
    float backpackScale = 0.75;

    float backpackW = openbackpackTex.width/1.5 * backpackScale;
    float backpackH = openbackpackTex.height * backpackScale;

    std::vector<physicalObject> BackpackWalls;
    BackpackWalls.push_back(WallGenerator(world, backpackCenterX, backpackCenterY + backpackH*0.38f, backpackW*0.95f, 10, b2_staticBody));   // chão
    BackpackWalls.push_back(WallGenerator(world, backpackCenterX - backpackW*0.46f, backpackCenterY, 10, backpackH*0.75f, b2_staticBody));   // parede esq
    BackpackWalls.push_back(WallGenerator(world, backpackCenterX + backpackW*0.46f, backpackCenterY, 10, backpackH*0.75f, b2_staticBody));   // parede dir
    
    
    std::vector<physicalObject> TotalItems;
    for(int i=0; i<5; i++){
        TotalItems.push_back(ItemGenerator(world, cuboslime, (screenWidth/2), screenHeight/2-400, b2_dynamicBody));
    }   
    TotalItems.push_back(ItemGenerator(world, espadacurta, (screenWidth/2)+(2*50)-50, screenHeight/2-100, b2_dynamicBody));
    TotalItems.push_back(ItemGenerator(world, pocaomisteriosa, (screenWidth/2+150), screenHeight/2-400, b2_dynamicBody));
    
    
    
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        b2World_Step(world, dt, 4);
        
        for(physicalObject& body : TotalItems){
            grab(body);
        }
        
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(backgroundtexture,0,0,WHITE);
        DrawTextureEx(equipamentTab, (Vector2){screenWidth/2-(float)(equipamentTab.width/4)+420,screenHeight/2-(float)(equipamentTab.height/4)-50}, 0, 0.6, WHITE);
        DrawTextureEx(openbackpackTex, (Vector2){screenWidth/2-(float)(openbackpackTex.width/4)-150,screenHeight/2-(float)(openbackpackTex.height/4)-150}, 0, backpackScale, WHITE);
        
        /*
        for (const physicalObject& body : BackpackWalls) {
            b2Vec2 pos = b2Body_GetPosition(body.bodyId);
            float x = pos.x * scale, y = pos.y * scale;
            DrawRectangle(
                x - body.wallData.width/2,
                y - body.wallData.height/2,
                body.wallData.width,
                body.wallData.height,
                RED
            );
        }
        */
        
        
        
        
        for (const physicalObject& body : TotalItems) {
            b2Rot rot = b2Body_GetRotation(body.bodyId);
            b2Vec2 pos = b2Body_GetPosition(body.bodyId);
            float x = pos.x * scale;
            float y = pos.y * scale;

            float angle = b2Rot_GetAngle(rot) * RAD2DEG;
            float w = body.templateData.itemPhysical->width;
            float h = body.templateData.itemPhysical->height;

            Texture2D tex = body.templateData.itemPhysical->texture;
            
            
            DrawTexturePro(
                body.templateData.itemPhysical->texture,
                (Rectangle){0, 0, (float)body.templateData.itemPhysical->texture.width, 
                (float)body.templateData.itemPhysical->texture.height},
                (Rectangle){x, y, body.templateData.itemPhysical->visualWidth,
                                body.templateData.itemPhysical->visualHeight},
                (Vector2){body.templateData.itemPhysical->visualWidth/2, body.templateData.itemPhysical->visualHeight/2},
                angle,
                WHITE
            );
        }
        EndDrawing();
    }

    b2DestroyWorld(world);
    CloseWindow();
    return 0;
}