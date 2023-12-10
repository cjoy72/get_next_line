/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoy720 <cjoy720@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:02:41 by cbaroi            #+#    #+#             */
/*   Updated: 2023/12/10 16:14:08 by cjoy720          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

BUFFER_SIZE = 10;

typedef struct s_node
{
	char			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					node;

node	**create_node()
{
	node	*new_node;
	
	if(new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (&new_node);
}

void	add_node(node **start, char *static_line)
{
	node	*ptr;
	
	ptr = *start;
	while ((ptr)->next != NULL)
		ptr = (ptr)->next;
	ptr->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (ptr->content == NULL)
		return (NULL);
	while()
		
}

char	*get_next_line(int fd)
{
	static char	*static_line;
	static int	prev_exist = 0;
	static node	**start;
	int			bytes_read;
	int			found_new_line;

	start = create_node();
	if (start == NULL)
		return (NULL);
	found_new_line = 0;
	while (!found_new_line || read(fd, static_line, 0) = 0)
	{
		bytes_read = read(fd, static_line, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		add_node(*start, static_line);
		
	}
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