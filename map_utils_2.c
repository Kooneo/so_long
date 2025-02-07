/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:35 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/07 14:16:39 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_is_rectangular(t_map *map)
{
	int	i;
	int	c_line_c;

	i = 0;
	if (!check_wall(map->ptr[i]))
		return (0);
	while (map->ptr[i])
	{
		c_line_c = ft_strlen(map->ptr[i]);
		if (c_line_c != map->x || !check_is_surrounded(map->ptr[i]))
			return (0);
		i++;
	}
	if (!check_wall(map->ptr[map->y - 1]))
		return (0);
	return (1);
}

int	check_psec_dup(t_map *map_data)
{
	int				map[255];
	unsigned char	c;
	int				i;
	int				j;

	ft_memset(map, 0, sizeof(map));
	i = 0;
	while (map_data->ptr[i])
	{
		j = 0;
		while (map_data->ptr[i][j++])
		{
			c = map_data->ptr[i][j];
			if (c == 'P' || c == 'E')
			{
				if (map[c] != 0)
					return (0);
				map[c] = 1;
			}
			if (c == 'C')
				map[c] = 1;
		}
		i++;
	}
	return (map['C'] && map['E'] && map['P']);
}

int	check_wall(char *wall)
{
	int	i;

	i = 0;
	while (wall && wall[i])
	{
		if (wall[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_is_surrounded(char *row)
{
	char	wall;
	size_t	r_count;

	wall = '1';
	r_count = ft_strlen(row) - 1;
	if (row[0] == wall && row[r_count] == wall)
		return (1);
	return (0);
}

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
		show_err("Invalid Map.");
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
