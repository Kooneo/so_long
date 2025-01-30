/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:41:20 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 14:19:02 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_win	*init_window(t_win *window, int map_y, int map_x)
{
	window->hight = map_y * TILE_SIZE;
	window->width = map_x * TILE_SIZE;
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, window->width, window->hight,
			"Drunk Runner!");
	if (!window->win || !window->mlx)
		return (NULL);
	return (window);
}


t_player	*init_player(t_player *player)
{
	player->moves_count = 0;
	player->items_collected = 0;
	player->sleep_time = 45000;
	return (player);
}

void init_game(t_game *game)
{
	t_win window;
	t_player player;
	game->window = init_window(&window, game->map->y, game->map->x);
	game->player = init_player(&player);
}