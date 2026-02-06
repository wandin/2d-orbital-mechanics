#pragma once

#include "simulation/State.hpp"

class OrbitDynamics
{
public:
    static void ComputeGravityAcceleration(State& State, Vector2 Center, float MU);

    static float ComputeTotalEnergy(const State& State, Vector2 Center, float MU);
};  