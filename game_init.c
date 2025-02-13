/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:41:20 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/13 18:08:55 by zbakour          ###   ########.fr       */
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

void count_enemies(t_map *map)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = -1;
	y = 0;
	while (++i < map->y && map->ptr[i])
	{
		x = 0;
		j = -1;
		while (map->ptr[i][++j])
		{
			if ( map->ptr[i][j] == 'T')
				map->enemy_count++;
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
}

void	init_game(t_game *game, t_map *map, t_win *window, t_player *player)
{
	map_init(map, map->filepath);
	init_window(window, map->y, map->x);
	player->moves_count = 0;
	player->items_collected = 0;
	player->sleep_time = 38000;
	game->map = map;
	game->window = window;
	game->player = player;
	game->map->exit_x = 0;
	game->map->exit_y = 0;

}

void	setup_hooks(t_win *window, t_game *game)
{
	int_keystate(game);
	mlx_hook(window->win, 2, 1L << 0, key_press, game);
	mlx_hook(window->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(window->mlx, handle_player_movement, game);
	// mlx_loop_hook(window->mlx, update_game, game);

	mlx_hook(window->win, 17, 0, exit_game, game);
	

}

void	map_init(t_map *map, char *filepath)
{
	if (!map || !filepath)
		return ;
	map->ptr = NULL;
	map->size = 0;
	map->x = 0;
	map->y = 0;
	map->filepath = filepath;
	map->coins_count = 0;
	map->is_sp = 0;
	map->enemy_count = 0;
	map->ptr = load_map(map);
	if (!check_is_rectangular(map) || !check_psec_dup(map))
	{
		free_map(map->ptr);
		show_err("Invalid Map.");
	}
}
