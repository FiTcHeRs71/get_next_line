/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:15:16 by fducrot           #+#    #+#             */
/*   Updated: 2025/10/15 10:17:35 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_update_static(char *all_files)
{
	size_t	i;
	char	*new_static;

	i = 0;
	while (all_files[i] && all_files[i] != '\n')
	{
		i++;
	}
	if (!all_files[i])
	{
		free(all_files);
		return (NULL);
	}
	new_static = ft_substr(all_files, i + 1, ft_strlen(all_files) - i);
	free(all_files);
	if (!new_static)
	{
		return (NULL);
	}
	if (!new_static[0])
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
		temp = all_files;
		all_files = ft_strjoin(temp, buffer);
		free(temp);
		if (!all_files)
		{
			free (all_files);
			return (NULL);
		}
	}
	return (all_files);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*all_files;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
	{
		return (NULL);
	}
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (read(fd, 0, 0) < 0)
	{
		free(buffer);
		free(all_files);
		all_files = NULL;
		return (NULL);
	}
	all_files = ft_read_doc(fd, buffer, all_files);
	free(buffer);
	if (!all_files || all_files[0] == '\0')
	{
		return (NULL);
	}
	line = ft_define_line(all_files);
	all_files = ft_update_static(all_files);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Erreur: impossible d'ouvrir le fichier\n");
		return (1);
	}
	line = get_next_line(fd); // kc
	printf("%s", line);
	free(line);
	line = get_next_line(fd); // \n
	printf("%s", line);
	free(line);
	line = get_next_line(fd); // fitch
	printf("%s", line);
	free(line);
	line = get_next_line(fd); // \n
	printf("%s", line);
	free(line);
	line = get_next_line(fd); // philo
	printf("%s", line);
	free(line);
	line = get_next_line(fd); // \n
	printf("%s", line);
	free(line);
	line = get_next_line(fd); // rien
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}*/

/*

FT_STRCHR

FT_STRDUP

FT_STRLEN

FT_SUBSTR

FT_STRJOIN
*/
