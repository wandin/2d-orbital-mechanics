#include "OrbitDynamics.hpp"
#include <raymath.h>
#include "OrbitDynamics.hpp"

void OrbitDynamics::ComputeGravityAcceleration(State &State, Vector2 Center, float MU)
{
    Vector2 R = Vector2Subtract(Center, State.Position);

    float d2 = Vector2LengthSqr(R);
    float d = sqrtf(d2);

    State.Acceleration = Vector2Scale(R, MU / (d2 * d));
}

float OrbitDynamics::ComputeTotalEnergy(const State &State, Vector2 Center, float MU)
{
    float SpeedSq = Vector2LengthSqr(State.Velocity);
    float R = Vector2Distance(State.Position, Center);

    float Kinetic = 0.5f * SpeedSq;
    float Potential = -MU / R;
    
    return Kinetic + Potential;
}
