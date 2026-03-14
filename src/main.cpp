#include "box2d/id.h"
#include "box2d/math_functions.h"
#include <raylib.h>
#include <box2d/box2d.h>
#include <cmath>
#include <iostream>

#define scale 10
bool segurado=false;

void click(b2BodyId id){


    b2Vec2 boxPos = b2Body_GetPosition(id);
    float drawX = (boxPos.x - 1.0f) * scale;
    float drawY = (boxPos.y - 1.0f) * scale;
    float drawWidth = 2.0f * scale;
    float drawHeight = 2.0f * scale;

    b2Vec2 mouseWorld = {
    (float)GetMouseX() / scale,
    (float)GetMouseY() / scale
    };

    b2Vec2 direcao = {
    mouseWorld.x - boxPos.x,
    mouseWorld.y - boxPos.y
    };

    b2Vec2 vel = {
    direcao.x * 15,
    direcao.y * 15
    };
    
    if(IsMouseButtonDown(0)){
        Rectangle mouseHitbox = (Rectangle){(float)GetMouseX(),(float)GetMouseY(),5,5};


        if(CheckCollisionRecs(mouseHitbox, (Rectangle){drawX, drawY, drawWidth, drawHeight})){
            segurado=true;
        }
    }
    if(IsMouseButtonReleased(0)){
        segurado=false;
        std::cout << "ta solto" << std::endl;
    }
    
    if(segurado==true){
        
        std::cout << "AAAAAAAAAAAAI" << std::endl;
        
        b2Body_SetLinearVelocity(id, vel);
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
    
    Texture2D texture = LoadTexture("images/open backpack.png");

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 9.8f};
    b2WorldId world = b2CreateWorld(&worldDef);

    // cria o formato basico da mochila

    //parte inferior
    b2BodyDef groundBodyDef = b2DefaultBodyDef(); //definebody
    groundBodyDef.position = {(screenWidth/2)/scale, (screenHeight/2+275)/scale}; //define posicao inicial
    b2BodyId groundBody = b2CreateBody(world, &groundBodyDef); //cria o "perfil" no mundo
    b2Polygon groundBox = b2MakeBox(20.0f, 0.5f); //cria uma caixa com o tamanho definido
    b2ShapeDef groundShapeDef = b2DefaultShapeDef(); //coloca o formato como quadrado padrao do box2d
    b2CreatePolygonShape(groundBody, &groundShapeDef, &groundBox); //aplica o formato e a caixa em um poligono

    //parte esquerda
    b2BodyDef leftBodyDef = b2DefaultBodyDef(); //definebody
    leftBodyDef.position = {(screenWidth/2-135)/scale, (screenHeight/2+100)/scale}; //define posicao inicial
    b2BodyId leftBody = b2CreateBody(world, &leftBodyDef); //cria o "perfil" no mundo
    b2Polygon leftBox = b2MakeBox(0.5f, 20); //cria uma caixa com o tamanho definido
    b2ShapeDef leftShapeDef = b2DefaultShapeDef(); //coloca o formato como quadrado padrao do box2d
    b2CreatePolygonShape(leftBody, &leftShapeDef, &leftBox); //aplica o formato e a caixa em um poligono

    //parte direita
    b2BodyDef rightBodyDef = b2DefaultBodyDef(); //definebody
    rightBodyDef.position = {(screenWidth/2+185)/scale, (screenHeight/2+100)/scale}; //define posicao inicial
    b2BodyId rightBody = b2CreateBody(world, &rightBodyDef); //cria o "perfil" no mundo
    b2Polygon rightBox = b2MakeBox(0.5f, 20); //cria uma caixa com o tamanho definido
    b2ShapeDef rightShapeDef = b2DefaultShapeDef(); //coloca o formato como quadrado padrao do box2d
    b2CreatePolygonShape(rightBody, &rightShapeDef, &rightBox); //aplica o formato e a caixa em um poligono
    
    //caixa de teste para colisao
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {(screenWidth/2)/scale+6, (screenHeight/2-100)/scale};
    b2BodyId bodyId = b2CreateBody(world, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    //caixa de teste para colisao
    b2BodyDef ballbodyDef = b2DefaultBodyDef();
    b2Circle circle;
    circle.center = {0.0f, 0.0f};
    circle.radius = 1.0f;
    ballbodyDef.type = b2_dynamicBody;
    ballbodyDef.position = {((screenWidth/2))/scale+5, (screenHeight/2-50)/scale};
    b2BodyId ballbodyId = b2CreateBody(world, &ballbodyDef);
    b2ShapeDef ballshapeDef = b2DefaultShapeDef();
    ballshapeDef.density = 1.0f;
    b2CreateCircleShape(ballbodyId, &ballshapeDef, &circle);
    
    
    while (!WindowShouldClose())
    {
        b2Vec2 boxPos = b2Body_GetPosition(bodyId);
        b2Vec2 ballPos = b2Body_GetPosition(ballbodyId);
        int bdrawX = (ballPos.x) * scale;
        int bdrawY = (ballPos.y) * scale;
        b2Vec2 groundPos = b2Body_GetPosition(groundBody);
        int groundDrawX = (groundPos.x - 20.0f) * scale;
        int groundDrawY = (groundPos.y - 0.5f) * scale;
        int groundDrawWidth = 40.0f * scale;
        int groundDrawHeight = 1.0f * scale;

        b2Vec2 leftPos = b2Body_GetPosition(leftBody);
        int leftDrawX = (leftPos.x - 0.5f) * scale;
        int leftDrawY = (leftPos.y - 20.0f) * scale;
        int leftDrawWidth = 1.0f * scale;
        int leftDrawHeight = 40.0f * scale;

        b2Vec2 rightPos = b2Body_GetPosition(rightBody);
        int rightDrawX = (rightPos.x - 0.5f) * scale;
        int rightDrawY = (rightPos.y - 20.0f) * scale;
        int rightDrawWidth = 1.0f * scale;
        int rightDrawHeight = 40.0f * scale;
        int drawX = (boxPos.x - 1.0f) * scale;
        int drawY = (boxPos.y - 1.0f) * scale;
        int drawWidth = 2.0f * scale;
        int drawHeight = 2.0f * scale;

        float dt = GetFrameTime();
        click(bodyId);

        b2World_Step(world, dt, 4);


        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(texture, (Vector2){(screenWidth/2)-250, screenHeight/2-200}, 0.0f, 0.55,WHITE);
        DrawRectangle(groundDrawX, groundDrawY, groundDrawWidth, groundDrawHeight, RED);
        DrawRectangle(leftDrawX, leftDrawY, leftDrawWidth, leftDrawHeight, RED);
        DrawRectangle(rightDrawX, rightDrawY, rightDrawWidth, rightDrawHeight, RED);



        DrawRectangle(drawX, drawY, drawWidth, drawHeight, GREEN);
        DrawCircle(bdrawX, bdrawY, 1*scale, GREEN);
        EndDrawing();
    }

    b2DestroyWorld(world);
    CloseWindow();
    return 0;
}