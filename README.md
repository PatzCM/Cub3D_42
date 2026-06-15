# Cub3D

A raycasting 3D game engine inspired by [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D), built as part of the [42 School](https://42.fr) curriculum. This project renders a first-person perspective of a maze using the DDA (Digital Differential Analyzer) raycasting algorithm with textured walls, a minimap, doors, and mouse-controlled camera movement.

![42 Badge](https://img.shields.io/badge/42-Project-blue)
![Language](https://img.shields.io/badge/Language-C-grey)
![Norminette](https://img.shields.io/badge/Norminette-passing-brightgreen)

---

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building](#building)
  - [Running](#running)
- [Controls](#controls)
- [Map File Format](#map-file-format)
  - [Configuration](#configuration)
  - [Map Section](#map-section)
  - [Example Map](#example-map)
- [Architecture](#architecture)
  - [Project Structure](#project-structure)
  - [Rendering Pipeline](#rendering-pipeline)
  - [Key Data Structures](#key-data-structures)
- [Bonus Features](#bonus-features)
- [Testing](#testing)
- [Dependencies](#dependencies)
- [Authors](#authors)
- [License](#license)

---

## Features

- **Real-time raycasting** engine rendering a 3D perspective from a 2D map
- **Textured walls** with per-pixel XPM texture mapping based on cardinal orientation (N/S/E/W)
- **Configurable floor and ceiling** colors via RGB values
- **Smooth movement** with frame-time-based speed (WASD + strafing)
- **Mouse look** for continuous horizontal camera rotation
- **Collision detection** preventing the player from walking through walls
- **Minimap** displaying a rotated top-down 2D overview
- **Door system** with open/close interaction (bonus)
- **Robust map parser** with comprehensive error handling and validation
- **Fish-eye correction** using perpendicular wall distance

---

## Getting Started

### Prerequisites

- **C Compiler**: GCC or Clang
- **GNU Make**: Build automation
- **X11 development libraries** (Linux):
  ```bash
  # Debian/Ubuntu
  sudo apt-get install libx11-dev libxext-dev libbsd-dev

  # Fedora
  sudo dnf install libX11-devel libXext-devel libbsd-devel
  ```

### Building

```bash
# Clone the repository
git clone --recursive https://github.com/PatzCM/Cub3D_42.git
cd Cub3D_42

# Build the mandatory version
make

# Build with bonus features (doors, minimap, mouse look)
make bonus
```

**Other build targets:**

| Target       | Description                              |
|--------------|------------------------------------------|
| `make all`   | Build the `cub3D` executable             |
| `make bonus` | Build `cub3D_bonus` with extra features  |
| `make clean` | Remove object files                      |
| `make fclean`| Remove all build artifacts               |
| `make re`    | Full clean rebuild                       |
| `make norm`  | Run norminette (42 code style checker)   |

### Running

```bash
# Run with a map file
./cub3D maps/valid/dungeon.cub

# Or with the bonus executable
./cub3D_bonus maps/valid/cheese_maze.cub
```

The program takes a single argument: the path to a `.cub` map file.

---

## Controls

| Key / Input        | Action                |
|--------------------|-----------------------|
| `W`                | Move forward          |
| `S`                | Move backward         |
| `A`                | Strafe left           |
| `D`                | Strafe right          |
| `Left Arrow`       | Rotate camera left    |
| `Right Arrow`      | Rotate camera right   |
| `Mouse (X-axis)`   | Rotate camera         |
| `E`                | Open / close doors    |
| `ESC`              | Exit the game         |

---

## Map File Format

Map files use the `.cub` extension and consist of two sections: configuration directives and the map grid.

### Configuration

Directives can appear in any order before the map. Each must appear exactly once.

| Directive | Format            | Description                          |
|-----------|-------------------|--------------------------------------|
| `NO`      | `NO path/to.xpm`  | North-facing wall texture            |
| `SO`      | `SO path/to.xpm`  | South-facing wall texture            |
| `WE`      | `WE path/to.xpm`  | West-facing wall texture             |
| `EA`      | `EA path/to.xpm`  | East-facing wall texture             |
| `F`       | `F R,G,B`         | Floor color (0-255 per channel)      |
| `C`       | `C R,G,B`         | Ceiling color (0-255 per channel)    |

### Map Section

The map follows the configuration, separated by an empty line. Valid characters:

| Character | Meaning                                      |
|-----------|----------------------------------------------|
| `1`       | Wall                                         |
| `0`       | Empty floor (walkable)                       |
| ` ` (space) | Void / outside the map                    |
| `N`       | Player spawn facing North                    |
| `S`       | Player spawn facing South                    |
| `E`       | Player spawn facing East                     |
| `W`       | Player spawn facing West                     |
| `D`       | Door (bonus only)                            |

**Rules:**
- The map must be completely enclosed by walls (`1`)
- Exactly one player spawn point is required
- Spaces are treated as void and must be surrounded by walls
- The file must have a `.cub` extension

### Example Map

```
NO textures/NORTH.xpm
SO textures/SOUTH.xpm
WE textures/WEST.xpm
EA textures/EAST.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

---

## Architecture

### Project Structure

```
Cub3D_42/
├── Makefile                    # Build configuration
├── incs/
│   ├── cub3d.h                # Main header (structs + prototypes)
│   └── cub3d_bonus.h          # Bonus header
├── srcs/
│   ├── main.c                 # Entry point, MLX loop setup
│   ├── ft_free.c              # Memory cleanup
│   ├── ft_free_map.c          # Map deallocation
│   ├── parsing/               # .cub file parser
│   │   ├── parsing.c          # Main parsing logic
│   │   ├── file_parsing.c     # Texture & color extraction
│   │   ├── flood_fill.c       # Map enclosure validation
│   │   ├── rgb.c              # RGB string to hex conversion
│   │   ├── copy_map.c         # Map grid extraction
│   │   ├── copy_maps_utils.c  # Map copy helpers
│   │   ├── fill_blank.c       # Whitespace normalization
│   │   └── utils.c            # Parsing utilities
│   ├── render/                # Raycasting engine
│   │   ├── ft_frame_render.c  # Main frame render loop (DDA)
│   │   ├── ft_render_line.c   # Vertical line drawing + textures
│   │   ├── ft_render_utils.c  # Raycasting helpers
│   │   ├── ft_render_utils2.c # Additional render helpers
│   │   ├── ft_player_mov.c    # Player movement + rotation
│   │   └── ft_minimap.c       # 2D minimap overlay
│   ├── init/                  # Initialization
│   │   ├── ft_init.c          # Main init routine
│   │   ├── ft_init_tex_player.c # Texture loading + player setup
│   │   └── ft_init_doors.c    # Door system init
│   └── hooks/                 # Input handling
│       └── key_hook.c         # Keyboard + mouse callbacks
├── libs/
│   ├── libft/                 # Custom C library (42 libft)
│   └── mlx/                   # MiniLibX graphics library
├── maps/
│   ├── valid/                 # 39 valid test maps
│   └── invalid/               # 54 invalid maps (error testing)
└── textures/                  # XPM wall/door textures
```

### Rendering Pipeline

1. **Ray casting**: For each vertical screen column (1280 total), a ray is cast from the player's position into the scene
2. **DDA traversal**: The ray steps through the 2D grid, testing each cell for a wall hit
3. **Distance calculation**: Perpendicular distance to the wall is computed (avoiding fish-eye distortion)
4. **Wall height**: The on-screen wall height is derived from the distance (closer = taller)
5. **Texture sampling**: The wall's texture is sampled at the exact intersection point
6. **Column rendering**: A vertical line is drawn with ceiling color above, textured wall in the middle, and floor color below
7. **Minimap overlay**: A rotated 2D grid is rendered in the corner showing the player's position and surroundings

### Key Data Structures

| Structure   | Purpose                                                |
|-------------|--------------------------------------------------------|
| `t_data`    | Main application state (MLX, images, player, map)      |
| `t_ray`     | Per-column raycasting state (direction, distance, hit) |
| `t_player`  | Player position and viewing angle                      |
| `t_map`     | Map grid and dimensions                                |
| `t_map_data`| Parsed .cub file configuration (textures, colors)      |
| `t_mov`     | Input state (movement flags, mouse position)           |
| `t_door`    | Door linked list (position, open state, animation)     |
| `t_img`     | MLX image wrapper (pixel buffer, dimensions)           |

---

## Bonus Features

The bonus version (`make bonus`) adds:

- **Door system** - Doors (`D` in map) that can be opened and closed with the `E` key, rendered with a dedicated texture
- **Minimap** - A real-time 2D overhead view displayed in the corner of the screen, rotating with the player's orientation
- **Mouse look** - Smooth horizontal camera rotation controlled by mouse movement with edge wrapping

---

## Testing

The repository includes extensive test maps:

```bash
# Valid maps (39 files) - should render correctly
./cub3D maps/valid/dungeon.cub
./cub3D maps/valid/cheese_maze.cub
./cub3D maps/valid/library.cub

# Invalid maps (54 files) - should produce error messages
./cub3D maps/invalid/player_none.cub       # No player spawn
./cub3D maps/invalid/wall_hole_north.cub   # Unclosed map
./cub3D maps/invalid/color_invalid_rgb.cub # Bad color values
./cub3D maps/invalid/empty.cub             # Empty file
```

Invalid maps test error handling for:
- Missing/duplicate textures and colors
- Invalid RGB values and formats
- Missing or multiple player spawns
- Unclosed maps (holes in walls)
- Invalid characters in map
- Wrong file extensions
- Broken/missing XPM files

---

## Dependencies

| Library              | Purpose                          | Source                                                        |
|----------------------|----------------------------------|---------------------------------------------------------------|
| **MiniLibX**         | Graphics (X11 window, images)    | [42Paris/minilibx-linux](https://github.com/42Paris/minilibx-linux) |
| **Libft**            | Custom C standard library        | [PatzCM/Libft_42](https://github.com/PatzCM/Libft_42)        |
| **X11 / Xext**       | Windowing system (Linux)         | System package                                                |
| **Math library (-lm)**| Trigonometric functions          | System library                                                |

---

## Authors

- **Patricia Monteiro** ([@PatzCM](https://github.com/PatzCM))

---

## License

This project was developed as part of the 42 School curriculum.
