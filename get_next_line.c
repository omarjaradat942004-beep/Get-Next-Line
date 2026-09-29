/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajarad <omajarad@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 11:25:57 by omajarad          #+#    #+#             */
/*   Updated: 2026/09/29 21:21:33 by omajarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
char    *get_next_line(int fd)
{
	char	*buffer;
	static	ssize_t	n;
	int	x;

	buffer = malloc(sizeof(char) * 10);
	n = read(fd,buffer, 10);
	if (n <= 0)
		return (NULL);
	while (n > 0)
	{
		x = 0;
                while (x < n)
                {
                        if (buffer[x] == '\n')
			{
				buffer[x+1] = '\0';
                                break ;
			}
                        x++;
                }
		if (x < n)
			break;
		n = read(fd,buffer, 10);
	}

	return (buffer);
}

int main()
{
	int	fd;

	fd = open("test.txt",O_RDONLY);
	printf("%s",get_next_line(fd));
}
