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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	all_size;
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	j = 0;
	all_size = ft_strlen(s1) + ft_strlen(s2);
	result = malloc((all_size + 1) * sizeof(char));
	if (!result || s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
    if (!s)
        return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (start > ft_strlen(s))
	{
		substring = malloc(1);
		if (!substring)
			return (NULL);
		substring[0] = '\0';
		return (substring);
	}
	i = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substring = malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	while (len > 0 && s[start] != '\0')
	{
		substring[i++] = s[start++];
		len--;
	}
	substring[i] = '\0';
	return (substring);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	size_t	i;
	char	*copy;

	size = 0;
	i = 0;
	while (s[size] != '\0')
		size++;
	copy = malloc((size + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (i < size)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
char    *get_next_line(int fd)
{
    //declare buffer
    static char *buffer;

    //declare bytes of buffer
    ssize_t bytes_of_buff;

    //declare static variable for leftovers between calling a function (to not lose data between calls)
    static char *leftovers;

    //declare the line we will return
    char *line;

    //declare start index to cut the line from leftovers
    //int start_index; dont need it ????

    //declare end index to cut the line from leftovers
    //int end_index; dont need it ?????

    //declare the len of the string we will have to cut
    int len_of_line_to_return;

    //initializing bytes of buffer to 1 to enter the cycle;
    bytes_of_buff = 1;

    //initializing leftovers to empty string to avoid an error on the call of functions ft_strchr and ft_strjoin
    //we can't do like this leftovers = "" because it cause segmentation fault ??????? 
    if (!leftovers)
	    leftovers = ft_strdup("");

    //allocation of memory for buffer;
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    
    //if allocation fail we return null
    if (!buffer)
        return (NULL);
    //if file descriptor is not valid return NULL
    if (fd == - 1)
        return (NULL);

    //if we sucessfully allocated the memory we are going thru the while cycle until the end of file or until we encounter the \n on current buffer
    while (bytes_of_buff > 0 && !ft_strchr(leftovers, '\n'))
    {
        //reading data piece by piece
        bytes_of_buff = read(fd, buffer, BUFFER_SIZE);
        
        //storing data from buffer to leftovers by joining the string
        leftovers = ft_strjoin(leftovers, buffer);
        //if something went wrong with strjoin we are freeing the memory for leftovers and returning NULL
        if (!leftovers)
        {
            free(leftovers);
            return (NULL);
        }
    }
    //freeing the memory from buffer
    free(buffer);

    //now we have to cut the line from the leftovers and change leftovers to new one
    // if there are \n in leftovers we are: 
    if (ft_strchr(leftovers, '\n'))
    {
        //checking the len we should cut (len_of_line_to_return)
        len_of_line_to_return = 0;
        while (leftovers[len_of_line_to_return] && leftovers[len_of_line_to_return] != '\n')
        {
            len_of_line_to_return++;
        }
        //increasing the len_of_line_to_return + 1 to add the \n (on the subject)
        len_of_line_to_return++;

        //cutting the string from leftovers from start to len we are checked before
        line = ft_substr(leftovers, 0, len_of_line_to_return);
        //creating a new leftovers (all we have after \n)
        char *new_leftovers = ft_strdup(leftovers + len_of_line_to_return);
        //freeing leftovers
        free(leftovers);
        //making leftovers a new leftovers
        leftovers = new_leftovers;
    } 
    else // if there are no \n in leftovers we are:
    {
        //duplicating to line what's left and freeing the leftovers
        line = ft_strdup(leftovers);
        free(leftovers);
        leftovers = NULL;
    }
    return (line);
}
#include <fcntl.h> // for open function
int main()
{
    int file_d = open("test.txt", O_RDONLY | O_CREAT);
    printf("%s\n", get_next_line(file_d));
    printf("%s\n", get_next_line(file_d));
    printf("%s\n", get_next_line(file_d));
    printf("%s\n", get_next_line(file_d));

    close(file_d);
    return (0);
}
