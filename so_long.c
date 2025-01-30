/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:01:03 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 14:13:01 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


// TODO:
// esc: exit game
// x button: exits game
// add flood fill algo
// map error if the map file is not .ber
int	main(int argc, char **argv)
{
	t_game		game;
	char		*mapname;
	t_img		base_image;
	if (argc != 2)
		show_err("Usage: ./so_long <map>");
	mapname = argv[1];
	game = init_game(&game, mapname);
	
	// Initialize key states
	int_keystate(&game);
	base_image = new_img(game.window->width, game.window->hight, *(game.window));
	game.base_img = &base_image;
	
	map_render(&game);
	mlx_hook(game.window->win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.window->win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.window->mlx, handle_player_movement, &game);
	mlx_loop(game.window->mlx);
	return (0);
}
