/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:15:43 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/13 18:59:32 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game(game);
	if (keycode >= 0 && keycode < 256)
		game->key_states[keycode] = 1;
	return (1);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->key_states[keycode] = 0;
	return (1);
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
