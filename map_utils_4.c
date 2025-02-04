/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:28:26 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/04 17:28:38 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	map_row_c(char *filepath)
{
	size_t	row_c;
	char	*read_line;
	char	*trimmed_line;
	int		fd;

	fd = open(filepath, O_RDWR);
	if (fd < 0)
		return (0);
	read_line = get_next_line(fd);
	if (!read_line)
	{
		show_err("Invalid Map.");
		exit(-1);
	}
	row_c = 0;
	while (read_line)
	{
		trimmed_line = ft_strtrim(read_line, "\n");
		if (trimmed_line)
		{
			row_c++;
			free(trimmed_line);
		}
		free(read_line);
		read_line = get_next_line(fd);
	}
	close(fd);
	return (row_c);
}
