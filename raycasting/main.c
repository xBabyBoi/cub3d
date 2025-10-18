/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:58:21 by yel-qori          #+#    #+#             */
/*   Updated: 2025/10/09 11:24:06 by yel-qori         ###   ########.fr       */
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
    
    // Transfer the map
    game->arena = info->map;
    
    // Count map lines
    i = 0;
    while (info->map[i])
        i++;
    game->arena_size = i;
    
    // Set player position from parsed data
    game->player.px = info->player->x * tile_size;
    game->player.py = info->player->y * tile_size;
    
    // Set direction based on player facing
    if (info->player->f == 'N')
    {
        game->player.dirX = 0;
        game->player.dirY = -1;
        game->camera.planeX = 0.6;
        game->camera.planeY = 0;
    }
    else if (info->player->f == 'S')
    {
        game->player.dirX = 0;
        game->player.dirY = 1;
        game->camera.planeX = -0.6;
        game->camera.planeY = 0;
    }
    else if (info->player->f == 'E')
    {
        game->player.dirX = 1;
        game->player.dirY = 0;
        game->camera.planeX = 0;
        game->camera.planeY = 0.6;
    }
    else if (info->player->f == 'W')
    {
        game->player.dirX = -1;
        game->player.dirY = 0;
        game->camera.planeX = 0;
        game->camera.planeY = -0.6;
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
    
    // Validate arguments
    if (ac != 2)
        return (printf("Usage: %s <map.cub>\n", av[0]), 1);
    
    // Check file format
    if (format_check(av[1], ".cub") == 1)
        return (printf("Error: Invalid file format (expected .cub)\n"), 1);
    
    // Allocate info structure
    info = malloc(sizeof(s_cub_info));
    if (!info)
        return (printf("Error: Memory allocation failed\n"), 1);
    
    // Open and read the .cub file
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return (printf("Error: Cannot open file %s\n", av[1]), 1);
    
    // Count lines in file
    line_count = count_lines(fd);
    close(fd);
    
    // Reopen file and read all lines
    fd = open(av[1], O_RDONLY);
    info->map = malloc(sizeof(char *) * (line_count + 1));
    if (!info->map)
        return (printf("Error: Memory allocation failed\n"), 1);
    
    i = 0;
    while ((line = get_next_line(fd)))
        info->map[i++] = line;
    info->map[i] = NULL;
    close(fd);
    
    // Parse the file content
    if (map_info(info) != 0)
        return (printf("Error: Failed to parse map info\n"), 1);
    
    if (map_parsing(info) != 0)
        return (printf("Error: Failed to parse map\n"), 1);
    
    // Validate map closure
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
    
    // Initialize the game
    init_game(&game);
    
    // Transfer parsed data to game structure
    transfer_parsed_data_to_game(&game, info);
    
    // Start the raycasting engine
    draw_map(game.arena, game.arena_size, &game);
    mlx_key_hook(game.win, key_handler, &game);
    mlx_hook(game.win, 17, 1L<<17, close_handler, &game);
    mlx_loop(game.mlx);
    
    return (0);
}