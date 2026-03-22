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
    b2CreatePolygonShape(bodyId, &bodyshapeDef, &bodyBox); //aplica o formato e a caixa em um poligono 
    physicalObject Parede;
    Parede.isWall = true;
    Parede.wallData = {(Texture2D){1},(float)width, (float)height, 0, false};
    Parede.bodyId = bodyId;
    return Parede;

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
        bodyshapeDef.density = 1.0f;
        Item.shapeId = b2CreatePolygonShape(bodyId, &bodyshapeDef, &bodyBox); // só uma vez
    } else {
        b2Circle circle;
        circle.center = {0.0f, 0.0f};
        circle.radius = templ.itemPhysical->radius/scale;
        b2ShapeDef ballshapeDef = b2DefaultShapeDef();
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
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    
    //nome da janela e FPS
    InitWindow(screenWidth, screenHeight, "long prep");
    SetTargetFPS(60);
    InitItemList();
    
    
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 20};
    b2WorldId world = b2CreateWorld(&worldDef);
    
    std::vector<physicalObject> BackpackWalls;
    BackpackWalls.push_back(WallGenerator(world, screenWidth/2, screenHeight/2+275, 400, 10,b2_staticBody));
    BackpackWalls.push_back(WallGenerator(world, screenWidth/2-135, screenHeight/2+100, 10, 400,b2_staticBody));
    BackpackWalls.push_back(WallGenerator(world, screenWidth/2+180, screenHeight/2+100, 10, 400,b2_staticBody));
    
    
    std::vector<physicalObject> TotalItems;
    for(int i=0; i<5; i++){
        TotalItems.push_back(ItemGenerator(world, cuboslime, (screenWidth/2), screenHeight/2-400, b2_dynamicBody));
    }   
    TotalItems.push_back(ItemGenerator(world, espadacurta, (screenWidth/2)+(2*50)-50, screenHeight/2-100, b2_dynamicBody));
    TotalItems.push_back(ItemGenerator(world, pocaomisteriosa, (screenWidth/2+200), screenHeight/2-400, b2_dynamicBody));
    
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        b2World_Step(world, dt, 4);
        
        for(physicalObject& body : TotalItems){
            grab(body);
        }

        BeginDrawing();
        ClearBackground(WHITE);
        
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