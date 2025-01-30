/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:30:12 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 13:33:05 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// 111111111111111111111111111111
// 10000T000000000P00000000000001
// 1001111011101110101111C1111101
// 1001C0001C100C100011E0000T0001
// 1011110T1000101T00100000000001
// 1C1111001T10100000001001111101
// 10011000001T1010111011011111C1
// 100T0001100000101100C101111101
// 10000000C00000T0000111C0000001
// 111111111111111111111111111111

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
		while (map_data->ptr[i][j])
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
			j++;
		}
		i++;
	}
	if (!map['C'] || !map['E'] || !map['P'])
		return (0);
	return (1);
}

void	fill(char **map, t_point size, t_point current, char to_fill)
{
	if (current.x < 0 || current.y < 0 || current.y >= size.y
		|| current.x >= size.x || map[current.y][current.x] != to_fill)
		return ;
	map[current.y][current.x] = 'V';
	fill(map, size, (t_point){current.x + 1, current.y}, to_fill);
	fill(map, size, (t_point){current.x - 1, current.y}, to_fill);
	fill(map, size, (t_point){current.x, current.y + 1}, to_fill);
	fill(map, size, (t_point){current.x, current.y - 1}, to_fill);
}

char	**make_new_map(t_map *map)
{
	char	**new_map;
	int		i;

	if (!map)
		return (NULL);
	new_map = malloc((map->y + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map->ptr[i] != NULL)
	{
		new_map[i] = ft_strdup(map->ptr[i]);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

void	flood_fill(char **map, t_point size, int x, int y)
{
	fill(map, size, (t_point){x, y}, 'C');
}

int	map_check(t_map *map)
{
	t_point	size;
	char	**new_map;
	int		i;

	new_map = make_new_map(map);
	i = 0;
	while (new_map[i] != NULL)
	{
		ft_printf("%s", new_map[i]);
		i++;
	}
	size = (t_point){map->x, map->y};
	flood_fill(new_map, size, map->player_x, map->player_y);
	i = 0;
	while (new_map[i] != NULL)
	{
		if (ft_strchr(new_map[i], 'C'))
			show_err("Invalid Map.");
		
		i++;
	}
	return (0);
}
