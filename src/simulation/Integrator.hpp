#pragma once

#include "simulation/State.hpp"

enum class IntegratorType
{
    Euler = 0,
    Verlet
};

// Integrator operates on acceleration only.
// All forces are resolved beforehand by the Dynamics module.
class Integrator
{
public:

    static void Step(IntegratorType Type, State& State, float DeltaTime, Vector2 Center, float mu);

private:

    static void Euler(State& State, float DeltaTime);
    static void Verlet(State& s, float dt, Vector2 center, float mu);
};