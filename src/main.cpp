#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include <raylib.h>
#include <box2d/box2d.h>
#include <cmath>
#include <iostream>
#include <vector>

#define scale 10

bool MousePressed = false;

//struct para guardar qual objeto tem qual tamanho (usado para rendering)
typedef struct {
    float width;
    float height;
    float radius;
    char itemType[30];
    b2BodyId id;
} physicalObject;

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
    Parede.width = width;
    Parede.height = height;
    Parede.id = bodyId;

    return Parede;
}

physicalObject ItemGenerator(b2WorldId world, bool isCircle ,float xP, float yP,float width, float height, float radius, enum b2BodyType type){ 
    b2BodyDef bodyDef = b2DefaultBodyDef(); //definebody 
    bodyDef.position = {(xP)/scale, (yP)/scale}; //define posicao inicial 
    bodyDef.type = type;
    b2BodyId bodyId = b2CreateBody(world, &bodyDef); //cria o "perfil" no mundo 
    if(!isCircle){
        b2Polygon bodyBox = b2MakeBox((width/2)/scale, (height/2)/scale); //cria uma caixa com o tamanho definido 
        b2ShapeDef bodyshapeDef = b2DefaultShapeDef(); //coloca o formato como quadrado padrao do box2d 
        bodyshapeDef.density = 1.0f;
        b2CreatePolygonShape(bodyId, &bodyshapeDef, &bodyBox); //aplica o formato e a caixa em um poligono 
    } else {
        b2Circle circle;
        circle.center = {0.0f, 0.0f};
        circle.radius = radius/scale;
        b2ShapeDef ballshapeDef = b2DefaultShapeDef();
        ballshapeDef.density = 1.0f;
        b2CreateCircleShape(bodyId, &ballshapeDef, &circle);
    }
    physicalObject Item;
    Item.width = width;
    Item.height = height;
    Item.radius = radius;
    Item.id = bodyId;

    return Item;
}

void Grab(physicalObject body,float reverseWeight){
    Rectangle mouseHitbox = (Rectangle){(float)GetMouseX()/scale,(float)GetMouseY()/scale,5,5};

    b2Vec2 pos = b2Body_GetPosition(body.id);

    float x = pos.x * scale;
    float y = pos.y * scale;

    b2Vec2 direction;
    direction.x = mouseHitbox.x - pos.x;
    direction.y = mouseHitbox.y - pos.y;

    b2Vec2 speed;
    speed.x = direction.x * reverseWeight;
    speed.y = direction.y * reverseWeight;

    if(MousePressed==true){
        b2Body_SetLinearVelocity(body.id, speed);
    }

    if(CheckCollisionCircleRec((Vector2){pos.x,pos.y}, body.radius/scale, mouseHitbox)){
        if(IsMouseButtonDown(0)){
            MousePressed=true;
        }
        else{
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
    worldDef.gravity = {0.0f, 9.8f};
    b2WorldId world = b2CreateWorld(&worldDef);

    std::vector<physicalObject> BackpackWalls;
    BackpackWalls.push_back(WallGenerator(world, screenWidth/2, screenHeight/2+275, 400, 10,b2_staticBody));
    BackpackWalls.push_back(WallGenerator(world, screenWidth/2-135, screenHeight/2+100, 10, 400,b2_staticBody));
    BackpackWalls.push_back(WallGenerator(world, screenWidth/2+180, screenHeight/2+100, 10, 400,b2_staticBody));
    
    physicalObject ball = ItemGenerator(world, true, screenWidth/2, screenHeight/2-100, 0, 0, 10, b2_dynamicBody);
    
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        b2World_Step(world, dt, 4);
        
        Grab(ball,10);

        BeginDrawing();
        ClearBackground(WHITE);
        
        for(const physicalObject& body: BackpackWalls){
            b2Vec2 pos = b2Body_GetPosition(body.id);

            float x = pos.x * scale;
            float y = pos.y * scale;

            DrawRectangle(x - body.width/2, y - body.height/2, body.width, body.height, RED);
        }

        for(int i=0; i<1; i++){
            b2Vec2 pos = b2Body_GetPosition(ball.id);
    
            float x = pos.x * scale;
            float y = pos.y * scale;
    
            DrawCircle(x, y, ball.radius, GREEN);
        }

        EndDrawing();
    }

    b2DestroyWorld(world);
    CloseWindow();
    return 0;
}