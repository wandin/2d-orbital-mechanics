#include "Renderer.hpp"
#include <raymath.h>

void Renderer::Draw(const State &State, Vector2 Center, IntegratorType Type, float Energy)
{
    BeginDrawing();
    ClearBackground(BLACK);

    // Orbit trail
    for(size_t i = 1; i < State.Trail.size(); ++i)
    {
        DrawLineV(State.Trail[i-1], State.Trail[i], DARKGREEN);
    }

    // Central Body
    DrawCircleV(Center, 8.0f, YELLOW);

    //Satellite
    DrawCircleV(State.Position, 5.0f, RED);


    // Info Text
    const char* Name = Type == IntegratorType::Euler ? "Euler" : "Verlet";
    
    DrawText(TextFormat("Integrator: %s", Name), 10, 20, 20, WHITE);
    DrawText(TextFormat("Total energy: %.4f", Energy), 10, 50, 20, LIGHTGRAY);
    DrawText("Press [1] Euler | [2] Verlet | [R] Reset", 10, 80, 20, GRAY);
    DrawText(TextFormat("Current FPS: %d", GetFPS()), 10,110, 20, GRAY);

    float radius = Vector2Distance(State.Position, Center);
    DrawText(TextFormat("Radius error: %.2f", radius - 200.0f), 10, 180, 20, ORANGE);

    EndDrawing();
}