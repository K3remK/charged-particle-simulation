# Charged Particle Simulation

A real-time 2D physics simulation of charged particles interacting through electrostatic forces, built with C and [raylib](https://www.raylib.com/).

## 🔬 Physics Simulation

This project simulates the behavior of point charges interacting according to **Coulomb's Law**. 

The force $F$ between two point charges is calculated as:

$$ F = k_e \frac{q_1 q_2}{r^2} $$

Where:
- $F$ is the electrostatic force.
- $k_e$ is Coulomb's constant.
- $q_1, q_2$ are the magnitudes of the charges.
- $r$ is the distance between the charges.

In this simulation:
- **Red Particles**: Positive charge (+).
- **Blue Particles**: Negative charge (-).
- Like charges repel, opposite charges attract.

## 🛠️ Build & Run

### Prerequisites
- **GCC Compiler** (MinGW recommended on Windows).
- **Raylib** library installed. 
  - *Default path assumed:* `C:\raylib`

### Building with Make
If you have `make` installed, simply run:

```bash
make
```

### Building Manually
You can compile the project directly using GCC. Ensure you point to the correct Raylib header and library paths:

```bash
gcc -o sim.exe sim.c -I"C:\raylib\include" "C:\raylib\lib\libraylib.a" -lopengl32 -lgdi32 -lwinmm
```

### Running
After compiling, launch the simulation:

```bash
./sim.exe
```

## 🎮 Controls

- Just watch the chaos unfold! The simulation runs automatically upon start.
- Close the window or press `ESC` to exit.
