# Circular Orbit – Energy Preservation & Numerical Integration

A **2D orbital mechanics simulator** written in **C++ using Raylib**, focused on demonstrating  
**energy conservation**, **numerical stability**, and the impact of different **time integration methods** on orbital motion.

This project is part of a progressive simulation series aimed at building strong foundations for **Guidance, Navigation & Control (GNC)**, aerospace simulation, and physics-based system modeling.

---

## 🎯 Project Objectives

- Simulate **circular orbital motion** under central gravity
- Compare **Euler integration** with **energy-preserving integrators**
- Demonstrate **numerical energy drift** vs **symplectic behavior**
- Visualize long-term stability of orbital trajectories
- Build intuition for why integrator choice matters in GNC systems

---

## 🧠 Physical Model

The system models a **point mass orbiting a fixed central body** under Newtonian gravity.

### Central Gravity Model

The acceleration is defined as:

```
a = -μ · r / |r|³
```

Where:
- `r` is the vector from the satellite to the central body
- `μ` is the **gravitational parameter**

```
μ = G · M
```

In this simulation, `μ` is treated as a configurable constant.

---

## 🛰 Circular Orbit Initial Conditions

A perfect circular orbit is achieved by initializing velocity as:

```
v = sqrt( μ / r )
```

Perpendicular to the radius vector.

This condition is used as a **baseline** to evaluate numerical accuracy.

---

## 🔬 Numerical Integrators

### Euler (Explicit)

- First-order method
- Computationally cheap
- Does **not conserve energy**
- Produces orbital spiraling over time

Observed behavior:
- Radius error increases continuously
- Total energy drifts monotonically
- Orbit becomes unstable over long simulation runs

---

### Velocity Verlet (Symplectic Integrator)

- Second-order, time-reversible method
- Widely used in orbital and molecular dynamics
- **Preserves energy in the long term**
- Maintains stable closed orbits

Observed behavior:
- Radius error remains near zero
- Total energy oscillates slightly but remains bounded
- Orbit remains stable even after tens of thousands of steps

This integrator demonstrates why **symplectic methods are preferred in orbital mechanics and GNC simulations**.

---

## ⚡ Energy Analysis

The total mechanical energy is computed as:
```
E = (1/2) · v² − μ / r
```

### Observations

- **Euler**
  - Energy steadily drifts
  - Leads to artificial orbital decay or expansion
- **Verlet**
  - Energy oscillates around the correct value
  - No long-term drift

This behavior directly explains the visual spiraling observed with Euler integration.

---

## 🎨 Visualization

- Green trail → orbital path
- Yellow dot → central body
- Red dot → orbiting satellite
- HUD displays:
  - Integrator type
  - Total energy
  - Radius error
  - FPS

The visualization makes numerical errors **immediately visible**, even without inspecting code.

---

## 🎮 Controls

| Key | Action |
|----|-------|
| **1** | Switch to Euler integrator |
| **2** | Switch to Velocity Verlet |
| **R** | Reset orbit |
| **ESC** | Exit |

---

## 🛠 Build & Run

### Requirements

- C++17 compatible compiler
- Raylib
- Supported platforms:
  - Linux
  - Windows
  - macOS

### Build (Linux)

```bash
mkdir -p build
g++ -Isrc $(find src -name '*.cpp') -o build/app \
  -std=c++17 -Wall -Wextra \
  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
### Run
```
./build/app
```

### Build (Windows MinGW)
```
mkdir build
g++ -Isrc src\**\*.cpp -o build\app.exe ^
  -std=c++17 -Wall -Wextra ^
  -lraylib -lopengl32 -lgdi32 -lwinmm
```
### Run
```
build\app.exe
```


### 🧱 Architecture Overview

The project is intentionally modular:

- **State**
  - Holds position, velocity, acceleration, and trajectory history

- **OrbitDynamics**
  - Computes gravitational acceleration and total energy

- **Integrator**
  - Advances the state using different numerical methods

- **Renderer**
  - Visualization and HUD

This separation mirrors real-world simulation and flight software design.

### 📚 Educational Context

This project is part of a progressive simulation roadmap:

Project	Concept:
- 1	Kinematics – State propagation
- 2	Dynamics – Force, mass, drag
- 3	Orbital Mechanics (this project)
- 4	Attitude Dynamics
- 5	Full 6DOF Rigid Body
- 6	Control Systems (PID, LQR)
- 7	State Estimation (Kalman Filters)

### 🚀 Next Steps

Multiple orbiting bodies
Elliptical and perturbed orbits
Energy vs time plots
Attitude and rotational dynamics
Closed-loop orbital control