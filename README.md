# Projectile Interception Simulation

## Description

This C++ program calculates whether an **interceptor** can shoot down a **projectile** in flight within a 2D plane.

The user enters the initial conditions for both projectiles. The program checks whether a valid launch angle exists for the interceptor by scanning angles from 0° to 90° using a bracketing method. If a solution exists and the firing delay is positive, it displays the results. Otherwise, it asks for new parameters until a valid configuration is found.

---
## Screenshots

![Interception Simulation Screenshot](https://github.com/yann-richard-info/Projectile-Interception-Simulation/blob/main/image_interception.png?raw=true)

---
## Prerequisites

- **IDE** : [CodeBlocks](https://www.codeblocks.org/)
- **Compiler** : GCC with MinGW (included in the Windows version of CodeBlocks)
- **Language** : C++
- **Libraries** : `<iostream>` and `<cmath>` only (no external dependencies)

---

## Installation

1. Download and install [CodeBlocks with MinGW](https://www.codeblocks.org/downloads/).
2. Download this repository.
3. Open `Saé_Info.cbp` in CodeBlocks.
4. Build : **Build > Build** (`Ctrl+F9`).
5. Run : **Build > Run** (`Ctrl+F10`).

> ⚠️ If the compiler is not detected, check the MinGW path under **Settings > Compiler > Toolchain executables**.

---
## Project Files

Here are the main files of the project:

- [Main Source Code (`main.cpp`)][https://github.com/votre-utilisateur/votre-depot/blob/main/main.cpp](https://raw.githubusercontent.com/yann-richard-info/Projectile-Interception-Simulation/refs/heads/main/Sa%C3%A9_Info.cbp)
- [Library Header (`ma_bibliotheque.h`)](https://github.com/votre-utilisateur/votre-depot/blob/main/ma_bibliotheque.h)
- [Library Source (`ma_bibliotheque.cpp`)](https://github.com/votre-utilisateur/votre-depot/blob/main/ma_bibliotheque.cpp)
- [CodeBlocks Project File (`Saé_Info.cbp`)](https://github.com/votre-utilisateur/votre-depot/blob/main/Saé_Info.cbp)

---
## User Guide

On startup, the program prompts for the following inputs one by one:

```
Entrer la vitesse initiale du projectile v0 (m/s) :
Entrer la position initiale x0 (m) :
Entrer la hauteur initiale z0 (m) :
Entrer l'angle de tir alpha0 (deg) :
Entrer la position d'interception xi (m) :
Entrer la distance yi' (m) de l'intercepteur :
Entrer la vitesse initiale de l'intercepteur vi (m/s) :
```

If no interception solution is found, or if the firing delay is negative (the interceptor cannot reach the missile in time), the program displays an error message and asks for new inputs.

### Example output

```
Altitude projectile : 211.71 m
Encadrement trouve entre 63° et 64°
Altitude du projectile au point d'interception : 211.71 m
Angle de tir de l'intercepteur : 63.14 deg
Temps de vol du projectile : 4.24 s
Temps de vol de l'intercepteur : 4.15 s
Decalage entre les tirs : 0.09 s
```

---

## Project Structure

```
Saé_Info/
├── Saé_Info.cbp          # CodeBlocks project file
├── main.cpp              # Entry point: user input, function calls, output display
├── ma_bibliotheque.h     # Function prototypes
└── ma_bibliotheque.cpp   # Function implementations
```

---

## Main Variables

| Variable             | Type          | Description                                        | Unit  |
|----------------------|---------------|----------------------------------------------------|-------|
| `G_PESANTEUR`        | `const float` | Gravitational constant (9.81)                      | m/s²  |
| `G`, `PI`            | `const float` | Physical constants (defined in `ma_bibliotheque.cpp`) | —  |
| `v0`                 | `float`       | Initial velocity of the projectile                 | m/s   |
| `x0`                 | `float`       | Initial horizontal position of the projectile      | m     |
| `z0`                 | `float`       | Initial height of the projectile                   | m     |
| `alpha0`             | `float`       | Launch angle of the projectile                     | deg   |
| `xi`                 | `float`       | Horizontal interception position                   | m     |
| `yi_prime`           | `float`       | Distance of the interceptor                        | m     |
| `vi`                 | `float`       | Initial velocity of the interceptor                | m/s   |
| `zi`                 | `float`       | Altitude of the projectile at the interception point | m   |
| `alpha_i`            | `float`       | Calculated launch angle of the interceptor         | deg   |
| `temps_projectile`   | `float`       | Flight time of the projectile to reach `xi`        | s     |
| `temps_intercepteur` | `float`       | Flight time of the interceptor to reach `xi`       | s     |
| `decalage_temps`     | `float`       | Firing delay between the two projectiles           | s     |
| `alpha_liste[91]`    | `float[]`     | List of tested angles from 0° to 90°               | deg   |

---

## Main Functions

### Utility functions

```cpp
float Util_Deg_2_Rad(float input_angle_deg);
```
Converts an angle from degrees to radians.

```cpp
float Util_Projeter_Axe_X(float input_vitesse, float input_angle);
float Util_Projeter_Axe_Z(float input_vitesse, float input_angle);
```
Projects a velocity onto the horizontal (X) or vertical (Z) axis.

### Physics simulation functions

```cpp
float Calculer_Z_Trajectoire(float input_x, float input_alpha, float input_v0, float input_x0, float input_z0);
```
Computes the altitude `z` of the projectile at horizontal position `x` using the parabolic trajectory equation.

```cpp
float Calculer_Alpha_Intercepteur(float input_xi, float input_yi_prime, float input_alpha0, float input_v0, float input_x0, float input_z0, float input_vi);
```
Calculates the interceptor's launch angle to reach the projectile at `xi`. Solves a quadratic equation on `tan(alpha)`.

```cpp
float Calculer_Temps_Vol(float input_x, float input_alpha, float input_v0, float input_x0, float input_z0);
```
Calculates the flight time of a projectile to cover a given horizontal distance.

```cpp
float Calculer_Decalage_Temps(float input_t_vol_projectile, float input_t_vol_intercepteur);
```
Returns the difference between the projectile's and interceptor's flight times. A positive result means the interceptor can be fired after the projectile and still arrive in time.

```cpp
bool Rechercher_Existence_Solution(float input_xi, float input_yi_prime, float input_alpha0, float input_v0, float input_x0, float input_z0, float input_vi, float input_liste_alpha_i[]);
```
Iterates through angles from 0° to 90° and uses a bracketing method to detect whether the interceptor's trajectory can cross the projectile's at `xi`. Prints the bracketing interval found, or a failure message.

---

## Roadmap

-  Implement additional physical forces such as **wind force**, **air resistance**, to improve simulation realism.
- Define constants `G` and `PI` using `#define` directives in the header file.
- Allow parameters to be passed via command-line arguments (`argc`, `argv`).
- Load initial conditions from a configuration file.
- Add graphical visualization of the interceptor and projectile trajectories.
- Implement a feature to save and load simulation parameters for later use.

---

## License

This project is distributed under the **MIT License**.

---

## Contributors

- Yann RICHARD
- Lucas BASSON

---
## Acknowledgments
We would like to thank our professors at Université Jean Monnet Saint-Étienne for their guidance, support, and valuable feedback throughout the development of this project.

----

## Feedback

For any questions or suggestions, contact us at:
[yann.richard@etu.univ-st-etienne.fr](mailto:yann.richard@etu.univ-st-etienne.fr) or
[lucas.basson@etu.univ-st-etienne.fr](mailto:lucas.basson@etu.univ-st-etienne.fr)
