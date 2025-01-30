/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:41:20 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 14:11:20 by zbakour          ###   ########.fr       */
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

t_map	*init_map(t_map *map, char *filepath)
{
	int	i;

	map->size = 0;
	map->x = 0;
	map->y = 0;
	map->filepath = filepath;
	map->ptr = load_map(map);
	map->coins_count = 0;
	map->is_sp = 0;
	map->exit_x = 0;
	map->exit_y = 0;
	if (!check_is_rectangular(map) || !check_psec_dup(map))
	{
		show_err("Invalid Map.");
		i = 0;
		while (map->ptr[i])
			free(map->ptr[i++]);
		exit(-1);
	}
	return (map);
}

t_player	*init_player(t_player *player)
{
	player->moves_count = 0;
	player->items_collected = 0;
	player->sleep_time = 45000;
	return (player);
}

t_game 	*init_game(t_game *game, char *map_path)
{
	t_win window;
	t_map map;
	t_player player;
	game->map = init_map(&map, map_path);
	game->window = init_window(&window, map.y, map.x);
	game->player = init_player(&player);

	return (game);
}