/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miakubov <miakubov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:27:59 by miakubov          #+#    #+#             */
/*   Updated: 2025/04/23 21:25:59 by miakubov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

//create a function to put data to the leftovers and free leftovers
char *create_leftover(int fd, char *leftovers)
{
    //declare bytes of buffer (what read function is gonna return)
    ssize_t bytes_of_buff;

    //declare buffer
    char *buffer;

    //creating temporary variable for !!!!!!!!!!!!!!!!
    char *temp;

    //allocation of memory for buffer;
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));

    //if allocation fail we return null or if file descriptor is not valid return NULL
    if (!buffer || fd < 0)
    {
        free(buffer);
        return (NULL);
    }

        //FIXING LEAKS!!!!!!!!! THIS IS TO REMOVE STRDUP FROM GET NEXT LINE
        if (!leftovers)
        {
            //используем ft_strdup("") вместо malloc(1) — более читаемо
            leftovers = ft_strdup("");
            if (!leftovers)
            {
                free(leftovers);
                return (NULL);
            }
        }
    //initializing bytes of buffer to 1 to enter the cycle;
    bytes_of_buff = 1;

    //if we successfully allocated the memory we are going thru the while cycle until the end of file or until we encounter the \n on current buffer
    while (bytes_of_buff > 0 && !ft_strchr(leftovers, '\n'))
    {
        // read a piece of data into the buffer
        bytes_of_buff = read(fd, buffer, BUFFER_SIZE);

        //fixing memory leaks
        if (bytes_of_buff <= 0)
        {
            //freeing buffer anyway
            free(buffer);

            //если мы достигли конца файла, но в leftovers что-то есть — возвращаем это !!!!!!!!!!!!!!!!!!
            if (bytes_of_buff == 0 && leftovers && *leftovers != '\0')
                return (leftovers);

            //иначе чистим всё
            free(leftovers);
            return (NULL);
        }

        // add read data to leftovers
        buffer[bytes_of_buff] = '\0';

        //сохраняем старые leftovers во временную переменную
        temp = leftovers;

        //объединяем старые leftovers и новый кусок из buffer
        leftovers = ft_strjoin(temp, buffer);
        //!!!!!!!!!!!!!!!!!!!!!!!!!test
        // static int counter = 0;
        // printf("ft_strjoin call: %d\n", ++counter);
        //если выделение памяти не удалось — освобождаем всё и выходим
        if (!leftovers)
        {
            free(buffer);
            free(temp); //  фикс утечки памяти: освобождаем старые leftovers
            return NULL;
        }

        //если всё ок — освобождаем временную переменную
        free(temp);
    }

    //freeing the memory from buffer
    free(buffer);
    return (leftovers);
}


//create a function to cut the line from the leftovers and change leftovers to new one
//we should make leftover as pointer to a pointer because !!!!!!!!!!!!
char *result_line(char **leftovers)
{
    //declare the line we will return
    char *line;
    //declare the len of the string we will have to cut
    int len_of_line_to_return;

    // if there are \n in leftovers we are:
    if (ft_strchr(*leftovers, '\n'))
    {
        //checking the len we should cut (len_of_line_to_return)
        len_of_line_to_return = 0;
        while ((*leftovers)[len_of_line_to_return] && (*leftovers)[len_of_line_to_return] != '\n')
        {
            len_of_line_to_return++;
        }

        //increasing the len_of_line_to_return + 1 to add the \n (on the subject)
        len_of_line_to_return++;

        //cutting the string from leftovers from start to len we are checked before
        line = ft_substr(*leftovers, 0, len_of_line_to_return);
        //creating a new leftovers (all we have after \n)
        char *new_leftovers = ft_strdup(*leftovers + len_of_line_to_return);

        //fixing memory leaks with valgrind and GPT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (!new_leftovers)
        {
            free(*leftovers);
            *leftovers = NULL;
            return (NULL);
        }

        //freeing leftovers
        free(*leftovers);
        //making leftovers a new leftovers
        *leftovers = new_leftovers;
    }
    else // if there are no \n in leftovers we are:
    {
        //duplicating to line what's left and freeing the leftovers
        line = ft_strdup(*leftovers);
        free(*leftovers);
        *leftovers = NULL;
    }
    return (line);
}

char *get_next_line(int fd)
{
    //declare static variable for leftovers between calling a function (to not lose data between calls)
    static char *leftovers;

    //declare the line we will return
    char *line;

    //initializing leftovers to empty string to avoid an error on the call of functions ft_strchr and ft_strjoin
    //we can't do like this leftovers = "" because it cause segmentation fault ???????
    // if (!leftovers)
    //     leftovers = ft_strdup("");
    // if (!leftovers)
    //     return (NULL); // malloc fail

    //checking memory leaks with valgrind and GPT
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

    char *line = get_next_line(file_d);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(file_d);
    }
    close(file_d);
    return (0); 
    // int file_d = open("test.txt", O_RDONLY);

    // printf("%s\n", get_next_line(file_d));
    // printf("%s\n", get_next_line(file_d));
    // printf("%s\n", get_next_line(file_d));
    // printf("%s", get_next_line(file_d));
    // close(file_d);
    // return (0);
}*/
