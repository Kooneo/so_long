/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:15:43 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/11 16:37:05 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_game *game)
{
	printf("%d", keycode);
	if (keycode >= 0 && keycode < 256)
		game->key_states[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->key_states[keycode] = 0;
	return (0);
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
