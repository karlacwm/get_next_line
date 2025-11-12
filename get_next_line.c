/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcheung <wcheung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:27:02 by wcheung           #+#    #+#             */
/*   Updated: 2025/11/12 17:55:40 by wcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// loop until end of line
// line to return - use malloc and put '\0'
// bytes read == 0 end of file, return and free malloc
// "line one\nline two"

#include "get_next_line.h"

char	*extract_line(char *remaining)
{
	int		i;
	char	*line;

	i = 0;
	if (!remaining)
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
// find length of line till \n or \0 in remaining
// malloc space and + 1
// copy line from remaining into str
// return str

char	*update_remaining(char *remaining)
{
	int		i;
	char	*temp;

	if (!remaining)
		return (NULL);
}
// find \n in remaining
// // free and return NULL when no \n
// find length after \name
// malloc space and +1
// copy from remaining into str
// free remaining
// return str

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*return_line;
	char		read_buffer[BUFFER_SIZE + 1];
	int			bytes_read; // how many bytes we have read

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remaining = NULL;
	bytes_read = 1;
	// loop continues: 1) no new line found in remaining; 2) bytes_read is not 0
	while (!ft_strchr(remaining, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		// if error when reading bytes
			return ();
		// add new things read to the remaining, join them, free old one, get new remaining
		remaining = ft_strjoin(remaining, read_buffer);
	}
	read_buffer[bytes_read] = '\0';

	// now remaining has a line (or end of file)?
	if (remaining == NULL || *remaining == '\0') // in case file or remaining is empty
	{
		return (NULL); // nothing to read
	}

	// finds the first \n in remaining, returns string with until and including \n
	return_line = (extract_line(remaining));

	// then remove what is returned already from remaining
	// finds the first '\n' and returns everything after it
	remaining = update_remaining(remaining);
	return (return_line);
}
