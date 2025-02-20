/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:44:23 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 16:36:35 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_ground(t_game *game, char *filepath)
{
	t_img	src_img;
	int		x;
	int		y;

	src_img = new_file_img(filepath, *(game->window));
	if (!src_img.img_ptr)
		return ;
	y = 0;
	while (y < game->window->hight)
	{
		x = 0;
		while (x < game->window->width)
		{
			put_img_to_img(*(game->base_img), src_img, x, y);
			x += src_img.w;
		}
		y += src_img.h;
	}
	destroy_image(src_img);
}
