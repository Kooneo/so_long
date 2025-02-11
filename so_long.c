/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:01:03 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/11 18:05:36 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// TODO:
// map error if the map file is not .ber
// make enemy follows the player

int	main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_win		window;
	t_player	player;
	t_img		base_image;

	if (argc != 2)
		show_err("Usage: ./so_long <map>");
	map.filepath = argv[1];
	init_game(&game, &map, &window, &player);
	base_image = new_img(window.width, window.hight, window);
	game.base_img = &base_image;
	map_render(&game);
	setup_hooks(&window, &game);
	mlx_loop(window.mlx);
	return (0);
}
