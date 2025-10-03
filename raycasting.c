/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:05:49 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/02 18:21:03 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_direction(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->arena[i])
    {
        j = 0;
        while (game->arena[i][j])
        {
            if (game->arena[i][j] == 'N' || game->arena[i][j] == 'S' || game->arena[i][j] == 'E' || game->arena[i][j] == 'W')
            {
                game->player.px = j * tile_size;
                game->player.py = i * tile_size;
                if (game->arena[i][j] == 'N')
                {
                    game->player.dirX = 0;
                    game->player.dirY = -1;
                }
                else if (game->arena[i][j] == 'S')
                {
                    game->player.dirX = 0;
                    game->player.dirY = 1;
                }
                else if (game->arena[i][j] == 'E')
                {
                    game->player.dirX = 1;
                    game->player.dirY = 0;
                }
                else if (game->arena[i][j] == 'W')
                {
                    game->player.dirX = -1;
                    game->player.dirY = 0;
                }
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

// void init_player_direction(t_game *game, t_player *player)
// {
//     if ()
// }