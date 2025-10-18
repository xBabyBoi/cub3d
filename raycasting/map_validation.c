#include "cub3d.h"

static int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static int	get_line_length(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

static int	get_map_width(char **map)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		current_width = get_line_length(map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

static char	**duplicate_map(char **map, int height, int width)
{
	char	**copy;
	int		i;
	int		j;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = malloc(sizeof(char) * (width + 1));
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		j = 0;
		while (map[i][j] && map[i][j] != '\n' && j < width)
		{
			copy[i][j] = map[i][j];
			j++;
		}
		while (j < width)
			copy[i][j++] = ' ';
		copy[i][j] = '\0';
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_map_copy(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	flood_fill(char **map, int y, int x, int max_y, int max_x)
{
	if (y < 0 || x < 0 || y >= max_y)
		return (0);
	if (x >= max_x || !map[y][x] || map[y][x] == '\n')
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1')
		return (1);
	if (map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill(map, y - 1, x, max_y, max_x))
		return (0);
	if (!flood_fill(map, y + 1, x, max_y, max_x))
		return (0);
	if (!flood_fill(map, y, x - 1, max_y, max_x))
		return (0);
	if (!flood_fill(map, y, x + 1, max_y, max_x))
		return (0);
	return (1);
}

static int	is_valid_neighbor(char **map, int y, int x, int height)
{
	int	line_len;

	if (y < 0 || y >= height)
		return (0);
	if (!map[y] || !map[y][x])
		return (0);
	line_len = get_line_length(map[y]);
	if (x >= line_len)
		return (0);
	if (map[y][x] == ' ')
		return (0);
	return (1);
}

static int	check_cell_enclosed(char **map, int y, int x, int height)
{
	if (!is_valid_neighbor(map, y - 1, x, height))
		return (0);
	if (!is_valid_neighbor(map, y + 1, x, height))
		return (0);
	if (!is_valid_neighbor(map, y, x - 1, height))
		return (0);
	if (!is_valid_neighbor(map, y, x + 1, height))
		return (0);
	return (1);
}

static int	validate_all_spaces_enclosed(char **map, int height)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	while (i < height)
	{
		line_len = get_line_length(map[i]);
		j = 0;
		while (j < line_len)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || 
				map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (!check_cell_enclosed(map, i, j, height))
				{
					printf("Error: Walkable space at [%d][%d] is not enclosed\n", i, j);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map_closure(s_cub_info *info)
{
	char	**map_copy;
	int		height;
	int		width;
	int		result;

	if (!info || !info->map || !info->player)
		return (0);
	height = get_map_height(info->map);
	width = get_map_width(info->map);
	if (height == 0 || width == 0)
		return (0);
	if (!validate_all_spaces_enclosed(info->map, height))
		return (0);
	map_copy = duplicate_map(info->map, height, width);
	if (!map_copy)
	{
		printf("Error: Memory allocation failed\n");
		return (0);
	}
	result = flood_fill(map_copy, info->player->y, 
		info->player->x, height, width);
	free_map_copy(map_copy);
	if (!result)
	{
		printf("Error: Map is not properly enclosed - player can escape\n");
		return (0);
	}
	return (1);
}
