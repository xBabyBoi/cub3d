/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:58:21 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/18 18:59:09 by outourmi         ###   ########.fr       */
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
    game->player.speed = 15;
}

void transfer_parsed_data_to_game(t_game *game, s_cub_info *info)
{
    int i;
    double planeLen;
    const double PI = 3.14159265358979323846;
    planeLen = tan((FOV * (PI / 180.0)) / 2.0);
    
    game->arena = info->map;
    
    i = 0;
    while (info->map[i])
        i++;
    game->arena_size = i;
    
    // Place player at the center of the starting tile to avoid DDA zero-distance artifacts
    game->player.px = (info->player->x + 0.5f) * tile_size;
    game->player.py = (info->player->y + 0.5f) * tile_size;
    
    if (info->player->f == 'N')
    {
        game->player.dirX = 0;
        game->player.dirY = -1;
        game->camera.planeX = planeLen;
        game->camera.planeY = 0;
    }
    else if (info->player->f == 'S')
    {
        game->player.dirX = 0;
        game->player.dirY = 1;
        game->camera.planeX = -planeLen;
        game->camera.planeY = 0;
    }
    else if (info->player->f == 'E')
    {
        game->player.dirX = 1;
        game->player.dirY = 0;
        game->camera.planeX = 0;
        game->camera.planeY = planeLen;
    }
    else if (info->player->f == 'W')
    {
        game->player.dirX = -1;
        game->player.dirY = 0;
        game->camera.planeX = 0;
        game->camera.planeY = -planeLen;
    }
}

int main(int ac, char **av)
{
    t_game game;
    s_cub_info *info;
    char *line;
    int i;
    int line_count;
    int fd;
    
    if (ac != 2)
        return (printf("Usage: %s <map.cub>\n", av[0]), 1);
    if (format_check(av[1], ".cub") == 1)
        return (printf("Error: Invalid file format (expected .cub)\n"), 1);
    info = malloc(sizeof(s_cub_info));
    if (!info)
        return (printf("Error: Memory allocation failed\n"), 1);
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return (printf("Error: Cannot open file %s\n", av[1]), 1);
    line_count = count_lines(fd);
    close(fd);
    fd = open(av[1], O_RDONLY);
    info->map = malloc(sizeof(char *) * (line_count + 1));
    if (!info->map)
        return (printf("Error: Memory allocation failed\n"), 1);
    i = 0;
    while ((line = get_next_line(fd)))
        info->map[i++] = line;
    info->map[i] = NULL;
    close(fd);
    if (map_info(info) != 0)
        return (printf("Error: Failed to parse map info\n"), 1);
    if (map_parsing(info) != 0)
        return (printf("Error: Failed to parse map\n"), 1);
    if (!validate_map_closure(info))
        return (printf("Error: Map validation failed\n"), 1);
    printf("Map parsed successfully!\n");
    printf("Textures:\n");
    printf("  North: %s\n", info->north);
    printf("  South: %s\n", info->south);
    printf("  East: %s\n", info->east);
    printf("  West: %s\n", info->west);
    printf("Floor color: %s\n", info->floor_color);
    printf("Ceiling color: %s\n", info->ceiling_color);
    printf("Player at: (%d, %d) facing %c\n", info->player->x, info->player->y, info->player->f);
    
    init_game(&game);
    transfer_parsed_data_to_game(&game, info);
    draw_map(game.arena, game.arena_size, &game);
    mlx_key_hook(game.win, key_handler, &game);
    mlx_hook(game.win, 17, 1L<<17, close_handler, &game);
    mlx_loop(game.mlx);
    return (0);
}