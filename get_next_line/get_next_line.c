/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaroi <cbaroi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:02:41 by cbaroi            #+#    #+#             */
/*   Updated: 2023/12/08 14:28:37 by cbaroi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

BUFFER_SIZE = 10;

char	get_next_line(int fd)
{
	static char	*static_line;
	int			bytes_read;

	bytes_read = read(fd, static_line, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
}

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	get_next_line(fd);
	return (0);
}
