/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoy720 <cjoy720@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:32:05 by cbaroi            #+#    #+#             */
/*   Updated: 2023/12/15 14:51:05 by cjoy720          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdarg.h>

char	*gnl_calloc(int size);
char	*gnl_free(int num, ...);
int		gnl_strlen(char *str);
char	*gnl_append(char *str, char *buffer);
char	*gnl_strmv(char *str);
char	*gnl_append(char *str, char *buffer);
char	*get_line(int fd,char *str, char *buffer, char *rest);
/*
char	*get_next_line(int fd);
char	*gnl_strjoin(char *str1, char *str2);
int		gnl_strlen(char *str);
char	*gnl_calloc(int size);
int		check_line(char *str);
*/

#endif
