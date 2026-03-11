#include <raylib.h>
#include <box2d/box2d.h>

int main() {
    InitWindow(1280, 720, "raylib + box2d");
    SetTargetFPS(60);

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 9.8f};

    b2WorldId world = b2CreateWorld(&worldDef);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        b2World_Step(world, dt, 4);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("raylib + box2d funcionando", 40, 40, 20, RAYWHITE);
        EndDrawing();
    }

    b2DestroyWorld(world);
    CloseWindow();
    return 0;
}