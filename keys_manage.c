/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:15:43 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 13:19:43 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->key_states[keycode] = 1; // Mark key as pressed
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->key_states[keycode] = 0; // Mark key as released
	return (0);
}

void	int_keystate(t_game *game)
{
	int i = 0;
	while (i < 1000000)
	{
		game->key_states[i] = 0;
		i++;
	}
}