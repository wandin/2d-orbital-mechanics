#include "OrbitDynamics.hpp"
#include <raymath.h>
#include "OrbitDynamics.hpp"

void OrbitDynamics::ComputeGravityAcceleration(State &State, Vector2 Center, float MU)
{
    Vector2 R = Vector2Subtract(Center, State.Position);
    float DistanceSq = Vector2LengthSqr(R);
    float Distance = sqrtf(DistanceSq);

    Vector2 Direction = Vector2Scale(R, 1.0f / Distance);

    float AccelerationMagnitude = MU / DistanceSq;
    State.Acceleration = Vector2Scale(Direction, AccelerationMagnitude);
}

float OrbitDynamics::ComputeTotalEnergy(const State &State, Vector2 Center, float MU)
{
    float SpeedSq = Vector2LengthSqr(State.Velocity);
    float R = Vector2Distance(State.Position, Center);

    float Kinetic = 0.5f * SpeedSq;
    float Potential = -MU / R;
    
    return Kinetic + Potential;
}
