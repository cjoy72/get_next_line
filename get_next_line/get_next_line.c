/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoy720 <cjoy720@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:02:41 by cbaroi            #+#    #+#             */
/*   Updated: 2023/12/11 00:57:26 by cjoy720          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

// Function to allocate and initialize memory
char *gnl_calloc(int size) {
    char *arr;

    if (size <= 0 || size > ULONG_MAX / sizeof(char))
        return NULL;

    arr = (char *)malloc(sizeof(char) * size);
    if (arr == NULL)
        return NULL;

    for (int i = 0; i < size; i++)
        arr[i] = '\0';

    return arr;
}

// Function to find the newline character in a string
int check_next_line(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n')
            return (i + 1); // Return position after '\n'
        i++;
    }
    return 0;
}

// Function to get the length of a string
int gnl_strlen(char *str) {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

// Function to concatenate two strings
char *gnl_strjoin(char *ret, char *str) {
    int ret_len = ret ? gnl_strlen(ret) : 0;  // Handle NULL pointer
    int str_len = str ? gnl_strlen(str) : 0;  // Handle NULL pointer
    char *retrn = gnl_calloc(ret_len + str_len + 1);

    if (retrn == NULL)
        return NULL;

    // Copy contents only if the pointers are not NULL
    if (ret) {
        for (int i = 0; i < ret_len; i++)
            retrn[i] = ret[i];
    }
    if (str) {
        for (int i = 0; i < str_len; i++)
            retrn[ret_len + i] = str[i];
    }

    free(ret); // Free the old 'ret' pointer
    return retrn;
}

// Main function to read a line from a file
char *get_next_line(int fd) {
    static char *str = NULL;
    char *ret = NULL;
    int out, ptr;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    if (str == NULL)
        str = gnl_calloc(BUFFER_SIZE + 1);

    if (str == NULL)
        return NULL;

    while (1) {
        out = read(fd, str, BUFFER_SIZE);
        if (out <= 0) {
            free(str);
            str = NULL;
            return ret; // Return what has been read so far
        }
        str[out] = '\0';

        ptr = check_next_line(str);
        if (ptr != 0) {
            char *temp = gnl_calloc(ptr + 1);
            strncpy(temp, str, ptr); // Copy only the part up to '\n'
            ret = gnl_strjoin(ret, temp);
            free(temp); // Free the temporary string
            int remaining = gnl_strlen(str) - ptr;
            memmove(str, str + ptr, remaining); // Shift remaining part to the beginning
            memset(str + remaining, '\0', BUFFER_SIZE - remaining); // Clear the rest of the buffer
            return ret;
        } else {
            ret = gnl_strjoin(ret, str);
            if (ret == NULL) {
                free(str);
                return NULL;
            }
        }

        if (out < BUFFER_SIZE) {
            // If the buffer is not full, it means we've reached the end of the file
            free(str);
            str = NULL;
            return ret; // Return the last line if end of file is reached
        }
    }
}


int	main(void)
{
	int	fd;
	char *line;

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
	return (0);
}