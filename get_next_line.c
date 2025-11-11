/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcheung <wcheung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:27:02 by wcheung           #+#    #+#             */
/*   Updated: 2025/11/11 15:20:52 by wcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// loop until end of line
// line to return - use malloc and put '\0'
// bytes read == 0 end of file, return and free malloc
// "line one\nline two"

#include <get_next_line.h>

static char	*leftover = NULL;

char	*get_next_line(int fd)
{
	char	*return_line;
	char	*read_buffer;
	int		bytes_read; // how many bytes we have read

	// loop continues: 1) no new line found in leftover; 2) bytes_read is not 0
	while ()
	{
		bytes_read = read(fd, read_buffer, size_t BUFFER_SIZE);
		if (bytes_read < 0)
		// if error when reading bytes
			return ();
	}
	read_buffer[bytes_read] = '\0';
	// add new things read to the leftover, join them, free old one, get new leftover
	// // join leftover and read_buffer:
	// create new and bigger string, copy leftover, join read_buffer, return new string
	leftover = ft_strjoin(leftover, read_buffer);

	// now leftover has a line (or end of file?)
	if (leftover == NULL || *leftover == '\0') // in case the file was empty or leftover' is empty
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
