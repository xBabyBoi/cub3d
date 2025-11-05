/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:01:46 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/19 18:09:07 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int row_len_no_nl(const char *s)
{
    int i = 0;
    while (s && s[i] && s[i] != '\n')
        i++;
    return i;
}

int can_move_to(t_game *game, float px, float py)
{
    int grid_x;
    int grid_y;

    grid_x = (int)(px / tile_size);
    grid_y = (int)(py / tile_size);
    if (grid_y < 0 || grid_y >= game->arena_size)
    return 0;

    int row_w = row_len_no_nl(game->arena[grid_y]);
    if (grid_x < 0 || grid_x >= row_w)
        return 0;

    char cell = game->arena[grid_y][grid_x];
    if (cell == '1' || cell == ' ')
        return 0;
    return 1;
}
 
void calculate_next_position(t_game *game, t_player *player, int keysym)
{
    double dx = 0.0;
    double dy = 0.0;
    double step = (double)player->speed;

    // Camera-relative movement
    if (keysym == XK_w || keysym == XK_W)
    {
        dx = game->player.dirX;
        dy = game->player.dirY;
    }
    else if (keysym == XK_s || keysym == XK_S)
    {
        dx = -game->player.dirX;
        dy = -game->player.dirY;
    }
    else if (keysym == XK_a || keysym == XK_A)
    {
        dx = -game->camera.planeX;
        dy = -game->camera.planeY;
    }
    else if (keysym == XK_d || keysym == XK_D)
    {
        dx = game->camera.planeX;
        dy = game->camera.planeY;
    }

    // Normalize to keep speed consistent regardless of FOV
    double mag = sqrt(dx * dx + dy * dy);
    if (mag > 0.000001)
    {
        dx /= mag;
        dy /= mag;
    }

    // Attempt axis-separated movement to slide along walls
    double try_px = player->px + dx * step;
    double try_py = player->py + dy * step;

    if (can_move_to(game, try_px, player->py))
        player->px = try_px;
    if (can_move_to(game, player->px, try_py))
        player->py = try_py;
}

void clear_window(t_game *game)
{
    mlx_clear_window(game->mlx, game->win);
}