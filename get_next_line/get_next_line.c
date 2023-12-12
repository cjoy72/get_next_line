/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaroi <cbaroi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 02:26:38 by cjoy720           #+#    #+#             */
/*   Updated: 2023/12/12 19:37:28 by cbaroi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			if (str[i + 1] == '\0')
				return (0);
			else
				return (i + 1);
		}
		else
			i++;
	}
	return (0);
}

char	*gnl_calloc(int size)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (str);
	i = 0;
	while (i < size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
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

char	*gnl_strjoin(char *str1, char *str2)
{
	int		size_str1;
	int		size_str2;
	char	*ret;
	int		i;

	size_str1 = gnl_strlen(str1);
	size_str2 = gnl_strlen(str2);
	ret = malloc(sizeof(char) * (size_str1 + size_str2 + 1));
	if (ret == NULL)
		return (ret);
	i = 0;
	while (i < size_str1)
	{
		ret[i] = str1[i];
		i++;
	}
	i = 0;
	while (i < size_str2)
	{
		ret[size_str1 + i] = str2[i];
		i++;
	}
	ret[size_str1 + size_str2] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	static int	pos = 0;
	char		*ret;
	int			out;
	char		*temp;

	ret = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (str == NULL)
	{
		str = gnl_calloc(BUFFER_SIZE + 1);
		if (str == NULL)
			return (NULL);
	}
	if (pos != 0)
	{
		if (str[pos] == '\n')
		{
			temp = malloc(sizeof(char) * 2);
			if (temp == NULL)
			{
				free(str);
				str = NULL;
				return (str);
			}
			temp[0] = '\n';
			temp[1] = '\0';
			if (str[pos + 1] != '\0')
				pos++;
			else
				pos = 0;
			return (temp);
		}
		ret = gnl_strjoin(&str[pos], ret);
		if (ret == NULL)
		{
			free(str);
			return (NULL);
		}
	}
	while (1)
	{
		out = read(fd, str, BUFFER_SIZE);
		if (out <= 0)
		{
			free(str);
			str = NULL;
			return (ret);
		}
		str[out] = '\0';
		pos = check_line(str);
		if (pos != 0)
		{
			temp = gnl_strjoin(str, NULL);
			if (temp == NULL)
			{
				free(str);
				return (temp);
			}
			temp[pos] = '\0';
			ret = gnl_strjoin(ret, temp);
			if (ret == NULL)
			{
				free(str);
				return (NULL);
			}
			return (ret);
		}
		else
		{
			ret = gnl_strjoin(ret, str);
			if (ret == NULL)
			{
				free(str);
				return (ret);
			}
		}
	}
}

/*
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
*/