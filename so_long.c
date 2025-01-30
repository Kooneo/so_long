/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:01:03 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 14:39:05 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (!check_is_rectangular(map) || !check_psec_dup(map))
	{
		show_err("Invalid Map.");
		i = 0;
		while (map->ptr[i])
			free(map->ptr[i++]);
		exit(-1);
	}
}

// TODO:
// esc: exit game
// x button: exits game
// add flood fill algo
// map error if the map file is not .ber
void	init_game(t_game *game, t_map *map, t_win *window, t_player *player, char *mapname)
{
	map_init(map, mapname);
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

int	main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_win		window;
	t_player	player;
	char		*mapname;
	t_img		base_image;

	if (argc != 2)
		show_err("Usage: ./so_long <map>");
	mapname = argv[1];
	init_game(&game, &map, &window, &player, mapname);
	base_image = new_img(window.width, window.hight, window);
	game.base_img = &base_image;
	map_render(&game);
	setup_hooks(&window, &game);
	mlx_loop(window.mlx);
	return (0);
}
