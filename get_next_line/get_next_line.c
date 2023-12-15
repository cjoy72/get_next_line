/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoy720 <cjoy720@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:26:38 by cjoy720           #+#    #+#             */
/*   Updated: 2023/12/15 15:04:34 by cjoy720          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_calloc(int size)
{
	char	*str;
	int		i;

	if (size < 0)
		return (NULL);
	str = malloc(size + 1);
	i = -1;
	while (++i != (size))
		str[i] = '\0';
	return (str);
}

char	*gnl_free(int num, ...)
{
	va_list args;
	int		i;

	va_start(args, num);
	i = -1;
	while (++i < num)
		free (va_arg(args, char *));
	va_end(args);
	return (NULL);
}

char	*gnl_strmv(char *str)
{
	int		size;
	char 	*ret;
	int		i;

	size = gnl_strlen(str);
	ret = gnl_calloc(size);
	i = -1;
	while (str[++i] != '\0')
		ret[i] = str[i];
	ret[i] = '\0';
	str[0] = '\0';
	return (ret);
}

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
		while (str[i] != '\0')
			i++;
	return (i);
}

char	*gnl_append(char *str, char *buffer)
{
	int	i;
	int	str_len;
	char	*ret;

	str_len = gnl_strlen(str);
	ret = gnl_calloc(str_len + BUFFER_SIZE);
	if (!ret)
		return (NULL);
	i = -1;
	while (str[++i] != '\0')
		ret[i] = str[i];
	i = -1;
	while (buffer[++i] != '0')
		ret[str_len + i] = buffer[i];
	ret[str_len + i] = '\0';
	free(str);
	return (ret);
}

void	find_line(char *str, char *rest)
{
	int	i;
	int j;

	i = 0;
	while(str[i] != '\n' && str[i] != '\0')
		++i;
	if (str[i] == '\n')
	{
		str[i++] = '\0';
		while (str[i] != '\0')
		{
			j = 0;
			while (str[i + j] != '\0')
			{
				rest[j] = str[i + j];
				str[i + j] = '\0';
				j++;
			}
			rest[j] = '\0';
		}
	}
}

char	*get_line(int fd,char *str, char *buffer, char *rest)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (gnl_free(1, buffer));
	buffer[bytes_read] = '\0';
	str = gnl_append(str, buffer);
	if (!str)
		return (NULL);
	find_line(str, rest);
	if (rest[0] != '\0')
		get_line(fd, str, buffer, rest);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*str;
	char		*buffer;
	char		*line;

	if (!rest)
	{
		rest = gnl_calloc(BUFFER_SIZE);
		if (!rest)
			return (NULL);
	}
	if (gnl_strlen(rest) != 0)
		str = gnl_strmv(rest);
	else
		str = gnl_calloc(1);
	if (fd <  0 && BUFFER_SIZE <= 0 && read(fd, str, 0) < 0)
		return (gnl_free(1, str));
	buffer = gnl_calloc(BUFFER_SIZE);
	if (buffer == NULL)
		return (gnl_free(1, buffer));
	line = get_line(fd, str, buffer, rest);
	if (rest[0] == '\0')
		free(rest);
	return (line);
}


int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	return (0);
}