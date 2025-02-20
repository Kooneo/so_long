/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:03:57 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/13 18:02:49 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

static int	to_skipe(int x, int y)
{
	return (((x / 64 >= 2 && x / 64 <= 5) && (y / 64 == 4 || y / 64 == 5))
		|| ((x / 64 >= 16 && x / 64 <= 18) && y / 64 == 6) || ((x / 64 >= 16
				&& x / 64 <= 17) && y / 64 == 7) || (x / 64 == 20 && y
			/ 64 == 5) || (x / 64 == 12 && y / 64 == 4) || (x / 64 == 4 && y
			/ 64 == 6) || ((x / 64 >= 3 && x / 64 <= 4) && y / 64 == 6));
}

static int	if_conddition_2(int x, int y)
{
	return (((x / 64 >= 23 && y / 64 == 6) && (x / 64 <= 27 && y / 64 == 6))
		|| ((x / 64 >= 23 && y / 64 == 7) && (x / 64 <= 27 && y / 64 == 7))
		|| ((x / 64 >= 23 && y / 64 == 5) && (x / 64 <= 27 && y / 64 == 5)));
}

static void	render_elements(t_game *g, t_paramholder p)
{
	if ((p.x / 64 == 25 && p.y / 64 == 6) || ((p.x / 64 == 27 || p.x / 64 == 23)
			&& p.y / 64 == 7))
	{
		if ((p.x / 64 == 23 && p.y / 64 == 7))
		{
			render_el_at(g, 2, p.x + 64 - 15, p.x - 15);
			render_el_at(g, 1, p.x + 10, p.x - 20);
		}
		if ((p.x / 64 == 25 && p.y / 64 == 6))
			render_el_at(g, 2, p.x, p.y - 15);
		render_el_at(g, 10, p.x, p.y);
	}
	else
		render_el_at(g, 9, p.x, p.y);
}

static void	process_tile(t_game *g, char c, t_paramholder p)
{
	if (c == '1')
	{
		if (g->map->is_sp == 1 && ((p.x / 64 == 12 && p.y / 64 == 5) || (p.x
					/ 64 == 18 && p.y / 64 == 4)))
			render_image(g, "textures/env/wall_001.xpm", p.x, p.y);
		else if (g->map->is_sp == 1 && to_skipe(p.x, p.y))
			render_image(g, "textures/bg_64n.xpm", p.x, p.y);
		else if (g->map->is_sp == 1 && if_conddition_2(p.x, p.y))
			render_elements(g, p);
		else
			render_wall(g, p);
	}
	else
	{
		if (c == 'T')
			g->map->enemy_count++;
		render_others(g, c, p.x, p.y);
	}
}

void	map_render(t_game *g)
{
	int	i;
	int	j;
	int	x;
	int	y;

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
			process_tile(g, g->map->ptr[i][j], (t_paramholder){i, j, x, y});
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	find_enemies(g);
	render_map_design(g);
}
