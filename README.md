# Charged Particle Simulation

A real-time 2D physics simulation of charged particles interacting through electrostatic forces, built with C and [raylib](https://www.raylib.com/).

## 🔬 Physics Simulation

This project simulates the behavior of point charges interacting according to **Coulomb's Law**.

### Core Concepts

*   **Electrostatic Force:** The force $F$ between two point charges is calculated as:
    $$ F = k_e \frac{q_1 q_2}{r^2} $$
    Where:
    *   $F$ is the electrostatic force.
    *   $k_e$ is Coulomb's constant (adjusted for simulation scale).
    *   $q_1, q_2$ are the magnitudes of the charges based on particle type.
    *   $r$ is the distance between the charges.

*   **Dynamics:**
    *   **Red Particles:** Positive charge (+).
    *   **Blue Particles:** Negative charge (-).
    *   **Interaction:** Like charges repel, opposite charges attract.
    *   **Damping:** A small drag factor is applied to particle velocities to approximate air resistance and stabilize the system over time.
    *   **Boundaries:** Particles reflect elastically off the screen edges.

## 🎮 Controls & Visualization

The simulation runs automatically, but you can toggle various visualizations to better understand the forces at play.

| Key | Action | Description |
| :--- | :--- | :--- |
| **V** | Toggle Velocity | Visualizes the velocity vector and speed value for each particle. |
| **F** | Toggle Pair Forces | Visualizes the individual electrostatic force vectors between interacting pairs. |
| **G** | Toggle Net Force | Visualizes the total resultant force acting on each particle. |
| **ESC** | Exit | Closes the simulation window. |

## ⚙️ Configuration

The simulation behavior is controlled by preprocessor macros defined at the top of `sim.c`. You can tweak these values to create different scenarios. **Recompile the project (`make`) after changing any of these values.**

| Macro | Default | Description |
| :--- | :--- | :--- |
| `NUM_CHARGES` | `300` | The total number of particles in the simulation. Increasing this will impact performance ($O(n^2)$ complexity). |
| `SPEED` | `5` | The maximum initial random velocity component for particles. |
| `FORCE_MAG` | `100000` | The coupling constant representing Coulomb's constant ($k_e$). Higher values result in stronger attraction/repulsion. |
| `RADIUS` | `7` | The visual radius of the particles. |
| `NEGATIVE_PARTICLE_PERCENTAGE` | `0` | Probability (0-100) of generating a negative charge. Set to `50` for a balanced mix of positive and negative charges. |
| `..._COLOR` | `RED`/`BLUE` | Colors for positive and negative particles. |

## 🛠️ Build & Run

### Prerequisites

*   **GCC Compiler** (MinGW recommended on Windows).
*   **Raylib** library installed.
    *   *Default path assumed:* `C:\raylib_mingw` (This is the standard installation path for the MinGW version of Raylib).

### Building with Make

If you have `make` installed, simply run from the project root:

```bash
make
```

### Building Manually

You can compile the project directly using GCC. Ensure you point to the correct Raylib header and library paths:

```bash
gcc -o sim.exe sim.c -I"C:\raylib_mingw\include" "C:\raylib_mingw\lib\libraylib.a" -lopengl32 -lgdi32 -lwinmm
```

### Running

After compiling, launch the simulation:

```bash
./sim.exe
```
