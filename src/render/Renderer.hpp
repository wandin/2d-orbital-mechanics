#pragma once

#include <raylib.h>
#include "simulation/State.hpp"
#include "simulation/Integrator.hpp"


class Renderer
{
public:
    static void DrawBody(const State& State);
    static void DrawHUD(IntegratorType IntegratorType, float Energy, float RadiusError);
};