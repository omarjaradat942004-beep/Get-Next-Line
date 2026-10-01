/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajarad <omajarad@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 11:26:34 by omajarad          #+#    #+#             */
/*   Updated: 2026/10/01 14:08:11 by omajarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	index;

	if (!s)
		return (0);
	index = 0;
	while (s[index] != '\0')
	{
		index++;
	}
	return (index);
}

char	*ft_strchr(const char *s, int c)
{
	int	index;

	index = 0;
	while (s[index])
	{
		if (s[index] == (unsigned char)c)
		{
			return ((char *)(s + index));
		}
		index++;
	}
	if ((unsigned char)c == '\0')
	{
		return ((char *)(s + index));
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	index;
	size_t	index2;

	if (!s1)
		s1 = "";
	index = ft_strlen(s1);
	index2 = ft_strlen(s2);
	ptr = malloc ((sizeof(char) * (index + index2)) + 1);
	if (!ptr)
		return (NULL);
	index2 = 0;
	while (s1[index2])
	{
		ptr[index2] = s1[index2];
		index2++;
	}
	index2 = 0;
	while (s2[index2])
		ptr[index++] = s2[index2++];
	ptr[index] = '\0';
	return (ptr);
}

char	*ft_extract_fill_line(char *stash)
{
	size_t	index;
	size_t	length;
	char	*line;

	index = 0;
	while (stash[index] && stash[index] != '\n')
		index++;
	if (stash[index] == '\n')
		index++;
	line = malloc(index + 1);
	if (!line)
		return (NULL);
	length = 0;
	while (length < index)
	{
		line[length] = stash[length];
		length++;
	}
	line[length] = '\0';
	return (line);
}

char	*saves_update(char *buffer)
{
	size_t	index;
	char	*new_buffer;
	size_t	start;
	size_t	length;

	index = 0;
	while (buffer[index] && buffer[index] != '\n')
		index++;
	if (!buffer[index])
		return (NULL);
	start = index + 1;
	length = ft_strlen(&buffer[start]);
	new_buffer = malloc(sizeof(char) * (length + 1));
	if (!new_buffer)
		return (NULL);
	index = 0;
	while (index < length)
	{
		new_buffer[index] = buffer[start + index];
		index++;
	}
	new_buffer[index] = '\0';
	return (new_buffer);
}
