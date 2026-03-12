#include <raylib.h>
#include <box2d/box2d.h>
#include <cmath>

// converte metros da física para pixels na tela
static constexpr float PIXELS_PER_METER = 100.0f;

static Vector2 ToScreen(b2Vec2 position)
{
    return Vector2{
        position.x * PIXELS_PER_METER,
        position.y * PIXELS_PER_METER
    };
}

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib + box2d teste");
    SetTargetFPS(60);

    // cria mundo da física
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 9.8f};
    b2WorldId world = b2CreateWorld(&worldDef);

    // cria o chão
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = {6.4f, 6.5f};
    b2BodyId groundBody = b2CreateBody(world, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(5.0f, 0.25f);

    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundBody, &groundShapeDef, &groundBox);

    // cria a caixa dinâmica
    b2BodyDef boxBodyDef = b2DefaultBodyDef();
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.position = {6.4f, 2.0f};
    b2BodyId boxBody = b2CreateBody(world, &boxBodyDef);

    b2Polygon boxShape = b2MakeBox(0.3f, 0.3f);

    b2ShapeDef boxShapeDef = b2DefaultShapeDef();
    boxShapeDef.material.friction = 0.4f;
    boxShapeDef.material.restitution = 0.1f;
    boxShapeDef.density = 1.0f;
    b2CreatePolygonShape(boxBody, &boxShapeDef, &boxShape);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // atualiza física
        b2World_Step(world, dt, 4);

        // pega posição e rotação da caixa
        b2Vec2 boxPos = b2Body_GetPosition(boxBody);
        b2Rot boxRot = b2Body_GetRotation(boxBody);

        Vector2 screenPos = ToScreen(boxPos);
        float angleDeg = atan2f(boxRot.s, boxRot.c) * RAD2DEG;

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("se a caixa cair e parar no chao, deu certo", 30, 30, 20, RAYWHITE);

        // desenha chão
        DrawRectanglePro(
            Rectangle{
                6.4f * PIXELS_PER_METER,
                6.5f * PIXELS_PER_METER,
                10.0f * PIXELS_PER_METER,
                0.5f * PIXELS_PER_METER
            },
            Vector2{
                5.0f * PIXELS_PER_METER,
                0.25f * PIXELS_PER_METER
            },
            0.0f,
            DARKGRAY
        );

        // desenha caixa
        DrawRectanglePro(
            Rectangle{
                screenPos.x,
                screenPos.y,
                0.6f * PIXELS_PER_METER,
                0.6f * PIXELS_PER_METER
            },
            Vector2{
                0.3f * PIXELS_PER_METER,
                0.3f * PIXELS_PER_METER
            },
            angleDeg,
            RED
        );

        EndDrawing();
    }

    b2DestroyWorld(world);
    CloseWindow();
    return 0;
}