/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:47:41 by yel-qori          #+#    #+#             */
/*   Updated: 2025/09/26 16:27:08 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_handler(t_game *game)
{
    printf("Closing game...\n");
    mlx_destroy_image(game->mlx, game->frame.img);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    // free(game->mlx);
    exit(0);
}

int key_handler(int keysym, t_game *game)
{
    printf("Key pressed: %d\n", keysym);
    
    if (keysym == XK_Escape)
        close_handler(game);
    else if (keysym == XK_w || keysym == XK_W ||
             keysym == XK_s || keysym == XK_S || 
             keysym == XK_a || keysym == XK_A || 
             keysym == XK_d || keysym == XK_D)
    {
        calculate_next_position(game, &game->player, keysym);
        // player_movements(game, keysym, &game->player);       
        draw_map(game->arena, game->arena_size, game);
    }
    return (0);
}
