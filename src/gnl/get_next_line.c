/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:12:40 by tstephan          #+#    #+#             */
/*   Updated: 2025/05/21 07:40:47 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

static char	*read_and_store(int fd, char *store)
{
	char	*buffer;
	char	*temp;
	size_t	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(store, '\n') && bytes_read != 0)
	{
		buffer = read_to_buffer(fd, &bytes_read);
		if (!buffer)
		{
			return (NULL);
		}
		if (!store)
			store = ft_strdup("");
		temp = ft_strjoin(store, buffer);
		free(store);
		free(buffer);
		if (!temp)
			return (NULL);
		store = temp;
	}
	return (store);
}

static size_t	calculate_line_length(char *store)
{
	size_t	i;

	if (!store)
		return (0);
	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	return (i);
}

static char	*extract_line(char *store)
{
	char	*line;
	size_t	line_length;
	size_t	i;

	if (!store || !*store)
		return (NULL);
	line_length = calculate_line_length(store);
	if (line_length == 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (line_length + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_length && store[i])
	{
		line[i] = store[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*save_remaining(char *store)
{
	char	*remaining;
	size_t	i;
	size_t	j;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (!store[i])
	{
		free(store);
		return (NULL);
	}
	remaining = (char *)malloc(sizeof(char) * (ft_strlen(store) - i + 1));
	if (!remaining)
	{
		free(store);
		return (NULL);
	}
	i++;
	j = 0;
	while (store[i])
		remaining[j++] = store[i++];
	remaining[j] = '\0';
	free(store);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char		*line;

	if (fd < 0 && store)
		free(store);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = read_and_store(fd, store);
	if (!store)
		return (NULL);
	line = extract_line(store);
	store = save_remaining(store);
	return (line);
}
