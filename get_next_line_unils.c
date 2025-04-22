/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_unils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miakubov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:28:31 by miakubov          #+#    #+#             */
/*   Updated: 2025/04/19 10:28:34 by miakubov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (!result || !s1 || !s2)
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
