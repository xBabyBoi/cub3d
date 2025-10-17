/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:23:56 by outourmi          #+#    #+#             */
/*   Updated: 2025/09/11 12:56:20 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_start(char *s, char *set)
{
	int	strt;
	int	y;

	strt = 0;
	while (s[strt])
	{
		y = 0;
		while (set[y])
		{
			if (s[strt] == set[y])
				break ;
			y++;
		}
		if (set[y] == '\0')
			break ;
		strt++;
	}
	return (strt);
}

int	ft_end(char *s, char *set)
{
	int	end;
	int	y;

	end = ft_strlen(s) - 1;
	while (end >= 0)
	{
		y = 0;
		while (set[y])
		{
			if (s[end] == set[y])
				break ;
			y++;
		}
		if (set[y] == '\0')
			break ;
		end--;
	}
	return (end);
}


char	*ft_strtrim(char *s1, char *set)
{
	int		strt;
	int		end;
	int		len;
	int		j;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	strt = ft_start(s1, set);
	end = ft_end(s1, set);
	j = 0;
	len = end - strt + 1;
	if (strt > end)
		return (ft_strdup(""));
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (str);
	while (strt <= end)
	{
		str[j] = s1[strt];
		strt++;
		j++;
	}
	str[len] = '\0';
	return (str);
}
