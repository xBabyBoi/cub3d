/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:58:21 by yel-qori          #+#    #+#             */
/*   Updated: 2025/09/25 13:53:18 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
    game->frame.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->frame.addr = mlx_get_data_addr(game->frame.img, &game->frame.bpp, &game->frame.line_len, &game->frame.endian);
    game->arena = NULL;
    game->arena_size = 0;
}

int main()
{
    t_game game;
    char *line;
    char **arena = NULL;
    int arena_size = 0;
    
    init_game(&game);
    
    int fd = open("map", O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Unable to open map file\n");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        char **tmp = malloc((arena_size + 1) * sizeof(char *));
        if (arena)
        {
            int i = 0;
            while (i < arena_size)
            {
                tmp[i] = arena[i];
                i++;
            }
            free(arena);
        }
        tmp[arena_size] = line;
        arena = tmp;
        arena_size++;
    }
    close(fd);
    game.arena = arena;
    game.arena_size = arena_size;
    if (arena_size > 0)
    {
        int total_rows = arena_size;
        int total_columns = ft_strlen(arena[0]);
        if (arena[0][total_columns - 1] == '\n')
            total_columns--;
        game.player.px = (total_columns / 2) * tile_size;
        game.player.py = (total_rows / 2) * tile_size;
    }
    draw_map(game.arena, game.arena_size, &game);
    
    mlx_key_hook(game.win, key_handler, &game);
    mlx_hook(game.win, 17, 1L<<17, close_handler, &game); // DestroyNotify event
    mlx_loop(game.mlx);
    int i = 0;
    while (i < arena_size)
    {
        free(arena[i]);
        i++;
    }
    free(arena);
    return (0);
}