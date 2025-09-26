/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:47:42 by yel-qori          #+#    #+#             */
/*   Updated: 2025/09/26 13:39:02 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_ray(t_game *game, int start_x, int start_y, int len, int color)
{
    int end_y;
    int y;
    
    end_y = start_y - len;
    y = start_y;
    while (y >= end_y)
    {
        mlx_pixel_put(game->mlx, game->win, start_x, y , color);
        y--;
    }
}

void player_movements(t_game *game, int keysym, t_player *player)
{
    float old_px = player->px;
    float old_py = player->py;
    
    if (keysym == XK_w || keysym == XK_W )
        player->py -= tile_size;
    else if (keysym == XK_s || keysym == XK_S)
        player->py += tile_size;
    else if (keysym == XK_d || keysym == XK_D)
        player->px += tile_size;
    else if (keysym == XK_a || keysym == XK_A)
        player->px -= tile_size;
}

void draw_map(char **arena, int arena_size, t_game *game)
{
    
    t_map map;
    map.row = 0;
    int i;
    int j;
    while (map.row < arena_size)
    {
        map.col = 0;
        while (arena[map.row][map.col] != '\0')
        {
            map.x = map.col * tile_size;
            map.y = map.row * tile_size;
            if (arena[map.row][map.col] == '1')
            {
                i = 0;
                while (i < tile_size)
                {
                    j = 0;
                    while (j < tile_size)
                    {
                        mlx_pixel_put(game->mlx, game->win, map.x + i, map.y + j, 0xFFFFFF);
                        j++;
                    }
                    i++;
                }
            }
            else if (arena[map.row][map.col] == '0')
            {
                i = 0;
                while (i < tile_size)
                {
                    j = 0;
                    while(j < tile_size)
                    {
                        mlx_pixel_put(game->mlx, game->win, map.x + i, map.y + j, 0x000000);
                        j++;
                    }
                    i++;
                }
            }
            map.col++;
        }
        map.row++;
    }
    i = 0;
    while (i < tile_size)
    {
        j = 0;
        while (j < tile_size)
        {
            mlx_pixel_put(game->mlx, game->win, game->player.px + i, game->player.py + j, 0xFF0000); // Red color for the player
            j++;
        }
        i++;
    }
}
// void player(t_game *game, char **arena)
// {
//     int totals_raws = get_totals_rows(arena);
//     int total_columns = get_totals_colums(arena, totals_raws);
//     int center_row = totals_raws / 2;
//     int center_col = total_columns / 2;
//     int i = 0;
//     int player_x = center_col * 32;
//     int player_y = center_row * 32;
//     while (i < 10)
//     {
//         int j = 0;
//         while (j < 10)
//         {
//             mlx_pixel_put(game->mlx, game->win, player_x + i, player_y + j, 0xFF0000);
//             j++;
//         }
//         i++;
//     }
// }