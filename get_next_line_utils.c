/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miakubov <miakubov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:28:31 by miakubov          #+#    #+#             */
/*   Updated: 2025/04/26 13:20:33 by miakubov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*src1;
	unsigned char		*dest1;
	size_t				i;

	if (n == 0 || dest == src)
		return (dest);
	dest1 = (unsigned char *)dest;
	src1 = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	// static int counter = 0;
    // printf("memcpy call: %d\n", ++counter);
	return (dest);
}
char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	all_size;
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	j = 0;
	all_size = ft_strlen(s1) + ft_strlen(s2);
	result = malloc((all_size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		result[i++] = s2[j++];
	}
	result[i] = '\0';
	// static int counter = 0;
    // printf("ft_strjoin call: %d\n", ++counter);
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
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


