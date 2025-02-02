/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 13:43:38 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/02 13:52:05 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_special_cases(t_game *g, int new_x, int new_y, char *dir)
{
	if (is_exit_and_valid(g, new_x, new_y) && dir)
	{
		ft_printf("\nI came, I played, I won! 🎉👑\n");
		exit_game(g);
	}
	else if (g->map->ptr[new_y / 64][new_x / 64] == 'T' && dir)
	{
		ft_printf("\nGame over... 🏁 you lose! 😜\n");
		exit_game(g);
	}
}

void	handle_collectibles(t_game *g, int new_x, int new_y)
{
	const int	x = new_x / 64;
	const int	y = new_y / 64;

	if (is_coin(g, new_x, new_y))
	{
		g->player->items_collected++;
		g->map->ptr[y][x] = '0';
	}
	else if (is_the_curse(g, new_x, new_y))
	{
		g->player->sleep_time /= 2;
		g->map->ptr[y][x] = '0';
	}
	else if (is_the_curse_remover(g, new_x, new_y))
	{
		if (g->player->sleep_time < 45000)
			g->player->sleep_time *= 2;
		g->map->ptr[y][x] = '0';
	}
	render_image(g, "textures/bg_64n.xpm", new_x, new_y);
}
