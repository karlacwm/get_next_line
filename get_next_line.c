/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcheung <wcheung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:27:02 by wcheung           #+#    #+#             */
/*   Updated: 2025/11/17 17:47:09 by wcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// loop until end of line
// line to return - use malloc and put '\0'
// bytes read == 0 end of file, return and free malloc
// "line one\nline two"

#include "get_next_line.h"

static char	*extract_line(char *remaining)
{
	int		i;
	char	*line;

	i = 0;
	if (!remaining || !remaining[i])
		return (NULL);
	while (remaining[i] && remaining[i] != '\n')
		i++;
	if (remaining[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, remaining, i);
	line[i] = '\0';
	return (line);
}

static char	*update_remaining(char *remaining)
{
	int		i;
	char	*updated;

	if (!remaining)
		return (NULL);
	i = 0;
	while (remaining[i] && remaining[i] != '\n')
		i++;
	if (!remaining[i] || !remaining[i + 1])
	{
		free(remaining);
		return (NULL);
	}
	updated = ft_strdup(&remaining[i + 1]);
	free(remaining);
	return (updated);
}

char	*get_next_line(int fd)
{
	static char	*remaining = NULL;
	char		*return_line;
	char		*read_buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
	{
		// free(remaining);
		return (NULL);
	}
	bytes_read = 1;
	while ((!ft_strchr(remaining, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(read_buffer);
			free(remaining);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		remaining = ft_strjoin(remaining, read_buffer);
		if (!remaining)
		{
			free(read_buffer);
			return (NULL);
		}
	}
	free(read_buffer);
	if (!remaining)
		return (NULL);
	if (remaining[0] == '\0')
	{
		free(remaining);
		remaining = NULL;
		return (NULL);
	}
	return_line = (extract_line(remaining));
	if (!return_line)
	{
		free(remaining);
		remaining = NULL;
		return (NULL);
	}
	remaining = update_remaining(remaining);
	return (return_line);
}
// find length of line till \n or \0 in remaining
// malloc space and + 1
// copy line from remaining into str
// return str

// find \n in remaining
// free and return NULL when no \n
// find length after \n
// malloc space and +1
// copy from remaining into str
// free remaining
// return str

// loop continues: 1) no new line found in remaining; 2) bytes_read is not 0
// add new things read to the remaining, join them, free old one,
// get new remaining
// now remaining has a line (or end of file)?
// in case file or remaining is empty
// finds the first \n in remaining, returns string with until and including \n
// then remove what is returned already from remaining
// finds the first '\n' and returns everything after it
