/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:09 by outourmi          #+#    #+#             */
/*   Updated: 2025/10/18 18:52:59 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line_buffer(int fd, char *left_c, char *buffer)
{
	char	*temp;
	int		b_r;

	if (read(fd, 0, 0) < 0)
	{
		free(left_c);
		return (NULL);
	}
	while (!(fd < 0 || BUFFER_SIZE <= 0))
	{
		b_r = read(fd, buffer, BUFFER_SIZE);
		buffer[b_r] = '\0';
		if (left_c == NULL)
			left_c = ft_strdup(buffer);
		else
		{
			temp = left_c;
			left_c = ft_strjoin(temp, buffer);
			free(temp);
		}
		if (ft_strchr(left_c, '\n') || b_r == 0)
			break ;
	}
	return (left_c);
}

char	*get_next_line(int fd)
{
	static char	*left_c[1024];
	char		*buffer;
	char		*line;
	char		*temp;
	int			i;

	i = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		return (NULL);
	}
	left_c[fd] = fill_line_buffer(fd, left_c[fd], buffer);
	free(buffer);
	if (left_c[fd] == NULL)
	{
		return (NULL);
	}
	while (left_c[fd][i] != '\n' && left_c[fd][i] != '\0')
		i++;
	line = ft_substr(left_c[fd], 0, i + 1);
	temp = ft_substr(left_c[fd], i + 1, ft_strlen(left_c[fd]));
	free(left_c[fd]);
	left_c[fd] = temp;
	return (line);
}