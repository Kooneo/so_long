/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:13:17 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/11 18:34:48 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void move_enemy(t_game *game, int index)
{
    int speed = 2; // Adjust speed if needed

    // Access enemy position
    int enemy_x = game->enemies[index].x_pos;
    int enemy_y = game->enemies[index].y_pos;

    // Access player position
    int player_x = game->player->x_pos;
    int player_y = game->player->y_pos;

    // Move the enemy towards the player
    if (enemy_x < player_x)
        game->enemies[index].x_pos += speed;
    else if (enemy_x > player_x)
        game->enemies[index].x_pos -= speed;

    if (enemy_y < player_y)
        game->enemies[index].y_pos += speed;
    else if (enemy_y > player_y)
        game->enemies[index].y_pos -= speed;
}
