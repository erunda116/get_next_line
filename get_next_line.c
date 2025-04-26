/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miakubov <miakubov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:27:59 by miakubov          #+#    #+#             */
/*   Updated: 2025/04/26 14:50:50 by miakubov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *while_for_lo(char *leftovers, int fd, char *buffer, ssize_t *bytes_of_buff)
{
    char *temp;

    *bytes_of_buff = read(fd, buffer, BUFFER_SIZE);
    if (*bytes_of_buff == -1)
    {
        free(leftovers);
        return (NULL);
    }
        if (*bytes_of_buff <= 0)
        {
            if (*bytes_of_buff == 0 && leftovers && *leftovers != '\0')
                return (leftovers);
            free(leftovers);
            return (NULL);
        }
    buffer[*bytes_of_buff] = '\0';
    temp = leftovers;
    leftovers = ft_strjoin(temp, buffer);
    free(temp);
    return (leftovers);
}

char *create_leftover(int fd, char *leftovers)
{
    ssize_t bytes_of_buff;
    char *buffer;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    if (!leftovers)
    {
        leftovers = ft_strdup("");
        if (!leftovers)
        {
            free(buffer);
            return (NULL);
        }
    }
    bytes_of_buff = 1;
    while (bytes_of_buff > 0 && !ft_strchr(leftovers, '\n'))
        leftovers = while_for_lo(leftovers, fd, buffer, &bytes_of_buff);
    free(buffer);
    return (leftovers);
}

// char if_strchr_fine_n(char *leftovers, int len_of_line_to_return, char *line)
// {

// }

char *result_line(char **leftovers)
{
    char *line;
    int len_of_line_to_return;
    char *new_leftovers;

    if (ft_strchr(*leftovers, '\n'))
    {
        len_of_line_to_return = 0;
        while ((*leftovers)[len_of_line_to_return] && (*leftovers)[len_of_line_to_return] != '\n')
        {
            len_of_line_to_return++;
        }
        len_of_line_to_return++;
        line = ft_substr(*leftovers, 0, len_of_line_to_return);
        new_leftovers = ft_strdup(*leftovers + len_of_line_to_return);
        if (!new_leftovers)
        {
            free(*leftovers);
            *leftovers = NULL;
            return (NULL);
        }
        free(*leftovers);
        *leftovers = new_leftovers;
    }
    else
    {
        line = ft_strdup(*leftovers);
        free(*leftovers);
        *leftovers = NULL;
    }
    return (line);
}

char *get_next_line(int fd)
{
    static char *leftovers;
    char *line;

    leftovers = create_leftover(fd, leftovers);
    if (!leftovers)
    {
        free(leftovers);
        return (NULL);
    }   
    line = result_line(&leftovers);
    return (line);
}

/*#include <fcntl.h> // for open function
int main()
{
      int file_d = open("test.txt", O_RDONLY);

    //char *line = get_next_line(file_d);
    

// char *get_next_line(int fd)
// {
//     //declare static variable for leftovers between calling a function (to not lose data between calls)
//     static char *leftovers;

//     //declare the line we will return
//     char    *line;
//     //check if fd is correct and buffer size is correct
//     if (fd == - 1 || BUFFER_SIZE <= 0)
//         return (NULL);
//     leftovers = get_and_store(fd);
//     return (line);
// }
 
    printf("%s\n", get_next_line(file_d));
    printf("%s\n", get_next_line(file_d));
    printf("%s\n", get_next_line(file_d));
    printf("%s", get_next_line(file_d));
    close(file_d);
    return (0);
}*/
