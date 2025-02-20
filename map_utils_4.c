/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:28:26 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/20 18:07:43 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	render_wall_statment(t_game *game, t_paramholder p)
{
	return (p.j > 0 && ((game->map->ptr[p.i][p.j - 1] == '0'
			|| game->map->ptr[p.i][p.j - 1] == 'P'
		|| game->map->ptr[p.i][p.j - 1] == 'C'
		|| game->map->ptr[p.i][p.j - 1] == 'E'
		|| game->map->ptr[p.i][p.j - 1] == 'X'
		|| game->map->ptr[p.i][p.j - 1] == 'G'))
		&& game->map->ptr[p.i][p.j + 1] == '1');
}

void	render_wall(t_game *game, t_paramholder p)
{
	if (render_wall_statment(game, p))
		render_image(game, "textures/xf_end.xpm", p.x, p.y);
	else if (!game->map->ptr[p.i + 1])
		render_image(game, "textures/wall_b.xpm", p.x, p.y);
	else if (game->map->ptr[p.i][p.j + 1] == '\0' || p.j == 0)
		render_image(game, "textures/wall_m.xpm", p.x, p.y);
	else if (p.i == 0)
		render_image(game, "textures/wall_b.xpm", p.x, p.y);
	else if (p.j > 0 && game->map->ptr[p.i][p.j - 1] == '1'
		&& game->map->ptr[p.i][p.j + 1] == '1')
		render_image(game, "textures/x_m_m.xpm", p.x, p.y);
	else if (p.j > 0 && game->map->ptr[p.i][p.j - 1] == '1'
		&& (game->map->ptr[p.i][p.j + 1] == '0' || game->map->ptr[p.i][p.j
			+ 1] == 'P' || game->map->ptr[p.i][p.j + 1] == 'C'
			|| game->map->ptr[p.i][p.j + 1] == 'E' || game->map->ptr[p.i][p.j
			+ 1] == 'G' || game->map->ptr[p.i][p.j + 1] == 'X'))
		render_image(game, "textures/xe_end.xpm", p.x, p.y);
	else
		render_image(game, "textures/mid_wall.xpm", p.x, p.y);
}

void	render_player(t_game *g, int x, int y)
{
	render_image(g, "textures/player/p_idle/down/idle_down_00.xpm", x, y);
	g->player->x_pos = x;
	g->player->y_pos = y;
	g->map->player_x = x;
	g->map->player_y = y;
	map_check(g->map);
}

int	is_valid_el(char c)
{
	int				i;
	const char		elements[8] = {'0', '1', 'P', 'T', 'X', 'G', 'E', 'C'};

	i = 0;
	while (i < 8)
	{
		if (elements[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	characters_check(t_map *map)
{
	int				i;
	int				j;
	unsigned char	c;

	i = 0;
	while (map->ptr[i])
	{
		j = 0;
		while (j < map->x)
		{
			c = map->ptr[i][j];
			if (!is_valid_el(c))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
