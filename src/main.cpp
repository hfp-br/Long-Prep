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
    Parede.templateData.itemPhysical.width = width;
    Parede.templateData.itemPhysical.height = height;
    Parede.bodyId = bodyId;

    return Parede;
}

physicalObject ItemGenerator(b2WorldId world, ItemTemplate& templ,float xP, float yP, enum b2BodyType type){ 
    b2BodyDef bodyDef = b2DefaultBodyDef(); //definebody 
    bodyDef.position = {(xP)/scale, (yP)/scale}; //define posicao inicial 
    bodyDef.type = type;
    b2BodyId bodyId = b2CreateBody(world, &bodyDef); //cria o "perfil" no mundo 
    if(!templ.itemPhysical.isCircle){
        b2Polygon bodyBox = b2MakeBox((templ.itemPhysical.width/2)/scale, (templ.itemPhysical.height/2)/scale); //cria uma caixa com o tamanho definido 
        b2ShapeDef bodyshapeDef = b2DefaultShapeDef(); //coloca o formato como quadrado padrao do box2d 
        bodyshapeDef.density = 1.0f;
        b2CreatePolygonShape(bodyId, &bodyshapeDef, &bodyBox); //aplica o formato e a caixa em um poligono 
    } else {
        b2Circle circle;
        circle.center = {0.0f, 0.0f};
        circle.radius = templ.itemPhysical.radius/scale;
        b2ShapeDef ballshapeDef = b2DefaultShapeDef();
        ballshapeDef.density = 1.0f;
        b2CreateCircleShape(bodyId, &ballshapeDef, &circle);
    }
    physicalObject Item;
    Item.templateData.itemPhysical.width = templ.itemPhysical.width;
    Item.templateData.itemPhysical.height = templ.itemPhysical.height;
    Item.templateData.itemPhysical.radius = templ.itemPhysical.radius;
    Item.bodyId = bodyId;

    return Item;
}

void Grab(physicalObject& body,float reverseWeight){
    Rectangle mouseHitbox = (Rectangle){(float)GetMouseX()/scale,(float)GetMouseY()/scale,5,5};

    b2Vec2 pos = b2Body_GetPosition(body.bodyId);

    float x = pos.x * scale;
    float y = pos.y * scale;

    b2Vec2 direction;
    direction.x = mouseHitbox.x - pos.x;
    direction.y = mouseHitbox.y - pos.y;

    b2Vec2 speed;
    speed.x = direction.x * reverseWeight;
    speed.y = direction.y * reverseWeight;

    if(MousePressed==true){
        b2Body_SetLinearVelocity(body.bodyId, speed);
    }

    if(IsMouseButtonUp(0)){
            MousePressed=false;
    }

    if(CheckCollisionCircleRec((Vector2){pos.x,pos.y}, body.templateData.itemPhysical.radius/scale, mouseHitbox)){
        if(IsMouseButtonDown(0)){
            MousePressed=true;

        }
        if(IsMouseButtonUp(0)){
            MousePressed=false;
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


    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 20};
    b2WorldId world = b2CreateWorld(&worldDef);

    std::vector<physicalObject> BackpackWalls;
    BackpackWalls.push_back(WallGenerator(world, screenWidth/2, screenHeight/2+275, 400, 10,b2_staticBody));
    BackpackWalls.push_back(WallGenerator(world, screenWidth/2-135, screenHeight/2+100, 10, 400,b2_staticBody));
    BackpackWalls.push_back(WallGenerator(world, screenWidth/2+180, screenHeight/2+100, 10, 400,b2_staticBody));
    

    std::vector<physicalObject> TotalItems;
    for(int i=0; i<5; i++){
        TotalItems.push_back(ItemGenerator(world, espadacurta, (screenWidth/2)+(i*50)-50, screenHeight/2-100, b2_dynamicBody));
    }
    
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        b2World_Step(world, dt, 4);
        
        for(physicalObject& body : TotalItems){
            Grab(body, 15);
        }

        BeginDrawing();
        ClearBackground(WHITE);
        
        for(const physicalObject& body: BackpackWalls){
            b2Vec2 pos = b2Body_GetPosition(body.bodyId);

            float x = pos.x * scale;
            float y = pos.y * scale;

            DrawRectangle(x - body.templateData.itemPhysical.width/2, y - body.templateData.itemPhysical.height/2, 
                body.templateData.itemPhysical.width, body.templateData.itemPhysical.height, RED);
        }


        for(const physicalObject& body: TotalItems){
            b2Vec2 pos = b2Body_GetPosition(body.bodyId);
            b2Rot rot = b2Body_GetRotation(body.bodyId);

            float x = pos.x * scale;
            float y = pos.y * scale;
            float angle = b2Rot_GetAngle(rot) * RAD2DEG;

            float width = body.templateData.itemPhysical.width;
            float height = body.templateData.itemPhysical.height;

            DrawRectanglePro(
                (Rectangle){ x, y, width, height },
                (Vector2){ width / 2.0f, height / 2.0f },
                angle,
                GREEN
            );
        }

        EndDrawing();
    }

    b2DestroyWorld(world);
    CloseWindow();
    return 0;
}