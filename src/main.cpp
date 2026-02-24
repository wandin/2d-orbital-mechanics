#include <raylib.h>
#include <raymath.h>
#include "render/Renderer.hpp"
#include "simulation/State.hpp"
#include "simulation/Integrator.hpp"
#include "simulation/OrbitDynamics.hpp"

constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
constexpr size_t MaxTrail = 6000;

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Circular Orbit - Energy Preservation");
    SetTargetFPS(300);
    ToggleFullscreen();

    Vector2 Center = { WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f };
    float MU = 20000.0f;

    // -----------------------------
    // Create orbiting bodies
    // -----------------------------
    std::vector<State> Bodies;
    const int NumBodies = 5;

    auto InitializeBodies = [&]()
    {
        Bodies.clear();

        for (int i = 0; i < NumBodies; ++i)
        {
            float radius = 120.0f + i * 60.0f;

            State s;
            s.Position = { Center.x + radius, Center.y };

            float speed = sqrtf(MU / radius);
            s.Velocity = { 0.0f, -speed };

            s.StateColor = {
                (unsigned char)GetRandomValue(80, 255),
                (unsigned char)GetRandomValue(80, 255),
                (unsigned char)GetRandomValue(80, 255),
                255
                };

            Bodies.push_back(s);
        }
    };

    InitializeBodies();

    IntegratorType CurrentType = IntegratorType::Verlet;
    float DeltaTime = 1.0f / 20.0f;

    // -----------------------------
    // Main Loop
    // -----------------------------
    while (!WindowShouldClose())
    {
        // Input
        if (IsKeyPressed(KEY_ONE))
            CurrentType = IntegratorType::Euler;

        if (IsKeyPressed(KEY_TWO))
            CurrentType = IntegratorType::Verlet;

        if (IsKeyPressed(KEY_R))
            InitializeBodies();

        // Physics step
        for (State& body : Bodies)
        {
            OrbitDynamics::ComputeGravityAcceleration(body, Center, MU);
            Integrator::Step(CurrentType, body, DeltaTime, Center, MU);

            body.Trail.push_back(body.Position);
       
            if (body.Trail.size() > MaxTrail)
            {
                body.Trail.erase(body.Trail.begin(), body.Trail.begin() + (body.Trail.size() - MaxTrail));
            }
        }

        // -----------------------------
        // Rendering (single frame!)
        // -----------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        // Central body
        DrawCircleV(Center, 8.0f, YELLOW);

        for (const State& body : Bodies)
        {
            Renderer::DrawBody(body);
        }

        // Use first body for HUD reference
        const State& ref = Bodies.front();
        float energy = OrbitDynamics::ComputeTotalEnergy(ref, Center, MU);
        float radius = Vector2Distance(ref.Position, Center);

        Renderer::DrawHUD(CurrentType, energy, radius - 120.0f);

        DrawText("1: Euler | 2: Verlet | R: Reset", 10, 10, 20, GRAY);
        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 50, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
