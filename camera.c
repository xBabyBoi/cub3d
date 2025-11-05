/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:25:03 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/09 10:25:15 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void rotate_camera(t_game *game, double angle)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = game->player.dirX;
	oldPlaneX = game->camera.planeX;

	game->player.dirX = game->player.dirX * cos(angle) - game->player.dirY * sin(angle);
	game->player.dirY = oldDirX * sin(angle) + game->player.dirY * cos(angle);

	game->camera.planeX = game->camera.planeX * cos(angle) - game->camera.planeY * sin(angle);
	game->camera.planeY = oldPlaneX * sin(angle) + game->camera.planeY * cos(angle);
}

