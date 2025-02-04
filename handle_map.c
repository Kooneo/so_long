/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:03:57 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/04 17:28:10 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"



static void	render_player(t_game *g, int x, int y)
{
	render_image(g, "textures/player/p_idle/down/idle_down_00.xpm", x, y);
	g->player->x_pos = x;
	g->player->y_pos = y;
	g->map->player_x = x;
	g->map->player_y = y;
}

static int	to_skipe(int x, int y)
{
	return (((x / 64 >= 2 && x / 64 <= 5) && (y / 64 == 4 || y / 64 == 5))
		|| ((x / 64 >= 16 && x / 64 <= 18) && y / 64 == 6)
		|| ((x / 64 >= 16 && x / 64 <= 17) && y / 64 == 7)
		|| (x / 64 == 20 && y / 64 == 5)
		|| (x / 64 == 12 && y / 64 == 4)
		|| (x / 64 == 4 && y / 64 == 6)
		|| ((x / 64 >= 3 && x / 64 <= 4) && y / 64 == 6));
}



static int	if_conddition_2(int x, int y)
{
	return (((x / 64 >= 23 && y / 64 == 6) && (x / 64 <= 27 && y / 64 == 6))
		|| ((x / 64 >= 23 && y / 64 == 7) && (x / 64 <= 27 && y / 64 == 7))
		|| ((x / 64 >= 23 && y / 64 == 5) && (x / 64 <= 27 && y / 64 == 5)));
}

static void	process_tile(t_game *g, char c, int x, int y, int i, int j)
{
	if (c == '1')
	{
		if (g->map->is_sp == 1
			&& ((x / 64 == 12 && y / 64 == 5) || (x / 64 == 18 && y / 64 == 4)))
			render_image(g, "textures/env/wall_001.xpm", x, y);
		else if (g->map->is_sp == 1 && to_skipe(x, y))
			render_image(g, "textures/bg_64n.xpm", x, y);
		else if (g->map->is_sp == 1 && if_conddition_2(x, y))
		{
			if ((x / 64 == 25 && y / 64 == 6)
				|| ((x / 64 == 27 || x / 64 == 23) && y / 64 == 7))
			{
				if ((x / 64 == 23 && y / 64 == 7))
				{
					render_el_at(g, 2, x + 64 - 15, y - 15);
					render_el_at(g, 1, x + 10, y - 20);
				}
				if ((x / 64 == 25 && y / 64 == 6))
					render_el_at(g, 2, x, y - 15);
				render_el_at(g, 10, x, y);
			}
			else
				render_el_at(g, 9, x, y);
		}
		else
			render_wall(g, i, j, x, y);
	}
	else
		render_others(g, c, x, y);
}

void	map_render(t_game *g)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = -1;
	y = 0;
	render_ground(g, "textures/bg_64n.xpm");
	g->map->is_sp = (ft_strcmp(g->map->filepath, "maps/map3.ber") == 0);
	while (++i < g->map->y && g->map->ptr[i])
	{
		x = 0;
		j = -1;
		while (g->map->ptr[i][++j])
		{
			if (!ft_isalnum(g->map->ptr[i][j]))
				return ;
			process_tile(g, g->map->ptr[i][j], x, y, i, j);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	render_map_design(g);
}
