/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcheung <wcheung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:27:02 by wcheung           #+#    #+#             */
/*   Updated: 2025/11/15 13:59:22 by wcheung          ###   ########.fr       */
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
// find length of line till \n or \0 in remaining
// malloc space and + 1
// copy line from remaining into str
// return str

char	*update_remaining(char *remaining)
{
	int		i;
	int		len_to_copy;
	char	*updated;

	if (!remaining)
		return (NULL);
	i = 0;
	while (remaining[i] && remaining[i] != '\n')
		i++;
	if (!remaining[i])
	{
		free(remaining);
		return (NULL);
	}
	len_to_copy = ft_strlen(remaining) - i - 1;
	updated = (char *)malloc(sizeof(char) * (len_to_copy + 1));
	if (!updated)
	{
		free(remaining);
		return (NULL);
	}
	ft_memcpy(updated, remaining + i + 1, len_to_copy);
	updated[len_to_copy] = '\0';
	free(remaining);
	return (updated);
}
// find \n in remaining
// free and return NULL when no \n
// find length after \n
// malloc space and +1
// copy from remaining into str
// free remaining
// return str

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*return_line;
	char		*temp;
	char		*read_buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while ((!remaining || !ft_strchr(remaining, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		// if (bytes_read == 0)
		// 	break ;
		if (bytes_read < 0)
		{
			free(remaining);
			free(read_buffer);
			return (remaining = NULL, NULL);
		}
		read_buffer[bytes_read] = '\0';
		// printf("%s", read_buffer);
		temp = ft_strjoin(remaining, read_buffer);
		if (!temp)
		{
		free(read_buffer);
		free(remaining);
		return (remaining = NULL, NULL);
		}
		free(remaining);
		remaining = temp;
		// printf("%s", remaining);
	}
	if (!remaining || *remaining == '\0')
	{
		free(remaining);
		free(read_buffer);
		return (remaining = NULL, NULL);
	}
	return_line = (extract_line(remaining));
	// printf("%s", return_line);
	remaining = update_remaining(remaining);
	free(read_buffer);
	return (return_line);
}
// loop continues: 1) no new line found in remaining; 2) bytes_read is not 0
// add new things read to the remaining, join them, free old one,
// get new remaining
// now remaining has a line (or end of file)?
// in case file or remaining is empty
// finds the first \n in remaining, returns string with until and including \n
// then remove what is returned already from remaining
// finds the first '\n' and returns everything after it
