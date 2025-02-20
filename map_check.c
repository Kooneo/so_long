/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:30:12 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/11 16:55:19 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	fill(char **map, t_point size, t_point current)
{
	if (current.x < 0 || current.y < 0 || current.y >= size.y
		|| current.x >= size.x || map[current.y][current.x] == '1'
		|| map[current.y][current.x] == 'V' || map[current.y][current.x] == 'T')
		return ;
	map[current.y][current.x] = 'V';
	fill(map, size, (t_point){current.x + 1, current.y});
	fill(map, size, (t_point){current.x - 1, current.y});
	fill(map, size, (t_point){current.x, current.y + 1});
	fill(map, size, (t_point){current.x, current.y - 1});
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
		return (0);
	size = (t_point){map->x, map->y};
	flood_fill(new_map, size, map->player_x / 64, map->player_y / 64);
	i = 0;
	while (new_map[i] != NULL)
	{
		if (ft_strchr(new_map[i], 'C') || ft_strchr(new_map[i], 'E'))
		{
			free_map(new_map);
			show_err("Invalid Map.");
			return (0);
		}
		i++;
	}
	free_map(new_map);
	return (1);
}
