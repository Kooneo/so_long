/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:25:53 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/13 18:18:24 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_el_at(t_game *game, int el, int x, int y)
{
	if (el == 1)
		render_image(game, "textures/env/el_1.xpm", x, y + 64 - 15);
	else if (el == 2)
		render_image(game, "textures/env/el_2.xpm", x, y + 64 - 15);
	else if (el == 3)
		render_image(game, "textures/env/el_3.xpm", x + 64 - 20, y + 64 - 15);
	else if (el == 9)
		render_image(game, "textures/env/el_9.xpm", x + 20, y);
	else if (el == 10)
		render_image(game, "textures/env/el_10.xpm", x + 25, y - 5);
	else if (el == 13)
		render_image(game, "textures/env/plant/el_1.xpm", x + 20, y - 80);
	else if (el == 14)
		render_image(game, "textures/env/plant/el_2.xpm", x + 20, y - 80);
	else if (el == 15)
		render_image(game, "textures/env/plant/el_3.xpm", x + 20, y - 80);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**load_map(t_map *map_data)
{
	char	*read_line;
	size_t	row_c;
	char	**map;
	int		fd;

	map = malloc(sizeof(char *) * map_row_c(map_data->filepath) * 100);
	if (!map)
		return (NULL);
	fd = open(map_data->filepath, O_RDWR);
	read_line = get_next_line(fd);
	if (!read_line)
		return (NULL);
	row_c = 0;
	while (read_line)
	{
		map[row_c++] = ft_strtrim(read_line, "\n");
		free(read_line);
		read_line = get_next_line(fd);
	}
	map_data->x = ft_strlen(map[0]);
	map_data->y = row_c;
	map_data->size = map_data->y * map_data->x;
	map[row_c] = NULL;
	close(fd);
	return (map);
}

void	render_others(t_game *g, int c, int x, int y)
{
	if (c == 'T' || c == 'X' || c == 'G')
	{
		if (c == 'T')
		{
			render_image(g, "textures/env/enemy.xpm", x - 3, y - 3);
		}
		else if (c == 'X')
			render_image(g, "textures/env/blue_hand.xpm", x - 3, y - 3);
		else
			render_image(g, "textures/env/green_hand.xpm", x - 3, y - 3);
	}
	else if (c == 'C')
	{
		render_image(g, "textures/coins/coin.xpm", x + 10, y);
		g->map->coins_count++;
	}
	else if (c == 'P')
		render_player(g, x, y);
	else if (c == 'E')
	{
		g->map->exit_x = x;
		g->map->exit_y = y;
	}
}
