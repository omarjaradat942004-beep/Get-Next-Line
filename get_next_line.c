/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajarad <omajarad@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 11:25:57 by omajarad          #+#    #+#             */
/*   Updated: 2026/10/02 17:19:07 by omajarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_stash(char *stash, char *buffer, int len, ssize_t bytes)
{
	char	*new_stash;

	new_stash = malloc(len + bytes + 1);
	if (!new_stash)
		return (NULL);
	if (stash)
		ft_memcpy(new_stash, stash, len);
	ft_memcpy(new_stash + len, buffer, bytes);
	new_stash[len + bytes] = '\0';
	free(stash);
	return (new_stash);
}

static ssize_t	read_buffer(int fd, char *buffer)
{
	ssize_t	bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes > 0)
		buffer[bytes] = '\0';
	return (bytes);
}

static int	read_stash(int fd, char **stash)
{
	ssize_t	byte_reader;
	char	*buffer;
	char	*new_stash;
	int		length;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (!*stash || !ft_strchr(*stash, '\n'))
	{
		length = 0;
		if (*stash)
			length = ft_strlen(*stash);
		byte_reader = read_buffer(fd, buffer);
		if (byte_reader < 0)
			return (free(buffer), -1);
		if (!byte_reader)
			return (free(buffer), 0);
		new_stash = update_stash(*stash, buffer, length, byte_reader);
		if (!new_stash)
			return (free(buffer), -1);
		*stash = new_stash;
	}
	free(buffer);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*new_stash;
	int			read_status;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_status = read_stash(fd, &stash);
	if (read_status == -1 || !stash || !stash[0])
		return (free(stash), stash = NULL, NULL);
	line = ft_extract_fill_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	new_stash = saves_update(stash);
	free(stash);
	stash = new_stash;
	return (line);
}
