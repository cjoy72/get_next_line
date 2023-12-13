/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoy720 <cjoy720@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:09:33 by cjoy720           #+#    #+#             */
/*   Updated: 2023/12/13 17:40:36 by cjoy720          ###   ########.fr       */
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

char	*ethnic_cleansing(char *to_free, char **to_null)
{
	free(to_free);
	*to_null = NULL;
	return (*to_null);
}

char	*get_single_line(char *str)
{
	char	*new_str;
	int		i;

	if (!str || *str == '\0')
		return (NULL);
	new_str = malloc(f_sl(str) * (str[f_sl(str) - 1] == '\n'));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[++i] != '\0' && str[i] != '\n')
		new_str[i - 1] = str[i];
	if (i <= f_sl(str) && str[i] != '\n')
		new_str[i-1] = str[i++];
	new_str[i - 1] = '\0';
	return (new_str);
}

int	f_sl(char *str)
{
	int	i;

	if(!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return(i);
}

char	*f_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		s1_len;
	int		s2_len;

	if (s1 && *s1 == 127)
		s1++;
	s1_len = f_s1(s1) + 1;
	s2_len = f_s1(s2);
	i = 0;
	newstr = malloc(s1_len + s2_len + 1);
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

char	*ft_calloc(int members, int size)
{
	char	*arr;
	int		n;

	if(members != 0 && size > ULONG_MAX / members)
		return (NULL);
	n = members * size;
	arr = malloc(n);
	while (arr && n-- > 0)
		arr[n] = '\0';
	return (arr);
}

char *get_next_line(int fd)
{
	char	*str;
	char	*ret;
	char	*buf;
	static char	*ptr;
	int			out;

	out = -69;
	while ((out > 0 && ptr) || out == -69)
	{
		str = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!str)
			break;
		out = read(fd, str, BUFFER_SIZE);
		buf = f_strjoin(ptr, str);
		ptr = buf;
		ret = get_single_line(ptr);
		if ((f_sl(ret) > 0 && (ret[f_sl(ret) - 1] == '\n')
				|| (out < BUFFER_SIZE && out >= 0)))
		{
			ptr += f_sl((ret) + (*buf == 127));
			return (ret);
		}
		free(ret);
	}
	return (ethnic_cleansing(buf, &ptr));
}

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	return (0);
}