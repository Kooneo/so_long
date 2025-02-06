/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:41:20 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/06 19:31:52 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_window(t_win *window, int map_y, int map_x)
{
	window->hight = map_y * TILE_SIZE;
	window->width = map_x * TILE_SIZE;
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, window->width, window->hight,
			"Drunk Runner!");
	if (!window->win || !window->mlx)
		return ;
}

void	init_game(t_game *game, t_map *map, t_win *window, t_player *player)
{
	map_init(map, map->filepath);
	map->coins_count = 0;
	map->is_sp = 0;
	init_window(window, map->y, map->x);
	player->moves_count = 0;
	player->items_collected = 0;
	player->sleep_time = 45000;
	game->map = map;
	game->window = window;
	game->player = player;
	int_keystate(game);
	game->map->exit_x = 0;
	game->map->exit_y = 0;
}

void	setup_hooks(t_win *window, t_game *game)
{
	mlx_hook(window->win, 2, 1L << 0, key_press, game);
	mlx_hook(window->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(window->mlx, handle_player_movement, game);
}

void	map_init(t_map *map, char *filepath)
{
	int	i;

	if (!map || !filepath)
		return ;
	map->ptr = NULL;
	map->size = 0;
	map->x = 0;
	map->y = 0;
	map->filepath = filepath;
	map->ptr = load_map(map);
	if (!check_is_rectangular(map) || !check_psec_dup(map) || !map_check(map))
	{
		show_err("Invalid Map.");
		i = 0;
		while (map->ptr[i])
			free(map->ptr[i++]);
		exit(-1);
	}
}
