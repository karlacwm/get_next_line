/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcheung <wcheung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:17:52 by wcheung           #+#    #+#             */
/*   Updated: 2025/11/17 17:16:10 by wcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("failed\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != 0)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
