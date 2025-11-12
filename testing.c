/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcheung <wcheung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:17:52 by wcheung           #+#    #+#             */
/*   Updated: 2025/11/11 17:18:09 by wcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	buffer[10];
	int		bytes_read;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("failed\n");
		return (1);
	}
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read == -1)
	{
		printf("failed\n");
		close(fd);
		return (1);
	}
	buffer[bytes_read] = '\0';
	printf("inside file:\n%s", buffer);
	close(fd);
	return (0);
}
