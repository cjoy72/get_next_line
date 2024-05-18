/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoy720 <cjoy720@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:09:33 by cjoy720           #+#    #+#             */
/*   Updated: 2023/12/13 22:20:26 by cjoy720          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*str;
	char		*ret;
	char		*buf;
	static char	*ptr;
	int			out;

	out = -69;
	while ((out > 0 && ptr) || out == -69)
	{
		str = gnl_alloc(BUFFER_SIZE + 1, sizeof(char));
		if (!str)
			break ;
		out = read(fd, str, BUFFER_SIZE);
		buf = f_strjoin(ptr, str);
		ptr = buf;
		ret = gnl_line(ptr);
		if (sl(ret) > 0
			&& (ret[sl(ret) - 1] == '\n' || (out < BUFFER_SIZE && out >= 0)))
		{
			ptr += sl(ret) + (*buf == 127);
			return (ret);
		}
		free(ret);
	}
	return (gnl_clean(buf, &ptr));
}

/*
int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("file.txt", O_RDONLY);
	i = 0;
	while (i++ < 6)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	return (0);
}
*/