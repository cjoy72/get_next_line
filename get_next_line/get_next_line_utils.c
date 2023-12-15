/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoy720 <cjoy720@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:31:07 by cbaroi            #+#    #+#             */
/*   Updated: 2023/12/15 15:01:26 by cjoy720          ###   ########.fr       */
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
//
//
//
//
//
/*
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
*/