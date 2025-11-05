/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:05:49 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/19 17:56:13 by outourmi         ###   ########.fr       */
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
        // printf("Ray %d: raydirX = %f, raydirY = %f\n", i, game->camera.raydirX[i], game->camera.raydirY[i]);
        i++;
    }
}

// void raycasting(t_game *game)
// {
//     int x;
//     t_ray ray;

//     x = 0;
//     while (x < WIDTH)
//     {
//         init_rays(game, &ray, x);
//         check_hit_wall(game , &ray);
        
//     }
// }

void draw_ray(t_game *game)
{
    int i;
    int ray_len;
    // int end_x;
    // int end_y;
    float step_x;
    float step_y;
    int steps;
    
    i = 0;
    ray_len = 400;  // Increase ray length
    while (i < WIDTH)
    {
        // int end_x = game->player.px + game->camera.raydirX[i] * ray_len;    
        // int end_y = game->player.py + game->camera.raydirY[i] * ray_len;

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

void calculate_wall_distance(t_game *game, t_ray *ray)
{
    double posX = game->player.px / tile_size;
    double posY = game->player.py / tile_size;
    if (ray->side == 0)
        ray->perpWallDist = (ray->mapX - posX + (1 - ray->stepX) / 2.0) / ray->rayDirX;
    else
        ray->perpWallDist = (ray->mapY - posY + (1 - ray->stepY) / 2.0) / ray->rayDirY;
    if (ray->perpWallDist < 1e-6)
        ray->perpWallDist = 1e-6;
}

void draw_wall_stripe(t_game *game, int x, t_ray *ray)
{
    int lineHeight = (int)(HEIGHT / ray->perpWallDist);
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    int y;
    int color = (ray->side == 0) ? 0xFF0000 : 0x0000FF;
    if (drawStart < 0) drawStart = 0;
    if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
    // ceiling
    y = 0;
    while (y < drawStart)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, 0x87CEEB);
        y++;
    }
    y = drawEnd;
    while(y <= drawEnd)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, color);
        y++;
    }
    // wall
    // floor
    y = drawEnd + 1;
    while (y < HEIGHT)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, 0x228B22);
        y++;
    }
    // for (y = drawEnd + 1; y < HEIGHT; ++y)
    //     mlx_pixel_put(game->mlx, game->win, x, y, 0x228B22);
}

void raycast_3d(t_game *game)
{
    int x;
    t_ray ray;

    // Clear and render full 3D frame
    mlx_clear_window(game->mlx, game->win);
    x = 0;
    while (x < WIDTH)
    {
        init_rays(game, &ray, x);
        check_hit_wall(game, &ray);
        calculate_wall_distance(game, &ray);
        draw_wall_stripe(game, x, &ray);
        x++;
    }
}