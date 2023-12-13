/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoy720 <cjoy720@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:09:33 by cjoy720           #+#    #+#             */
/*   Updated: 2023/12/13 19:07:57 by cjoy720          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

int		f_sl(char *c);
char	*ft_calloc(size_t nmemb, size_t size);
char	*free_and_null(char *to_free, char **to_null);
char	*get_next_line(int fd);
char	*get_single_line(char *str);

char	*free_and_null(char *to_free, char **to_null)
{
	free(to_free);
	*to_null = NULL;
	return (NULL);
}

char	*get_single_line(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	if (!str || *str == '\0')
		return (NULL);
	new_str = malloc(f_sl(str) + (str[f_sl(str) - 1] == '\n'));
	if (!new_str)
		return (NULL);
	while (str[++i] != '\0' && str[i] != '\n')
		new_str[i - 1] = str[i];
	if (i <= f_sl(str) && str[i] == '\n')
	{
		new_str[i - 1] = str[i];
		i++;
	}
	new_str[i - 1] = '\0';
	return (new_str);
}

char	*f_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		s1_len;
	int		s2_len;

	if (s1 && *s1 == 127)
		s1++;
	s1_len = f_sl(s1) + 1;
	s2_len = f_sl(s2);
	i = 0;
	newstr = malloc((s1_len + s2_len + 1));
	if (newstr)
		newstr[0] = 127;
	while (newstr && ++i < s1_len && s1)
		newstr[i] = s1[i - 1];
	i = -1;
	while (newstr && ++i < s2_len && s2)
		newstr[s1_len + i] = s2[i];
	if (newstr)
		newstr[s1_len + i] = '\0';
	free(s2);
	while (s1 && *s1 != 127)
		s1--;
	free(s1);
	return (newstr);
}

int	f_sl(char *c)
{
	int	n;

	if (!c)
		return (0);
	n = 0;
	while (c[n])
		n++;
	return (n);
}

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*arr;
	int		n;

	if (nmemb != 0 && size > ULONG_MAX / nmemb)
		return (NULL);
	n = nmemb * size;
	arr = malloc(n);
	while (arr && n-- > 0)
		arr[n] = '\0';
	return (arr);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*ret;
	char		*buf;
	static char	*ptr;
	int			out;

	out = -42;
	while ((out > 0 && ptr) || out == -42)
	{
		str = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!str)
			break ;
		out = read(fd, str, BUFFER_SIZE);
		buf = f_strjoin(ptr, str);
		ptr = buf;
		ret = get_single_line(ptr);
		if (f_sl(ret) > 0
			&& (ret[f_sl(ret) - 1] == '\n' || (out < BUFFER_SIZE && out >= 0)))
		{
			ptr += f_sl(ret) + (*buf == 127);
			return (ret);
		}
		free(ret);
	}
	return (free_and_null(buf, &ptr));
}

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