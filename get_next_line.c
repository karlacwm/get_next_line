/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcheung <wcheung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:27:02 by wcheung           #+#    #+#             */
/*   Updated: 2025/11/10 12:26:42 by wcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// loop until end of line
// line to return - use malloc and put '\0'
// bytes read == 0 end of file, return and free malloc

char *get_next_line(int fd)
{
	char	read_buffer;
	int	bytes_read;

	bytes_read = read(fd, read_buffer, size_t );
}
