/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:21:00 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/19 17:56:41 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_rays(t_game *game, t_ray *ray, int x)
{
    double cameraX;

    
    cameraX = 2 * x / (double)WIDTH - 1; // convert screen corrd to 1 -1
    ray->rayDirX = game->player.dirX + game->camera.planeX * cameraX;
    ray->rayDirY = game->player.dirY + game->camera.planeY * cameraX;
    
    ray->mapX = game->player.px / tile_size;
    ray->mapY = game->player.py / tile_size;
    // protect from division by zero
    if (ray->rayDirX == 0)
        ray->deltaDistX = 1e30;
    else
        ray->deltaDistX = fabs(1 / ray->rayDirX);
    if (ray->rayDirY == 0)
        ray->deltaDistY = 1e30;
    else
        ray->deltaDistY = fabs(1 / ray->rayDirY);

    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (game->player.px / tile_size - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - game->player.px / tile_size) * ray->deltaDistX;
    }
    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (game->player.py / tile_size - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - game->player.py / tile_size) * ray->deltaDistY;
    }
}

void check_hit_wall(t_game * game, t_ray *ray)
{
    int hit;

    hit = 0;
    while (hit == 0)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        // Bounds check
        if (ray->mapX < 0 || ray->mapY < 0)
            break;
        if (ray->mapY >= game->arena_size || !game->arena[ray->mapY])
            break;
        if (game->arena[ray->mapY][ray->mapX] == '1')
            hit = 1;
    }
}


