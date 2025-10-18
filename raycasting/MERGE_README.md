# Parsing Integration into Raycasting

## Summary
The parsing code has been successfully merged into the raycasting directory without modifying any raycasting logic or files.

## Changes Made

### 1. Files Copied from `parsing/` to `raycasting/`:
- `map_parsing.c` - Map parsing and extraction logic
- `map_validation.c` - Map validation and flood fill algorithm
- `map_info.c` - Texture and color information parsing
- `utils.c` - Utility functions (ft_atoi, ft_strcmp, ft_strncmp, format_check, etc.)
- `ft_strtrim.c` - String trimming function
- `ft_itoa.c` - Integer to string conversion
- `Get_next_line/` - Directory with get_next_line implementation for parsing

### 2. Header File Updated (`cub3d.h`):
Added parsing-related structures and function declarations:

#### New Structures:
```c
typedef struct s_playerinfo
{
    int x;
    int y;
    char f;
} s_playerinfo;

typedef struct s_cub_info
{
    char **map;
    char *north;
    char *south;
    char *east;
    char *west;
    char *floor_color;
    char *ceiling_color;
    s_playerinfo *player;
} s_cub_info;
```

#### New Function Declarations:
- `int validate_map_closure(s_cub_info *info);`
- `int parse_textures(s_cub_info *info);`
- `int count_lines(int fd);`
- `int ft_atoi(char *str);`
- `int map_info(s_cub_info *info);`
- `int map_parsing(s_cub_info *info);`
- `int ft_strcmp(char *s1, char *s2);`
- `char *ft_itoa(int n);`
- `int format_check(char *str, char *format);`
- `char *ft_strcpy(char *dest, char *src);`
- `int ft_strncmp(char *s1, char *s2, unsigned int n);`
- `char *ft_strtrim(char *s1, char *set);`
- `char *ft_strdup(const char *src);`
- `size_t ft_strlen(const char *s);`

### 3. Makefile Updated:
Added parsing source files to the compilation list:
```makefile
SRC = main.c\
	draw_map.c\
	get_next_line_utils.c\
	get_next_line.c\
	helper_functions.c\
	keys_handler.c\
	movements.c\
	raycasting.c\
	map_parsing.c\
	map_validation.c\
	map_info.c\
	utils.c\
	ft_strtrim.c\
	ft_itoa.c\
	Get_next_line/get_next_line.c\
	Get_next_line/get_next_line_utils.c
```

### 4. Symbolic Link Created:
Created a symbolic link `minilibx-linux` pointing to `../minilibx_mms_20191025_beta` for easier minilibx access.

## Parsing Functions Available

### `map_info(s_cub_info *info)`
- Extracts texture identifiers (NO, SO, WE, EA, F, C) from the map file
- Validates that each identifier appears exactly once
- Calls `parse_info()` to process the extracted information

### `map_parsing(s_cub_info *info)`
- Extracts the actual map from the config file
- Validates map characters (only N, S, E, W, 1, 0, space, tab allowed)
- Checks for player position (exactly one N/S/E/W required)
- Updates `info->map` with the clean map data

### `validate_map_closure(s_cub_info *info)`
- Validates that the map is properly enclosed by walls
- Uses flood fill algorithm to ensure player cannot escape
- Checks that all walkable spaces (0) and player positions are surrounded by valid cells

### `parse_color(char *str)`
- Converts RGB color strings to hexadecimal format
- Validates RGB values are in range [0, 255]

### `format_check(char *str, char *format)`
- Checks if a filename has the correct extension
- Used to validate .cub and .xpm file formats

## Integration Notes

### Raycasting Files (UNCHANGED):
- All raycasting `.c` files remain unmodified
- Raycasting structures (`t_game`, `t_player`, `t_camera`, `t_ray`, etc.) are preserved
- All raycasting functions work as before

### Parsing Structures:
- `s_cub_info` - Holds all configuration and map data from .cub file
- `s_playerinfo` - Stores player starting position and facing direction

### Usage Pattern:
To use the parsing in your main program:
```c
s_cub_info *info;
info = malloc(sizeof(s_cub_info));

// Read .cub file into info->map
// ... (file reading code)

// Parse the file
map_info(info);        // Extract textures and colors
map_parsing(info);     // Extract and validate map
validate_map_closure(info);  // Ensure map is enclosed

// Now info contains:
// - info->north, south, east, west (texture paths)
// - info->floor_color, ceiling_color (hex colors)
// - info->map (2D array of map data)
// - info->player (x, y, facing direction)
```

## Compilation Status

The code structure is complete, but compilation requires:
1. Linux MLX (minilibx-linux) with proper X11 support, OR
2. Adapting the code to use Mac MLX (minilibx_mms)

Currently, the raycasting code uses Linux MLX with X11 keysyms (XK_w, XK_Escape, etc.), but only Mac MLX is available in the workspace.

## Next Steps

To complete the integration and make it runnable:

1. **Either**: Install proper Linux MLX
   ```bash
   cd /mnt/c/Users/youssef/Desktop/cub33d
   git clone https://github.com/42Paris/minilibx-linux.git
   cd minilibx-linux
   make
   ```

2. **Or**: Adapt the code to use Mac MLX keycodes instead of X11 keysyms

3. **Update main.c** to use parsing functions:
   - Read .cub file (command line argument)
   - Parse with `map_info()` and `map_parsing()`
   - Validate with `validate_map_closure()`
   - Transfer data to `t_game` structure
   - Launch raycasting engine

4. **Compile**: Once MLX is properly set up:
   ```bash
   cd raycasting
   make
   ```

## File Structure

```
raycasting/
├── cub3d.h                    # Updated with parsing declarations
├── Makefile                   # Updated with parsing sources
├── main.c                     # (Raycasting - unchanged)
├── draw_map.c                 # (Raycasting - unchanged)
├── raycasting.c               # (Raycasting - unchanged)
├── keys_handler.c             # (Raycasting - unchanged)
├── movements.c                # (Raycasting - unchanged)
├── helper_functions.c         # (Raycasting - unchanged)
├── get_next_line.c            # (Raycasting - unchanged)
├── get_next_line.h            # (Raycasting - unchanged)
├── get_next_line_utils.c      # (Raycasting - unchanged)
├── map_parsing.c              # NEW - From parsing
├── map_validation.c           # NEW - From parsing
├── map_info.c                 # NEW - From parsing
├── utils.c                    # NEW - From parsing
├── ft_strtrim.c               # NEW - From parsing
├── ft_itoa.c                  # NEW - From parsing
└── Get_next_line/             # NEW - From parsing
    ├── get_next_line.c
    ├── get_next_line.h
    └── get_next_line_utils.c
```
