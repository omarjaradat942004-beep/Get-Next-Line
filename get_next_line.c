/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajarad <omajarad@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 11:25:57 by omajarad          #+#    #+#             */
/*   Updated: 2026/09/30 15:20:10 by omajarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static int	read_stash(int fd, char **stash)
{
	ssize_t	byte_reader;
	char	*buffer;
	char	*new_stash;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (!*stash || !ft_strchr(*stash, '\n'))
	{
		byte_reader = read(fd, buffer, BUFFER_SIZE);
		if (byte_reader < 0)
			return (free(buffer),-1);
		if (byte_reader == 0)
                	return (free(buffer),0);
		buffer[byte_reader] = '\0';
		new_stash = ft_strjoin(*stash, buffer);
		if (!new_stash)
			return (free(buffer), -1);
		free(*stash);
		*stash = new_stash;
	}
	free(buffer);
	return (1);
}

char    *get_next_line(int fd)
{
	static char	*stash;
	char    *new_stash;
	int	read_buffer;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);
	read_buffer = read_stash(fd, &stash);
	if (read_buffer == -1 ||  !stash ||  !stash[0])
		return (free(stash), stash = NULL , NULL);
	line = ft_extract_fill_line(stash);
	if (!line)
		return (free(stash), stash = NULL , NULL);
	new_stash = saves_update(stash);
	free(stash);
	stash = new_stash;
	return (line);
}

int main()
{
	int	fd;

	fd = open("test.txt",O_RDONLY);
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
}
