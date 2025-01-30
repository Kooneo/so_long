/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:35 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 15:04:15 by zbakour          ###   ########.fr       */
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
	int	map[255];
	int	i;
	int	j;

	ft_memset(map, 0, sizeof(map));
	i = 0;
	while (map_data->ptr[i])
	{
		j = 0;
		while (map_data->ptr[i][j])
		{
			if (map_data->ptr[i][j] == 'P' || map_data->ptr[i][j] == 'E')
			{
				if (map[(char)map_data->ptr[i][j]] != 0)
					return (0);
				map[(char)map_data->ptr[i][j]] = 1;
			}
			if ((char)map_data->ptr[i][j] == 'C')
				map[(char)map_data->ptr[i][j]] = 1;
			j++;
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
