/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:01:03 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 14:18:41 by zbakour          ###   ########.fr       */
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
int	main(int argc, char **argv)
{
	t_game	game;
	char	*mapname;
	t_map	map;
	t_img	base_image;

	if (argc != 2)
		show_err("Usage: ./so_long <map>");
	mapname = argv[1];
	map_init(&map, mapname);
	game.map = &map;
	init_game(&game, mapname);
	// Initialize key states
	int_keystate(&game);
	base_image = new_img(game.window->width, game.window->hight,
			*(game.window));
	game.base_img = &base_image;
	map_render(&game);
	mlx_hook(game.window->win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.window->win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.window->mlx, handle_player_movement, &game);
	mlx_loop(game.window->mlx);
	return (0);
}
