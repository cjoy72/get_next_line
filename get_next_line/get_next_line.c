/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoy720 <cjoy720@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:02:41 by cbaroi            #+#    #+#             */
/*   Updated: 2023/12/10 21:11:36 by cjoy720          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char	*gnl_calloc(int size)
{
	int		i;
	char	*arr;
	
	if (size != 0 && size > ULONG_MAX / size && size <= 0)
		return (NULL);
	arr = (char *)malloc(sizeof(char) * size);
	i = 0;
	while(i < size)
		arr[i++] = '\0';
	return (arr);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*ret;
	char		*buf;
	static char	*ptr = NULL;
	int			out;

	out = -69;
	while ((out > 0 && ptr) || out == -69)
	{
		str = gnl_calloc(BUFFER_SIZE + 1);
		if (!str)
			break;
		out = read(fd, str, BUFFER_SIZE);
		buf = gnl_strjoin(ptr, str);
		ptr = buf;
		ret = get_single_line(ptr);
		if (gnl_strlen(ret) > 0 && (ret[gnl_strlen(ret) - 1] == '\n' || out < BUFFER_SIZE && out >= 0))
		{
			ptr += gnl_strlen(ret) + (*buf == 127);
			return (ret);
		}
		free (ret);
	}
	free(buf);
	ptr = NULL;
	return (NULL);
}

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	get_next_line(fd);
	for (int i = 0; i < 6; i++)
 	{
 		line = get_next_line(fd);
 		printf("%s", line);
 		free(line);
 	}
    
	return (0);
}