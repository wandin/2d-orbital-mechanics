#include "Integrator.hpp"
#include <raymath.h>

// Dispatcher
void Integrator::Step(IntegratorType Type, State& State, float DeltaTime, Vector2 Center, float mu)
{
    switch(Type)
    {
        case IntegratorType::Euler:
        Euler(State, DeltaTime);
        break;
        
        case IntegratorType::Verlet:
        Verlet(State, DeltaTime, Center, mu);
        break;
    }
}

// Semi implicit Euler
void Integrator::Euler(State &State, float DeltaTime)
{
    State.Position += Vector2Scale(State.Velocity, DeltaTime);
    State.Velocity += Vector2Scale(State.Acceleration, DeltaTime);
}

// Velocity Verlet
void Integrator::Verlet(State& State, float DeltaTime, Vector2 Center, float MU)
{
    Vector2 a0 = State.Acceleration;

    // x(t + dt)
    State.Position = Vector2Add(
        State.Position,
        Vector2Add(
            Vector2Scale(State.Velocity, DeltaTime),
            Vector2Scale(a0, 0.5f * DeltaTime * DeltaTime)
        )
    );

    // compute a(t + dt)
    Vector2 r = Vector2Subtract(Center, State.Position);
    float d2 = Vector2LengthSqr(r);
    float d = sqrtf(d2);
    Vector2 a1 = Vector2Scale(r, MU / (d2 * d));

    // v(t + dt)
    State.Velocity = Vector2Add(
        State.Velocity,
        Vector2Scale(Vector2Add(a0, a1), 0.5f * DeltaTime)
    );

    State.Acceleration = a1;
}

