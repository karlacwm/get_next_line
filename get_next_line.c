/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcheung <wcheung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:27:02 by wcheung           #+#    #+#             */
/*   Updated: 2025/11/12 17:41:00 by wcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// loop until end of line
// line to return - use malloc and put '\0'
// bytes read == 0 end of file, return and free malloc
// "line one\nline two"

#include "get_next_line.h"

static char	*leftover = NULL;

char	*extract_line(char *leftover)
{
	int		i;
	char	*line;

	i = 0;
	if (!leftover)
		return (NULL);
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (leftover[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, leftover, i);
	line[i] = '\0';
	return (line);
}
// find length of line till \n or \0 in leftover
// malloc space and + 1
// copy line from leftover into str
// return str

char	*update_leftover(char *str)
{

}
// find \n in leftover
// // free and return NULL when no \n
// find length after \name
// malloc space and +1
// copy from leftover into str
// free leftover
// return str

char	*get_next_line(int fd)
{
	char	*return_line;
	char	read_buffer[BUFFER_SIZE + 1];
	int		bytes_read; // how many bytes we have read

	// loop continues: 1) no new line found in leftover; 2) bytes_read is not 0
	bytes_read = 1;
	while (!ft_strchr(leftover, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		// if error when reading bytes
			return ();
		// add new things read to the leftover, join them, free old one, get new leftover
		leftover = ft_strjoin(leftover, read_buffer);
	}
	read_buffer[bytes_read] = '\0';

	// now leftover has a line (or end of file)?
	if (leftover == NULL || *leftover == '\0') // in case file or leftover is empty
	{
		return (NULL); // nothing to read
	}

	// finds the first \n in leftover, returns string with until and including \n
	return_line = (extract_line(leftover));

	// then remove what is returned already from leftover
	// finds the first '\n' and returns everything after it
	leftover = update_leftover(leftover);
	return (return_line);
}
