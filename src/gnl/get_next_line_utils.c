/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skydogzz </var/spool/mail/skydogzz>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:16:13 by skydogzz          #+#    #+#             */
/*   Updated: 2025/05/21 03:25:17 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

/*size_t	ft_strlen(const char *s)*/
/*{*/
/*	size_t	i;*/
/**/
/*	i = 0;*/
/*	if (!s)*/
/*		return (0);*/
/*	while (s[i])*/
/*		i++;*/
/*	return (i);*/
/*}*/

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/*char	*ft_strdup(const char *s1)*/
/*{*/
/*	char	*copy;*/
/*	size_t	i;*/
/**/
/*	if (!s1)*/
/*		return (NULL);*/
/*	copy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));*/
/*	if (!copy)*/
/*		return (NULL);*/
/*	i = 0;*/
/*	while (s1[i])*/
/*	{*/
/*		copy[i] = s1[i];*/
/*		i++;*/
/*	}*/
/*	copy[i] = '\0';*/
/*	return (copy);*/
/*}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			joined[i] = s1[i];
			i++;
		}
	}
	j = 0;
	if (s2)
		while (s2[j])
			joined[i++] = s2[j++];
	joined[i] = '\0';
	return (joined);
}

char	*read_to_buffer(int fd, size_t *bytes_read)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read == (size_t) -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[*bytes_read] = '\0';
	return (buffer);
}
