#include "cub3d.h"

int count_lines(int fd)
{
    char *line;
    int count = 0;
    
    while((line = get_next_line(fd)))
    {
        count++;
        free(line);
    }
    return count;
}

char *rgb_to_hex(char *r, char *g, char *b)
{
    char *color;
    int value_r;
    int value_g;
    int value_b;
    
    value_r = ft_atoi(r);
    value_g = ft_atoi(g);
    value_b = ft_atoi(b);
    if ((value_r < 0 || value_r > 255) || (value_g < 0 || value_g > 255) || (value_b < 0 || value_b > 255))
        exit(printf("invalid color"));
    color = malloc(9);
    if (!color)
        return NULL;
    color[0] = '0';
    color[1] = 'x';
    color[2] = "0123456789ABCDEF"[value_r / 16];
    color[3] = "0123456789ABCDEF"[value_r % 16];
    color[4] = "0123456789ABCDEF"[value_g / 16];
    color[5] = "0123456789ABCDEF"[value_g % 16];
    color[6] = "0123456789ABCDEF"[value_b / 16];
    color[7] = "0123456789ABCDEF"[value_b % 16];
    color[8] = '\0';
    return (color);
}

char *parse_color(char *str)
{
    char **color;
    char *str1;
    int i;
    int x;
    int j;
    int comp;
    
    color = malloc(3 * sizeof(char*));
    color[0] = malloc(4);
    color[1] = malloc(4);
    color[2] = malloc(4);
    i = 0;
    j = 0;
    x = 1;
    comp = 0;
    while(str[i] && comp < 3)
    {
        if((str[i] < 48 || str[i] > 57) && str[i] != ',' && str[i] != ' ' && str[i] != '\t')
            exit(printf("error\n"));
        if(str[i] == ',')
        {
            color[comp][j] = '\0';
            if(str[i + 1] >= 48 && str[i + 1] <= 57)
                x++;
            comp++;
            j = 0;
        }
        else
        {
            color[comp][j] = str[i];
            j++;
        }
        i++;
    }
    if(x != 3)
        exit(printf("error"));
    color[comp][j] = '\0';
    str1 = rgb_to_hex(color[0], color[1], color[2]);
    return(str1);
}

char *parse_inf(char *str)
{
    str = ft_strtrim(str, " \nNOSOWEAFC");
    return (str);
}

void parse_info(s_cub_info *info)
{
    info->north = parse_inf(info->north);
    info->south = parse_inf(info->south);
    info->west = parse_inf(info->west);
    info->east = parse_inf(info->east);
    info->floor_color = parse_inf(info->floor_color);
    info->ceiling_color = parse_inf(info->ceiling_color);
    info->floor_color = parse_color(info->floor_color);
    info->ceiling_color = parse_color(info->ceiling_color);
    if(format_check(info->north, ".xpm") == 1 || format_check(info->south, ".xpm") == 1 || format_check(info->west, ".xpm") == 1 || format_check(info->east, ".xpm") == 1)
            exit(printf("Invalid texture format\n"));
}

int map_info(s_cub_info *info)
{
    int i = 0;
    int j;
    int no = 0;
    int so = 0;
    int ea = 0;
    int we = 0;
    int f = 0;
    int c = 0;
    
    while(info->map[i])
    {
        j = 0;
        while(info->map[i][j] == ' ' || info->map[i][j] == '\t')
        j++;
        if(ft_strncmp(&info->map[i][j], "NO", 2) == 0)
        {
            info->north = info->map[i];
            no++;
        }
        else if(ft_strncmp(&info->map[i][j], "SO", 2) == 0)
        {
            info->south = info->map[i];
            so++;
        }
        else if(ft_strncmp(&info->map[i][j], "WE", 2) == 0)
        {
            info->west = info->map[i];
            we++;
        }
        else if(ft_strncmp(&info->map[i][j], "EA", 2) == 0)
        {
            info->east = info->map[i];
            ea++;
        }
        else if(ft_strncmp(&info->map[i][j], "F", 1) == 0)
        {
            info->floor_color = info->map[i];
            f++;
        }
        else if(ft_strncmp(&info->map[i][j], "C", 1) == 0)
        {
            info->ceiling_color = info->map[i];
            c++;
        }
        i++;
    }
    if (no != 1 || so != 1 || we != 1 || ea != 1 || f != 1 || c != 1)
        exit(printf("Texture identifier error\n"));
    parse_info(info);
    return(0);
}