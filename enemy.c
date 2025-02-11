/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:13:17 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/11 18:19:18 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void move_enemy(t_game *game, int index)
{
    int speed = 2; // Adjust speed if needed

    if (game->enemy_x[index] < game->player_x)
        game->enemy_x[index] += speed;
    else if (game->enemy_x[index] > game->player_x)
        game->enemy_x[index] -= speed;

    if (game->enemy_y[index] < game->player_y)
        game->enemy_y[index] += speed;
    else if (game->enemy_y[index] > game->player_y)
        game->enemy_y[index] -= speed;
}
