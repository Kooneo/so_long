/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:30:12 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/06 19:31:06 by zbakour          ###   ########.fr       */
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

void	fill(char **map, t_point size, t_point current)
{
	if (current.x < 0 || current.y < 0 || current.y >= size.y
		|| current.x >= size.x || !ft_strchr("0PCE", map[current.y][current.x]))
		return ;
		
	map[current.y][current.x] = 'V';

	fill(map, size, (t_point){current.x + 1, current.y});
	fill(map, size, (t_point){current.x - 1, current.y});
	fill(map, size, (t_point){current.x, current.y + 1});
	fill(map, size, (t_point){current.x, current.y - 1});
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
		if (!new_map[i])
		{
			while (i > 0)
				free(new_map[--i]);
			free(new_map);
			return (NULL);
		}
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}


void	flood_fill(char **map, t_point size, int x, int y)
{
	fill(map, size, (t_point){x, y});
}

int	map_check(t_map *map)
{
	t_point	size;
	char	**new_map;
	int		i;

	new_map = make_new_map(map);
	if (!new_map)
		show_err("Memory allocation failed.");
	i = 0;
	while (new_map[i] != NULL)
		ft_printf("%s\n", new_map[i++]);
	size = (t_point){map->x, map->y};
	flood_fill(new_map, size, map->player_x, map->player_y);
	i = 0;
	while (new_map[i] != NULL)
	{
		if (ft_strchr(new_map[i], 'C'))
		{
			show_err("Invalid Map.");
			return (1);
		}
		i++;
	}
	i = 0;
	while (new_map[i] != NULL)
		free(new_map[i++]);
	free(new_map);
	return (0);
}
