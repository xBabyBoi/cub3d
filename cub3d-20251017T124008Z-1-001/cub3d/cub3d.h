/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:34:42 by outourmi          #+#    #+#             */
/*   Updated: 2025/09/11 12:58:11 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "Get_next_line/get_next_line.h"
#include <stdio.h>
#include <string.h>

typedef struct s_playerinfo
{
    int x;
    int y;
    char f;
} s_playerinfo;

typedef struct s_cub_info
{
    // int width;
    // int height;
    char **map;
    char *north;
    char *south;
    char *east;
    char *west;
    char *floor_color;
    char *ceiling_color;
    s_playerinfo *player;
} s_cub_info;

int validate_map_closure(s_cub_info *info);
int parse_textures(s_cub_info *info);
int count_lines(int fd);
int	ft_atoi(char *str);
int map_info(s_cub_info *info);
int map_parsing(s_cub_info *info);
int	ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
// int format_check(char *str);
int format_check(char *str,char *format);
char	*ft_strcpy(char *dest, char *src);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *s);
int	ft_atoi(char *str);

#endif