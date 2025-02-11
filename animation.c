/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:17:49 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/11 16:35:20 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_player(t_game *game, t_paramholder p, char *direction)
{
	static int	frame_count = 8;
	char		*file_path;
	int			i;
	int			y;
	int			x;

	i = 0;
	while (i < frame_count)
	{
		x = p.i + (p.x - p.i) * (i + 1) / frame_count;
		y = p.j + (p.y - p.j) * (i + 1) / frame_count;
		file_path = get_frames(direction)[i];
		render_image(game, "textures/bg_64n.xpm", x, y);
		render_image(game, "textures/bg_64n.xpm", p.i, p.j);
		render_image(game, file_path, x, y);
		usleep(game->player->sleep_time);
		i++;
		mlx_put_image_to_window(game->window->mlx, game->window->win,
			game->base_img->img_ptr, 0, 0);
	}
}
