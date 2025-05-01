/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miakubov <miakubov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:28:31 by miakubov          #+#    #+#             */
/*   Updated: 2025/05/01 17:26:17 by miakubov         ###   ########.fr       */
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
	int		i;
	int		j;
	size_t	len;
	char	*new;

	if (!s2[0])
		return (NULL);
	i = 0;
	j = 0;
	if (!s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (s1 && s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	free((char *)s1);
	return (new);
}

void	clear_leftovers(char *leftovers)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (leftovers[i] && leftovers[i] != '\n')
		i++;
	if (leftovers[i] == '\n')
		i++;
	while (leftovers[i])
		leftovers[j++] = leftovers[i++];
	leftovers[j] = '\0';
}

int	if_newline(char *leftovers)
{
	int	i;

	i = -1;
	while (leftovers[++i])
	{
		if (leftovers[i] == '\n')
			return (1);
	}
	return (0);
}

void	read_data(int fd, char **line, char *leftovers)
{
	ssize_t		bb;

	bb = 0;
	if (leftovers[0])
		*line = ft_strjoin(*line, leftovers);
	while (!if_newline(leftovers))
	{
		bb = read(fd, leftovers, BUFFER_SIZE);
		if (bb < 1)
			break ;
		leftovers[bb] = '\0';
		*line = ft_strjoin(*line, leftovers);
	}
}
