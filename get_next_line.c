/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:45:17 by fducrot           #+#    #+#             */
/*   Updated: 2025/10/16 10:45:37 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_update_static(char *r_read)
{
	size_t	i;
	char	*new_static;

	if (!r_read)
	{
		return (NULL);
	}
	i = 0;
	while (r_read[i] && r_read[i] != '\n')
	{
		i++;
	}
	new_static = ft_substr(r_read, i + 1, ft_strlen(r_read) - i);
	free(r_read);
	if (!new_static || !*new_static)
	{
		free(new_static);
		return (NULL);
	}
	return (new_static);
}

char	*ft_define_line(char *r_read)
{
	size_t	i;
	char	*line;

	i = 0;
	while (r_read[i] && r_read[i] != '\n')
	{
		i++;
	}
	if (r_read[i] == '\n')
	{
		i++;
	}
	line = ft_substr(r_read, 0, i);
	if (!line)
	{
		return (NULL);
	}
	if (!line[0])
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_read_doc(int fd, char *buffer, char *r_read)
{
	ssize_t	reader;
	char	*temp;

	reader = 1;
	while (reader > 0 && (!ft_strchr(r_read, '\n')))
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
		{
			free(r_read);
			return (NULL);
		}
		buffer[reader] = '\0';
		if (!r_read)
			r_read = ft_strdup("");
		temp = r_read;
		r_read = ft_strjoin(temp, buffer);
		if (!r_read)
			return (NULL);
		free(temp);
	}
	return (r_read);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*r_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(r_read);
		r_read = NULL;
		return (NULL);
	}
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	r_read = ft_read_doc(fd, buffer, r_read);
	free(buffer);
	if (!r_read || r_read[0] == '\0')
	{
		if (r_read)
			free(r_read);
		r_read = NULL;
		return (NULL);
	}
	line = ft_define_line(r_read);
	r_read = ft_update_static(r_read);
	return (line);
}
