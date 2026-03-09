# CUB3D — 3D Raycasting Engine


M4UU5-4CDCC-MDDC3-3U5GA-BDRB3



**42 School project (42 Kocaeli)** · A Wolfenstein 3D–style first-person 3D maze game written in C. The engine is implemented from scratch (raycasting, texture mapping, input handling) with no external 3D libraries.

---

## About the Project

CUB3D is a project from the **42 School** Graphics/Algorithms track. The goal is to read map and visual settings from a `.cub` configuration file, produce a real-time 3D view using **raycasting**, and let the player move with WASD and arrow keys. The game is rendered in a window using **MiniLibX**.

This project can be used in a portfolio to showcase **gameplay programming** and **low-level graphics/game loop** experience.

---

## Key Techniques (Gameplay / Engine)

### Raycasting & 3D Rendering
- **DDA (Digital Differential Analyzer) raycasting**: For each screen column, a ray is cast into the grid; the algorithm finds where the ray first hits a wall and computes the perpendicular wall distance.
- **Perspective correction**: Wall height (`wall_height = SCREEN_HEIGHT / perp_wall_dist`) and on-screen start/end pixel range are derived from wall distance.
- **Direction-based texture selection**: The correct wall texture (N/S/E/W) is chosen based on which face was hit, giving a sense of orientation.

### Texture Mapping
- **Wall texture mapping**: The hit point on the wall is converted to texture coordinates; the wall strip is drawn by sampling the texture vertically.
- **Ceiling / floor**: Single RGB colors for ceiling and floor, read from the config.
- **64×64 XPM textures**; pixel read via `get_image_color`, write via `put_pixel_to_mlx_image` on the image buffer.

### Player & Camera
- **2D vectors**: `position`, `direction`, and `camera_plane` (for FOV) stored in double precision.
- **Movement**: Forward/back with `direction` (W/S), strafe with `camera_plane` (A/D); **collision** is checked against the grid each step to prevent walking through walls.
- **Rotation**: A **rotation matrix** using `cos`/`sin` is applied to both `direction` and `camera_plane` so FOV stays consistent.
- **Initial orientation**: Player position and facing are set from the `N`/`S`/`E`/`W` character on the map.

### Map & Data
- **.cub parser**: Texture paths (NO/SO/EA/WE), ceiling and floor colors (F/C RGB), then a 2D character map (1=wall, 0=empty, N/S/E/W=player spawn).
- **Map validation**: Valid characters, exactly one player, **closed map** (border check plus **DFS** to ensure the playable area does not leak outside).
- **Grid-based collision**: Before moving, the target cell is checked for `'1'`; movement is allowed only into valid cells.

### Game Loop & Input
- **MLX hooks**: Key state (W/A/S/D, left/right arrows) is stored in a struct via `ON_KEYDOWN`/`ON_KEYUP`; inside **mlx_loop_hook**, movement, raycasting, and screen update run only when at least one key is pressed (no redundant redraws).
- **Clean shutdown**: Window close or ESC frees all allocations (`free_cub3d`).

### Code Structure
- **Modular C**: config, game, raycasting, player, and MLX helpers in separate files; central `t_cub3d` and sub-structs (`t_config`, `t_game`, `t_player`, `t_ray`, `t_screen`).
- **42 norm**: `-Wall -Wextra -Werror` and norminette-compliant style.
- **Cross-platform key codes**: Separate key defines for `__linux__` and `__APPLE__`.

---

## Tech Stack

| Area | Used |
|------|------|
| Language | C |
| Graphics / Window | MiniLibX (42's official graphics library) |
| Compiler | gcc (`-Wall -Wextra -Werror`) |
| Platform | macOS (Darwin), Linux |

---

## Features

- Real-time **raycasting** 3D maze view
- **Directional wall textures** (North/South/East/West)
- **WASD** movement, **arrow keys** for turning
- Load map, textures, and ceiling/floor colors from **.cub** files
- Map validation: closed walls, single player, valid characters
- **1920×1080** resolution (configurable in header)
- **Collision** so the player cannot walk through walls
- Clean **memory management** and exit behavior

---

## Controls

| Key | Action |
|-----|--------|
| **W** | Forward |
| **S** | Backward |
| **A** | Strafe left |
| **D** | Strafe right |
| **← / →** | Turn left / right |
| **ESC** | Quit |

---

## Build & Run

**Requirements:** `make`, `gcc`, MiniLibX.

- **macOS:** MiniLibX is in `mlx/` (OpenGL/AppKit).
- **Linux:** You need **minilibx-linux** once. From the `cub3d/` folder:

```bash
git clone https://github.com/42Paris/minilibx-linux mlx_linux
```

Then build and run:

```bash
cd cub3d
make
./cub3D maps/map0.cub
```

Use any valid `.cub` (e.g. `maps/mandatory.cub` or `maps/map0.cub`).

---

## .cub File Format (Brief)

- **NO / SO / EA / WE**: North/South/East/West wall texture (XPM path).
- **F / C**: Floor and ceiling color (e.g. `F 120,164,75`).
- Then the **map**: `1` = wall, `0` = empty, `N`/`S`/`E`/`W` = player spawn. The map can be separated by blank lines; the parser handles it.

---

## Project Structure (Overview)

```
cub3d/
├── Makefile
├── mlx/                    # MiniLibX (macOS)
├── mlx_linux/              # MiniLibX for Linux (clone 42Paris/minilibx-linux)
├── src/
│   ├── mandatory/
│   │   ├── config/         # .cub read, parse, map validation (incl. DFS)
│   │   ├── game/           # MLX, player, raycasting, textures, input loop
│   │   ├── cub3d.h
│   │   ├── main.c
│   │   ├── init_free_cub3d.c
│   │   └── print_error.c
│   └── utilities/          # ft_*, free_double_pointer, etc.
├── maps/                   # Example .cub maps
├── textures/               # 64×64 XPM wall textures (NO/SO/EA/WE)
└── tools/                  # Optional (e.g. resize_xpm_to_64.py)
```

---

## 42 Project Note

This project is **CUB3D** in the **42 Kocaeli** (and general 42 network) curriculum. The aim is to gain experience in C graphics programming, file parsing, memory management, and a simple game loop. Evaluation (norm, leaks, error messages, etc.) follows 42's official CUB3D subject.

---

## Contact

Feel free to reach out for questions or portfolio-related links.
