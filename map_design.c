/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_design.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:31:18 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/31 20:34:03 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_special_props(t_game *g, int tx, int ty, int xy[2])
{
	const int	x = xy[0];
	const int	y = xy[1];

	if ((tx == 25 && ty == 7) || (tx == 23 && ty == 6))
	{
		if (tx == 23 && ty == 6)
			render_el_at(g, 14, x, y + 25);
		else
			render_el_at(g, 13, x, y);
	}
	if (tx == 18 && ty == 3)
		render_el_at(g, 15, x - 12, y + 32);
}

static void	render_tile_special(t_game *g, int tx, int ty, int xy[2])
{
	const int	x = xy[0];
	const int	y = xy[1];

	if (tx == 3 && ty == 4)
		render_image(g, "textures/env/big_obj_1.xpm", x + 25, y);
	else if (tx == 17 && ty == 6)
		render_image(g, "textures/env/props/el_2.xpm", x, y);
	else if (tx == 16 && ty == 6)
		render_section_16_6(g, x, y);
	else if (tx == 18 && ty == 6)
		render_section_18_6(g, x, y);
	else if (tx == 17 && ty == 7)
		render_image(g, "textures/env/props/el_12.xpm", x - 15, y + 25);
	else if (tx == 20 && ty == 5)
	{
		render_image(g, "textures/env/props/el_15.xpm", x, y);
		render_image(g, "textures/env/props/el_9.xpm", x + 38, y + 23);
	}
}

static void	render_additional_decor(t_game *g, int tx, int ty, int xy[2])
{
	const int	x = xy[0];
	const int	y = xy[1];

	if (tx == 12 && ty == 4)
	{
		render_image(g, "textures/env/el_5.xpm", x, y);
		render_image(g, "textures/env/el_2.xpm", x, y + 55);
		render_image(g, "textures/env/el_3.xpm", x + 10, y + 40);
		render_image(g, "textures/env/el_4.xpm", x + 35, y + 55);
	}
	else if (tx == 4 && ty == 6)
		render_image(g, "textures/env/obj_3.xpm", x, y - 10);
	else if (tx == 2 && ty == 4)
	{
		render_image(g, "textures/env/obj_2.xpm", x, y + 5);
		render_image(g, "textures/env/object_21.xpm", x + 74, y + 10);
		render_image(g, "textures/env/object_22.xpm", x, y + 40);
	}
	else if (tx == 3 && ty == 6)
		render_image(g, "textures/env/object_25.xpm", x, y + 10);
}

void	render_map_design(t_game *g)
{
	int	i;
	int	j;
	int	xy[2];
	int	tile[2];

	i = -1;
	xy[1] = 0;
	while (++i < g->map->y && g->map->ptr[i] && g->map->is_sp)
	{
		j = -1;
		xy[0] = 0;
		while (g->map->ptr[i][++j])
		{
			tile[0] = xy[0] / TILE_SIZE;
			tile[1] = xy[1] / TILE_SIZE;
			if (g->map->ptr[i][j] == '1')
			{
				render_special_props(g, tile[0], tile[1], xy);
				render_tile_special(g, tile[0], tile[1], xy);
				render_additional_decor(g, tile[0], tile[1], xy);
			}
			xy[0] += TILE_SIZE;
		}
		xy[1] += TILE_SIZE;
	}
}
