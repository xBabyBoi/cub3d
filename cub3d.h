/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:07:10 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/02 16:24:43 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>        // Add this for open()
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "get_next_line.h"

#define HEIGHT 1920
#define WIDTH  1080


#ifndef tile_size
# define tile_size 32
#endif

typedef struct s_player
{
    float px;
    float py;
    int position;
    int dirX;
    int dirY;
    int speed;
} t_player;


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
}   t_game; 


int key_handler(int keysym, t_game *game);
int close_handler(t_game *game);
void draw_map(char **mape, int map_size, t_game *game);
int get_totals_rows(char **arena);
int get_totals_colums(char **arena, int rows);
int is_valid_map_line(char *line);
void player(t_game *game, char **arena);
void player_movements(t_game *game, int keysym, t_player *player);
void calculate_next_position(t_game *game, t_player *player, int keysym);
int can_move_to(t_game *game, float px, float py);
int get_direction(t_game *game);

#endif