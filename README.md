*This project has been created as part of the 42 curriculum by paulcard, aamandio.*

# 🎮 Cub3D — Raycasting Engine (Wolfenstein-inspired)

---

## Description

Cub3D is a graphical project inspired by the classic game **Wolfenstein 3D**, widely considered one of the first First-Person Shooter (FPS) games ever created.

The main goal of this project is to build a simple 3D engine using the **raycasting technique**, allowing the player to navigate through a maze from a first-person perspective.

Instead of using a real 3D engine, this project simulates a 3D environment using **mathematics (vectors, angles, and projections)** and a **2D map**, where walls are rendered dynamically based on the player's position and direction.

---

## Features

### Mandatory
- Real-time raycasting rendering.
- Smooth player movement and rotation.
- Wall collision detection.
- Dynamic perspective projection.
- Texture mapping for different wall orientations (North, South, East, West).
- Customizable floor and ceiling colors.

### Bonus
- **Animated Loading Screen**: A custom progress bar that greets the player.
- **Interactive Menu**: Keyboard-navigable main menu with "Game", "About", and "Quit" options.
- **Minimap**: Real-time 2D top-down view of the player's surroundings.
- **Mouse Control**: Look around using the mouse for a more immersive FPS feel.
- **Doors**: Interactive elements within the map (D).

---

## Controls

| Key           | Action            |
| ------------- | ----------------- |
| **W / S**     | Move forward/back |
| **A / D**     | Move left/right   |
| **← / →**     | Rotate view       |
| **Mouse**     | Rotate view (bonus)|
| **ESC**       | Exit game         |

---

## Map Format

The `.cub` file defines the game world. It includes texture paths, colors, and a grid representing the maze layout.

### Example:
```
NO ./assets/textures/north.xpm
SO ./assets/textures/south.xpm
WE ./assets/textures/west.xpm
EA ./assets/textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
10N001
100001
111111
```

- **Characters**: `1` (Wall), `0` (Empty Space), `N/S/E/W` (Player Start & Direction).

---

## How It Works (Simplified)

For each vertical stripe of the screen:
1. **Ray Casting**: A ray is cast from the player’s position in the direction of the camera plane.
2. **DDA Algorithm**: The ray travels through the map grid using **Digital Differential Analysis**, jumping from one grid line to the next with minimal calculations.
3. **Hit Detection**: When the ray hits a wall, the distance to the player is calculated.
4. **Projection**: To avoid the fish-eye effect, the perpendicular distance is used to project the wall height onto the screen.
5. **Rendering**: A vertical line is drawn, textured according to which side of the wall was hit.

---

## Architecture & Technical Choices

- **Language**: C
- **Graphics Library**: MiniLibX
- **Algorithm**: DDA (Digital Differential Analysis) for ray-wall intersections.

### Modules:
- **Parsing**: Validates `.cub` files, handles textures, and sanitizes map data.
- **Rendering Engine**: Handles the mathematical calculations and pixel plotting.
- **Input Handling**: Manages keyboard states and mouse movements for smooth controls.
- **Game Loop**: A continuous cycle of updating state and re-rendering frames.

---

## Instructions

### Compilation

```bash
# Clone the repository
git clone https://github.com/paulcard/cub3d.git
cd cub3d

# Compile mandatory version
make

# Compile bonus version
make bonus
```

### Execution

```bash
# Launch mandatory
./cub3D maps/test.cub

# Launch bonus
./cub3D_bonus maps/door_test_bonus.cub
```

---

## Resources

### External References

- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html): The gold standard for understanding raycasting and the DDA algorithm.
- [Permadi Raycasting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/): A classic deep dive into the math behind the projection.
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx): Reference for the 42 graphics library.

### AI Usage

Artificial Intelligence tools were used during the development of this project to support learning and implementation.

**How AI was used:**
- **Conceptual Learning**: Explaining raycasting principles and the DDA algorithm.
- **Mathematics Support**: Understanding vector math, rotation matrices, and perspective projection.
- **Architecture**: Structuring the project modules for better maintainability.

---

## Final Note

This project is a deep dive into low-level graphics programming, forcing the developer to understand how 3D perception can be simulated using mathematics and efficient algorithms. It is not just about building a game — it's about understanding how games work under the hood.
