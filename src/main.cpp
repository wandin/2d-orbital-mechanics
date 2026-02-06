#include <raylib.h>
#include <raymath.h>
#include "render/Renderer.hpp"
#include "simulation/State.hpp"
#include "simulation/Integrator.hpp"
#include "simulation/OrbitDynamics.hpp"

constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Circular Orbit - Energy Preservation");
    SetTargetFPS(300);
    ToggleFullscreen();

   Vector2 Center = { WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f };
   float MU = 20000.0f;

   State CurrentState;
   CurrentState.Position = { Center.x + 200.f, Center.y };
   CurrentState.Velocity = { 0.0f, -sqrtf(MU / 200.0f) };

   IntegratorType CurrentType = IntegratorType::Verlet;

   float DeltaTime = 1.0f / 20.f;

   while(!WindowShouldClose())
   {
        if(IsKeyPressed(KEY_ONE))
        {
            CurrentType = IntegratorType::Euler;
        }
        if(IsKeyPressed(KEY_TWO))
        {
            CurrentType = IntegratorType::Verlet;
        }

        if(IsKeyPressed(KEY_R))
        {
            CurrentState.Position = { Center.x + 200.0f, Center.y };
            CurrentState.Velocity = { 0.0f, -sqrtf( MU / 200.0f) };
            CurrentState.Trail.clear();
        }


        OrbitDynamics::ComputeGravityAcceleration(CurrentState, Center, MU);
        Integrator::Step(CurrentType, CurrentState, DeltaTime, Center, MU);

        CurrentState.Trail.push_back(CurrentState.Position);

        if(CurrentState.Trail.size() > 30000)
        {
            CurrentState.Trail.erase(CurrentState.Trail.begin());
        }

        float TotalEnergy = OrbitDynamics::ComputeTotalEnergy(CurrentState, Center, MU);

        Renderer::Draw(CurrentState, Center, CurrentType, TotalEnergy);

        DrawText(TextFormat("Trail Lengh: %d", CurrentState.Trail.size()), 10, 140, 20, BLUE);
   }

    CloseWindow();

    return 0;
}
