/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:05:49 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/03 15:47:33 by yel-qori         ###   ########.fr       */
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
                    game->camera.planeX = 0.6;
                    game->camera.planeY = 0;
                }
                else if (game->arena[i][j] == 'S')
                {
                    game->player.dirX = 0;
                    game->player.dirY = 1;
                    game->camera.planeX = -0.6;
                    game->camera.planeY = 0;
                }
                else if (game->arena[i][j] == 'E')
                {
                    game->player.dirX = 1;
                    game->player.dirY = 0;
                    game->camera.planeX = 0;
                    game->camera.planeY = 0.6;
                }
                else if (game->arena[i][j] == 'W')
                {
                    game->player.dirX = -1;
                    game->player.dirY = 0;
                    game->camera.planeX = 0;
                    game->camera.planeY = -0.6;
                }
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

void ray_direction(t_game *game)
{
    int i;
    double cameraX;

    i = 0;
    while (i < WIDTH)
    {
        cameraX = 2 * i / (double)WIDTH - 1;
        game->camera.raydirX[i] = game->player.dirX + game->camera.planeX * cameraX;
        game->camera.raydirY[i] = game->player.dirY + game->camera.planeY * cameraX;
        printf("Ray %d: raydirX = %f, raydirY = %f\n", i, game->camera.raydirX[i], game->camera.raydirY[i]);
        i++;
    }
}

void draw_ray(t_game *game)
{
    int i;
    int ray_len;
    int end_x;
    int end_y;
    float step_x;
    float step_y;
    int steps;
    
    i = 0;
    ray_len = 400;  // Increase ray length
    while (i < WIDTH)
    {
        end_x = game->player.px + game->camera.raydirX[i] * ray_len;    
        end_y = game->player.py + game->camera.raydirY[i] * ray_len;

        // Draw the line, not just the endpoint
        steps = ray_len;
        step_x = game->camera.raydirX[i];
        step_y = game->camera.raydirY[i];
        
        int j = 0;
        while (j < steps)
        {
            int ray_x = game->player.px + step_x * j;
            int ray_y = game->player.py + step_y * j;
            if (ray_x >= 0 && ray_x < WIDTH && ray_y >= 0 && ray_y < HEIGHT)
                mlx_pixel_put(game->mlx, game->win, ray_x, ray_y, 0x00FF00);
            j++;
        }
        i += 10;  // Draw every 10th ray to make it visible
    }
}