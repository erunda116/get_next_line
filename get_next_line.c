/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miakubov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:27:59 by miakubov          #+#    #+#             */
/*   Updated: 2025/04/19 10:28:02 by miakubov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char    *get_next_line(int fd)
{
    //ssize_t read(int fildes, void *buf, size_t nbyte);
    static int file_d;
    static char *buffer;
    int i = 0;
    file_d = fd;
    buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer || fd == -1)
        return (NULL);
    while (buffer[i] != '\n')
    {
        read(file_d, buffer, 10);
        printf("000000000000000000000000");        
        i++;
    }
    return (buffer);
}
#include <fcntl.h> // for open function
int main()
{
    int file_d = open("test.txt", O_RDONLY | O_CREAT);
    char *one_line = get_next_line(file_d);
    printf("%s\n", one_line);
    close(file_d);
    return (0);
}
