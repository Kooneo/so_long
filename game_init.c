/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:41:20 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 13:46:44 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_window(t_win *window, int map_y, int map_x)
{
    window->hight = map_y * TILE_SIZE;
	window->width = map_x * TILE_SIZE;
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, window->width, window->hight, "Drunk Runner!");
	if (!window->win || !window->mlx)
		return ;
}