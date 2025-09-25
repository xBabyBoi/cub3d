/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:08:04 by yel-qori          #+#    #+#             */
/*   Updated: 2025/09/25 13:18:10 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// size_t ft_strlen(const char *s)
// {
//     size_t len = 0;
//     while (s[len])
//         len++;
//     return (len);
// }

int get_totals_rows(char **arena)
{
    int rows;

    rows = 0;
    while (arena[rows] != NULL)
        rows++;
    return (rows);
}

int get_totals_colums(char **arena, int rows)
{
    int colums;
    size_t len;
    int i;

    i = 0;
    colums = 0;
    while (i < rows)
    {
        len = ft_strlen(arena[i]);
        if (len > 0 && arena[i][len - 1] == '\n')
        {        
            arena[i][len - 1] = '\0';
            len--;
        }
        if (len > colums)
            colums = len;
        i++;
    }
    return (colums);
}

int is_valid_map_line(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
            return (0);
        i++;
    }
    return (1);
}
