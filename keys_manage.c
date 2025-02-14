/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:15:43 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/14 20:32:51 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game(game);
	if (keycode >= 0 && keycode < 256)
		game->key_states[keycode] = 1;
}

void	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->key_states[keycode] = 0;
}

void	int_keystate(t_game *game)
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		game->key_states[i] = 0;
		i++;
	}
}

static int	handle_movement_keys(int *new_xy, t_game *g, char **dir)
{
	const int keys[] = {119, 115, 100, 97};
	const int mov[] = {-64, 64, 64, -64};
	const char *directions[] = {"up", "down", "right", "left"};
	int i;

	i = -1;
	while (++i < 4)
	{
		if (g->key_states[keys[i]])
		{
			if (i < 2)
				new_xy[1] += mov[i];
			else
				new_xy[0] += mov[i];
			*dir = (char *)directions[i];
			return (1);
		}
	}
	if (g->key_states[65307])
		exit_game(g);
	return (0);
}