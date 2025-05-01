/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miakubov <miakubov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:27:59 by miakubov          #+#    #+#             */
/*   Updated: 2025/05/01 17:21:58 by miakubov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	int			i;
	static char	leftovers[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	line = NULL;
	read_data(fd, &line, leftovers);
	if (line)
	{
		while (line[i] && line[i] != '\n')
			i++;
		if (line[i] == '\n')
			i++;
		line[i] = '\0';
	}
	clear_leftovers(leftovers);
	return (line);
}
/*
#include <fcntl.h>

int main()
{
    int file_d = open("test.txt", O_RDONLY);
    char *line;

    line = get_next_line(file_d);
	printf("%s", line);
	free(line);
    // while (line)
    // {
        // printf("%s", line);
        // free(line);
        // line = get_next_line(file_d);
    // }
    close(file_d);
    return (0);

	//int file_d = open("test.txt", O_RDONLY);
 
    //printf("%s\n", get_next_line(file_d));
    //printf("%s\n", get_next_line(file_d));
    //printf("%s\n", get_next_line(file_d));
    //printf("%s", get_next_line(file_d));
    //close(file_d);
    //return (0);
} */