/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:30:49 by outourmi          #+#    #+#             */
/*   Updated: 2025/09/11 13:03:58 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    s_cub_info *info;
    info = malloc(sizeof(s_cub_info) + 1);
    char *line;
    int i;
    int line_count;
    int fd;
    
    i = 0;
    if(ac == 2)
    {
        if(format_check(av[1], ".cub") == 1)
            return(printf("Invalid format\n"));
        fd = open(av[1], O_RDONLY);
        if(fd == -1)
            return(printf("Map not found\n"));
        line_count = count_lines(fd);
        close(fd);
        fd = open(av[1], O_RDONLY);
        info->map = malloc(sizeof(char *) * (line_count + 1));
        while((line = get_next_line(fd)))
            info->map[i++] = line;
        info->map[i] = NULL;
        close(fd);
    }
    else
        return(printf("Invalid Arguments\n"));
    map_info(info);
    map_parsing(info);
    if (!validate_map_closure(info))
        return (printf("Map validation failed\n"));
    i = 0;
    while (info->map[i])
    {
        printf("%s", info->map[i]);
        i++;
    }
    return(0);
}
