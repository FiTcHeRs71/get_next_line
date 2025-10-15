/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    get_next_line_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:28:58 by fducrot           #+#    #+#             */
/*   Updated: 2025/10/15 17:29:17 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_update_static(char *all_files)
{
	size_t	i;
	char	*new_static;

	if (!all_files)
	{
		return (NULL);
	}
	i = 0;
	while (all_files[i] && all_files[i] != '\n')
	{
		i++;
	}
	new_static = ft_substr(all_files, i + 1, ft_strlen(all_files) - i);
	free(all_files);
	if (!new_static || !*new_static)
	{
		free(new_static);
		return (NULL);
	}
	return (new_static);
}

char	*ft_define_line(char *all_files)
{
	size_t	i;
	char	*line;

	i = 0;
	while (all_files[i] && all_files[i] != '\n')
	{
		i++;
	}
	if (all_files[i] == '\n')
	{
		i++;
	}
	line = ft_substr(all_files, 0, i);
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

char	*ft_read_doc(int fd, char *buffer, char *all_files)
{
	ssize_t	reader;
	char	*temp;

	reader = 1;
	while (reader > 0 && (!ft_strchr(all_files, '\n')))
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
		{
			free(all_files);
			return (NULL);
		}
		buffer[reader] = '\0';
		if (!all_files)
			all_files = ft_strdup("");
		temp = all_files;
		all_files = ft_strjoin(temp, buffer);
		if (!all_files)
			return (NULL);
		free(temp);
		if (!all_files)
			return (NULL);
	}
	return (all_files);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*r_read[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
	{
		free(r_read[MAX_FD]);
		r_read[MAX_FD] = NULL;
		return (NULL);
	}
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	r_read[MAX_FD] = ft_read_doc(fd, buffer, r_read[MAX_FD]);
	free(buffer);
	if (!r_read[MAX_FD] || r_read[MAX_FD][0] == '\0')
	{
		if (r_read[MAX_FD])
			free(r_read[MAX_FD]);
		r_read[MAX_FD] = NULL;
		return (NULL);
	}
	line = ft_define_line(r_read[MAX_FD]);
	r_read[MAX_FD] = ft_update_static(r_read[MAX_FD]);
	return (line);
}
