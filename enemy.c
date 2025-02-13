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


int	enemy_is_move_valid(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0 || new_x >= ((game->map->x - 2) * TILE_SIZE)
		|| (new_y >= (game->map->y * TILE_SIZE)))
		return (0);
	if (game->map->ptr[new_y / 64][new_x / 64] == '1')
		return (0);
	return (1);
}

void move_enemy(t_game *game, int index)
{
    (void)index; 
    int speed = 1; // Adjust speed if needed

    // Access enemy position
    int enemy_x = game->enemies[0].x_pos;
    // int enemy_y = game->enemies[0].y_pos;

    // Access player position
    // int player_x = game->player->x_pos;
    // int player_y = game->player->y_pos;

    ft_printf("enemy pos x: %d, y: %d\n", game->enemies[0].x_pos, game->enemies[0].y_pos);
    ft_printf("map end pos x: %d, y: %d\n", game->map->x * TILE_SIZE, game->map->y * TILE_SIZE);
    // Move the enemy towards the player
    if (enemy_x < game->player->x_pos)
    {
        if (enemy_is_move_valid(game,  game->enemies[0].x_pos + speed,  game->enemies[0].y_pos))
        {
            game->enemies[0].x_pos += speed;
        }
    }
    else if (enemy_x > game->player->x_pos)
    {
        if (enemy_is_move_valid(game,  game->enemies[0].x_pos - speed, game->enemies[0].y_pos))
        {
            game->enemies[0].x_pos -= speed;
        }
        // game->enemies[index].x_pos -= speed;
    }

    // if (enemy_y <  (int)game->player->y_pos)
    // {
    //     // if (is_move_valid(game, enemy_x + speed, enemy_y + speed))
    //     // {
    //     game->enemies[0].y_pos += speed;
    //     // }
    //     // game->enemies[index].y_pos += speed;

    // }
    // else
    // {
    //     // if (is_move_valid(game, enemy_x - speed, enemy_y - speed))
    //     // {
    //         game->enemies[0].y_pos -= speed;
    //     // }
    //     // game->enemies[index].y_pos -= speed;

    // }
}
