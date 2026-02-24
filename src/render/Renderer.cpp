#include "Renderer.hpp"
#include <raymath.h>

void Renderer::DrawBody(const State& State)
{
    // Trail
    for (size_t i = 1; i < State.Trail.size(); ++i)
    {
        DrawLineV(State.Trail[i - 1], State.Trail[i], State.StateColor);
    }

    // Satellite
    DrawCircleV(State.Position, 5.0f, State.StateColor);
}

void Renderer::DrawHUD(IntegratorType IntegratorType, float Energy, float RadiusError)
{
    const char* name = IntegratorType == IntegratorType::Euler ? "Euler" : "Verlet";

    DrawText(TextFormat("Integrator: %s", name), 10, 80, 20, WHITE);
    DrawText(TextFormat("Total energy: %.2f", Energy), 10, 110, 20, LIGHTGRAY);
    DrawText(TextFormat("Radius error: %.2f", RadiusError), 10, 140, 20, ORANGE);
}