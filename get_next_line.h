/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoy720 <cjoy720@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:51:45 by cjoy720           #+#    #+#             */
/*   Updated: 2023/12/13 22:19:43 by cjoy720          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
//  Just to test with main function
//  #include <fcntl.h>
//  #include <stdio.h>

int		sl(char *c);
char	*gnl_alloc(size_t num, size_t size);
char	*gnl_clean(char *to_free, char **to_null);
char	*get_next_line(int fd);
char	*gnl_line(char *str);
char	*f_strjoin(char *s1, char *s2);
#endif