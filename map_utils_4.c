/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:28:26 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/11 15:27:06 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		&& (game->map->ptr[p.i][p.j + 1] == '0'
		|| game->map->ptr[p.i][p.j + 1] == 'P'
			|| game->map->ptr[p.i][p.j + 1] == 'C' || game->map->ptr[p.i][p.j
			+ 1] == 'E' || game->map->ptr[p.i][p.j + 1] == 'G'
			|| game->map->ptr[p.i][p.j + 1] == 'X'))
		render_image(game, "textures/xe_end.xpm", p.x, p.y);
	else
		render_image(game, "textures/mid_wall.xpm", p.x, p.y);
}
