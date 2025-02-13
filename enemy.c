/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:13:17 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/13 18:34:54 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void move_enemy(t_game *game, t_enemy *enemy)
{
    int new_x = enemy->x + enemy->direction;
    int new_y = enemy->y; // Keep y the same for left/right movement
    // Collision check: If the enemy hits a wall, change direction
    if (game->map->ptr[new_y][new_x] == '1') 
        enemy->direction *= -1; // Reverse direction
    else
    {
        // Clear the old position
        game->map->ptr[enemy->y][enemy->x] = '0';
        // Move to the new position
        render_image(game, "textures/bg_64n.xpm",  enemy->x * TILE_SIZE, enemy->y * TILE_SIZE);
        enemy->x = new_x;
        game->map->ptr[enemy->y][enemy->x] = 'T';
        render_image(game, "textures/env/enemy.xpm", new_x * TILE_SIZE, enemy->y * TILE_SIZE);
    }
    ft_printf("enemy: {x: %d, y: %d, dir: %d}\n", enemy->x * TILE_SIZE, enemy->y * TILE_SIZE, enemy->direction);

}

void move_enemy_vertical(t_game *game, t_enemy *enemy)
{
    int new_y = enemy->y + enemy->direction;
    int new_x = enemy->x; // Keep x the same for up/down movement

    if (game->map->ptr[new_y][new_x] == '1')
        enemy->direction *= -1;
    else
    {
        game->map->ptr[enemy->y][enemy->x] = '0';
        enemy->y = new_y;
        game->map->ptr[enemy->y][enemy->x] = 'T';
    }
}

void    print_map(t_game *g)
{
    for (size_t i = 0; i < g->map->y; i++)
    {
        for (size_t j = 0; j < g->map->x; j++)
        {
            ft_printf("%c", g->map->ptr[i][j]);
        }
        
    }
    
}



// int	enemy_is_move_valid(t_game *game, int new_x, int new_y)
// {
// 	if (new_x < 0 || new_y < 0 || new_x >= ((game->map->x - 2) * TILE_SIZE)
// 		|| (new_y >= (game->map->y * TILE_SIZE)))
// 		return (0);
// 	if (game->map->ptr[new_y / 64][new_x / 64] == '1')
// 		return (0);
// 	return (1);
// }

// void move_enemy(t_game *game, int index)
// {
//     (void)index; 
//     int speed = 1; // Adjust speed if needed

//     // Access enemy position
//     int enemy_x = game->enemies[0].x_pos;
//     // int enemy_y = game->enemies[0].y_pos;

//     // Access player position
//     // int player_x = game->player->x_pos;
//     // int player_y = game->player->y_pos;

//     ft_printf("enemy pos x: %d, y: %d\n", game->enemies[0].x_pos, game->enemies[0].y_pos);
//     ft_printf("map end pos x: %d, y: %d\n", game->map->x * TILE_SIZE, game->map->y * TILE_SIZE);
//     // Move the enemy towards the player
//     if (enemy_x < game->player->x_pos)
//     {
//         if (enemy_is_move_valid(game,  game->enemies[0].x_pos + speed,  game->enemies[0].y_pos))
//         {
//             game->enemies[0].x_pos += speed;
//         }
//     }
//     else if (enemy_x > game->player->x_pos)
//     {
//         if (enemy_is_move_valid(game,  game->enemies[0].x_pos - speed, game->enemies[0].y_pos))
//         {
//             game->enemies[0].x_pos -= speed;
//         }
//         // game->enemies[index].x_pos -= speed;
//     }

//     // if (enemy_y <  (int)game->player->y_pos)
//     // {
//     //     // if (is_move_valid(game, enemy_x + speed, enemy_y + speed))
//     //     // {
//     //     game->enemies[0].y_pos += speed;
//     //     // }
//     //     // game->enemies[index].y_pos += speed;

//     // }
//     // else
//     // {
//     //     // if (is_move_valid(game, enemy_x - speed, enemy_y - speed))
//     //     // {
//     //         game->enemies[0].y_pos -= speed;
//     //     // }
//     //     // game->enemies[index].y_pos -= speed;

//     // }
// }
