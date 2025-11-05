/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:07:10 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/18 18:43:58 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
# include "/home/youssef/Desktop/cub3d/minilibx-linux/mlx.h"
# include <math.h>
# include "get_next_line/get_next_line.h"

#ifndef XK_Escape
# define XK_Escape 0xff1b
# define XK_w 0x0077
# define XK_W 0x0057
# define XK_a 0x0061
# define XK_A 0x0041
# define XK_s 0x0073
# define XK_S 0x0053
# define XK_d 0x0064
# define XK_D 0x0044
 # define XK_Left  0xff51
 # define XK_Right 0xff53
#endif

#define HEIGHT 600
#define WIDTH  800
// Field of view in degrees (wider FOV -> larger camera plane)
#define FOV 60


#ifndef tile_size
# define tile_size 32
#endif

typedef struct s_player
{
    float px;
    float py;
    int position;
    double dirX;
    double dirY;
    int speed;
} t_player;

typedef struct s_camera
{
    float planeX;
    float planeY;
    double raydirX[WIDTH];
    double raydirY[WIDTH];
} t_camera;


typedef struct s_map
{
    int x;
    int y;
    int row;
    int col;
} t_map;

typedef struct s_img
{
    void *img;      //the mlx image
    char *addr;     // pointer to pixel memory
    int bpp;        // bits used for each pixel
    int line_len;   // numbers of bytes for one raw of pixels
    int endian;
}   t_img;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *image;
    t_img frame;
    t_img textures[4]; // N S E W
    t_player player;
    char **arena;      // Add arena storage
    int arena_size;    // Add arena size storage
    t_camera camera;
}   t_game; 


typedef struct s_ray
{
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit;
    int side;
} t_ray;

// Parsing structures
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

// Raycasting functions
int key_handler(int keysym, t_game *game);
int close_handler(t_game *game);
void draw_map(char **mape, int map_size, t_game *game);
int get_totals_rows(char **arena);
int get_totals_colums(char **arena, int rows);
int is_valid_map_line(char *line);
void player(t_game *game, char **arena);
void player_movements(t_game *game, int keysym);
void calculate_next_position(t_game *game, t_player *player, int keysym);
int can_move_to(t_game *game, float px, float py);
int get_direction(t_game *game);
void ray_direction(t_game *game);
void draw_ray(t_game *game);
void clear_window(t_game *game);
void rotate_camera(t_game *game, double angle);
void init_rays(t_game *game, t_ray *ray, int x);
void check_hit_wall(t_game * game, t_ray *ray);
void calculate_wall_distance(t_game *game, t_ray *ray);
void draw_wall_stripe(t_game *game, int x, t_ray *ray);
void raycast_3d(t_game *game);

// Parsing functions
int validate_map_closure(s_cub_info *info);
int parse_textures(s_cub_info *info);
int count_lines(int fd);
int	ft_atoi(char *str);
int map_info(s_cub_info *info);
int map_parsing(s_cub_info *info);
int	ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
int format_check(char *str,char *format);
char	*ft_strcpy(char *dest, char *src);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strtrim(char *s1, char *set);
// ft_strdup and ft_strlen are already declared in get_next_line.h

#endif