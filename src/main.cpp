#include <raylib.h>
#include <box2d/box2d.h>
#include <cmath>

#define scale 10

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
    groundBodyDef.position = {(screenWidth/2-175)/scale, (screenHeight/2+275)/scale}; //define posicao inicial
    b2BodyId groundBody = b2CreateBody(world, &groundBodyDef); //cria o "perfil" no mundo
    b2Polygon groundBox = b2MakeBox(20.0f, 0.5f); //cria uma caixa com o tamanho definido
    b2ShapeDef groundShapeDef = b2DefaultShapeDef(); //coloca o formato como quadrado padrao do box2d
    b2CreatePolygonShape(groundBody, &groundShapeDef, &groundBox); //aplica o formato e a caixa em um poligono

    //parte esquerda
    b2BodyDef leftBodyDef = b2DefaultBodyDef(); //definebody
    leftBodyDef.position = {(screenWidth/2-135)/scale, (screenHeight/2-125)/scale}; //define posicao inicial
    b2BodyId leftBody = b2CreateBody(world, &leftBodyDef); //cria o "perfil" no mundo
    b2Polygon leftBox = b2MakeBox(0.5f, 20); //cria uma caixa com o tamanho definido
    b2ShapeDef leftShapeDef = b2DefaultShapeDef(); //coloca o formato como quadrado padrao do box2d
    b2CreatePolygonShape(leftBody, &leftShapeDef, &leftBox); //aplica o formato e a caixa em um poligono

    //parte direita
    b2BodyDef rightBodyDef = b2DefaultBodyDef(); //definebody
    rightBodyDef.position = {(screenWidth/2+185)/scale, (screenHeight/2-125)/scale}; //define posicao inicial
    b2BodyId rightBody = b2CreateBody(world, &rightBodyDef); //cria o "perfil" no mundo
    b2Polygon rightBox = b2MakeBox(0.5f, 20); //cria uma caixa com o tamanho definido
    b2ShapeDef rightShapeDef = b2DefaultShapeDef(); //coloca o formato como quadrado padrao do box2d
    b2CreatePolygonShape(rightBody, &rightShapeDef, &rightBox); //aplica o formato e a caixa em um poligono
    
    //caixa de teste para colisao
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {(screenWidth/2)/scale, (screenHeight/2-100)/scale};
    b2BodyId bodyId = b2CreateBody(world, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
    
    
    while (!WindowShouldClose())
    {
        b2Vec2 boxPos = b2Body_GetPosition(bodyId);
    
        int drawX = (boxPos.x - 1.0f) * scale;
        int drawY = (boxPos.y - 1.0f) * scale;
        int drawWidth = 2.0f * scale;
        int drawHeight = 2.0f * scale;

        float dt = GetFrameTime();
        b2World_Step(world, dt, 4);

        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(texture, (Vector2){(screenWidth/2)-250, screenHeight/2-200}, 0.0f, 0.55,WHITE);
        DrawRectangle(screenWidth/2-175,screenHeight/2+265,400,10,RED);
        DrawRectangle(screenWidth/2-135,screenHeight/2-125,10,400,RED);
        DrawRectangle(screenWidth/2+185,screenHeight/2-125,10,400,RED);



        DrawRectangle(drawX, drawY, drawWidth, drawHeight, GREEN);
        EndDrawing();
    }

    b2DestroyWorld(world);
    CloseWindow();
    return 0;
}