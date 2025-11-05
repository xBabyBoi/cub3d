
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:13:03 by outourmi          #+#    #+#             */
/*   Updated: 2024/11/23 17:30:15 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while ((char)c != s[i])
	{
		if (!s[i])
		{
			return (NULL);
		}
		s++;
	}
	return ((char *)s);
}

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = 0;
	while (src[len])
	{
		len++;
	}
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
	{
		return (NULL);
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	length;
	char	*result;

	i = 0;
	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	if (start >= length)
		return (NULL);
	if (length - start < len)
	{
		len = length - start;
	}
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		h;
	int		len;
	char	*ss;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	h = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	ss = malloc((len + 1) * sizeof(char));
	if (ss == NULL)
		return (NULL);
	while (s1[h])
	{
		ss[i++] = s1[h++];
	}
	h = 0;
	i = ft_strlen(s1);
	while (s2[h])
	{
		ss[i++] = s2[h++];
	}
	ss[i] = '\0';
	return (ss);
}
