/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:01:46 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/02 16:26:58 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int can_move_to(t_game *game, float px, float py)
{
    int grid_x;
    int grid_y;

    grid_x = (int)(px / tile_size);
    grid_y = (int)(py / tile_size);
    if(grid_x < 0 || grid_x >= game->arena_size || grid_y < 0 || grid_y >= game->arena_size)
        return (0);
    if (game->arena[grid_y][grid_x] == '1')
        return (0);
    return (1);
}
 
void calculate_next_position(t_game *game, t_player *player, int keysym)
{
    float next_px;
    float next_py;

    next_px = player->px;
    next_py = player->py;
    int xd = get_direction(game);
    if (keysym == XK_w || keysym == XK_W)
        next_py -= player->speed;
    else if (keysym == XK_s || keysym == XK_S)
        next_py += player->speed;
    else if (keysym == XK_a || keysym == XK_A)
        next_px -= player->speed;
    else if (keysym == XK_d || keysym == XK_D)
        next_px += player->speed;
    if (can_move_to(game, next_px, next_py))
    {
        player->px = next_px;
        player->py = next_py;
    }
}
