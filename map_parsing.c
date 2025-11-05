/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:44:08 by outourmi          #+#    #+#             */
/*   Updated: 2025/10/18 15:56:12 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_identifier_line(char *line)
{
    if (!line)
        return 0;
    while (*line == ' ' || *line == '\t')
        line++;
    if (ft_strncmp(line, "NO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
        return 1;
    if (ft_strncmp(line, "SO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
        return 1;
    if (ft_strncmp(line, "WE", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
        return 1;
    if (ft_strncmp(line, "EA", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
        return 1;
    if (ft_strncmp(line, "F", 1) == 0 && (line[1] == ' ' || line[1] == '\t'))
        return 1;
    if (ft_strncmp(line, "C", 1) == 0 && (line[1] == ' ' || line[1] == '\t'))
        return 1;
    return 0;
}

int is_empty_line(char *line)
{
    if (!line)
        return 1;
    while (*line)
    {
        if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
            return 0;
        line++;
    }
    return 1;
}

char **extract_map(char **lines, int *map_start_idx)
{
    int i = 0;
    while (lines[i] && (is_identifier_line(lines[i]) || is_empty_line(lines[i])))
        i++;
    if (map_start_idx)
        *map_start_idx = i;
    int count = 0, j = i;
    while (lines[j])
    {
        if (!is_empty_line(lines[j]))
            count++;
        j++;
    }
    char **map = malloc((count + 1) * sizeof(char *));
    if (!map)
        return NULL;
    int k = 0;
    j = i;
    while (lines[j])
    {
        if (!is_empty_line(lines[j]))
        {
            map[k++] = lines[j];
        }
        j++;
    }
    map[k] = NULL;
    return map;
}

void check_map(char **map)
{
    int i = 0;
    int count = 0;
    while (map[i])
    {
        int j = 0;
        while (map[i][j] && map[i][j] != '\n')
        {
            if (map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && map[i][j] != '\t')
                count++;
            j++;
        }
        i++;
    }
    if(count != 0)
        exit(printf("invalid map\n"));
}

void check_player(char **map, s_cub_info *info)
{
    int i = 0;
    int count = 0;
    char c;

    if (!info->player)
    {
        info->player = malloc(sizeof(*info->player));
        if (!info->player)
            exit(printf("malloc failed\n"));
    }
    info->player->x = -1;
    info->player->y = -1;
    info->player->f = 0;

    while (map[i])
    {
        int j = 0;
        while (map[i][j] && map[i][j] != '\n')
        {
            c = map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                count++;
                info->player->f = c;
                info->player->y = i;
                info->player->x = j;
            }
            j++;
        }
        i++;
    }
    if (count != 1)
        exit(printf("invalid map\n"));
}

int map_parsing(s_cub_info *info)
{
    int map_start = 0;
    char **map_only = extract_map(info->map, &map_start);
    if (!map_only)
        return 1;
    check_map(map_only);
    check_player(map_only, info);
    info->map = map_only;
    return 0;
}
