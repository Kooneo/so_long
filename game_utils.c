/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:24:55 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 13:25:20 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_move_valid(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0 || new_x >= (game->map->x * TILE_SIZE)
		|| (new_y >= (game->map->y * TILE_SIZE)))
		return (0);
	if (game->map->ptr[new_y / 64][new_x / 64] == '1')
		return (0);
	return (1);
}

int	is_coin(t_game *game, int new_x, int new_y)
{
	if (game->map->ptr[new_y / 64][new_x / 64] == 'C')
		return (1);
	return (0);
}

int	is_the_curse(t_game *game, int new_x, int new_y)
{
	if (game->map->ptr[new_y / 64][new_x / 64] == 'X')
		return (1);
	return (0);
}

int	is_the_curse_remover(t_game *game, int new_x, int new_y)
{
	if (game->map->ptr[new_y / 64][new_x / 64] == 'G')
		return (1);
	return (0);
}

int	is_exit_and_valid(t_game *game, int new_x, int new_y)
{
	if (game->map->ptr[new_y / 64][new_x / 64] == 'E'
		&& game->player->items_collected == game->map->coins_count)
		return (1);
	return (0);
}
