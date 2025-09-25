/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:47:41 by yel-qori          #+#    #+#             */
/*   Updated: 2025/09/25 13:49:58 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_handler(t_game *game)
{
    printf("Closing game...\n");
    mlx_destroy_image(game->mlx, game->frame.img);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    exit(0);
}

int key_handler(int keysym, t_game *game)
{
    printf("Key pressed: %d\n", keysym);
    
    if (keysym == XK_Escape || keysym == 65307) // ESC key
    {
        close_handler(game);
    }
    else if (keysym == XK_w || keysym == XK_W || keysym == 119 || keysym == 87 ||  // W key
             keysym == XK_s || keysym == XK_S || keysym == 115 || keysym == 83 ||  // S key  
             keysym == XK_a || keysym == XK_A || keysym == 97 || keysym == 65 ||   // A key
             keysym == XK_d || keysym == XK_D || keysym == 100 || keysym == 68)    // D key
    {
        printf("Movement key detected! Current pos: px=%f, py=%f\n", 
               game->player.px, game->player.py);
               
        player_movements(game, keysym, &game->player);
        
        printf("New position: px=%f, py=%f\n", 
               game->player.px, game->player.py);
               
        draw_map(game->arena, game->arena_size, game);
    }
    return (0);
}
