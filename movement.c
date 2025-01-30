/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:12:36 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 16:34:30 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_digit(t_game *game, int digit, int x, int y)
{
	char	*file_path;
	char	*d;

	if (digit < 0 || digit > 9)
		return ;
	d = ft_itoa(digit);
	file_path = ft_strjoin("textures/numbers/", d);
	file_path = ft_strjoin_free(file_path, ".xpm");
	render_image(game, file_path, x, y);
	free(file_path);
	free(d);
}

void	render_movement_count(t_game *game)
{
	int	movement_count;
	int	digit_x;
	int	digit_y;
	int	m;
	int	divisor;

	movement_count = game->player->moves_count;
	digit_x = 10;
	digit_y = 10;
	m = 1;
	render_image(game, "textures/wall_m.xpm", 0, 0);
	while (m < game->map->x - 2)
		render_image(game, "textures/wall_b.xpm", 64 * m++, 0);
	if (movement_count == 0)
		return (render_digit(game, 0, digit_x, digit_y));
	divisor = 1;
	while (movement_count / divisor >= 10)
		divisor *= 10;
	while (divisor > 0)
	{
		render_digit(game, movement_count / divisor, digit_x, digit_y);
		digit_x += 30;
		movement_count %= divisor;
		divisor /= 10;
	}
}

static void	handle_key_input(t_game *game, t_movement *move)
{
	move->new_x = game->player->x_pos;
	move->new_y = game->player->y_pos;
	move->direction = NULL;
	if (game->key_states[119])
	{
		move->new_y -= 64;
		move->direction = "up";
	}
	else if (game->key_states[115])
	{
		move->new_y += 64;
		move->direction = "down";
	}
	else if (game->key_states[100])
	{
		move->new_x += 64;
		move->direction = "right";
	}
	else if (game->key_states[97])
	{
		move->new_x -= 64;
		move->direction = "left";
	}
	else if (game->key_states[65307])
		exit_game(game);
}

static void	check_and_render_exit(t_game *game)
{
	if (game->player->items_collected == game->map->coins_count)
		render_exit(game);
}

static int	check_conditions(t_game *game, t_movement *move)
{
	(void)game;
	(void)move;
	// if (check_exit(game, move) || check_trap(game, move) || check_curse(game,
	// 		move) || check_curse_remover(game, move) || check_coin(game, move)
	// 	|| check_valid_move(game, move))
	// 	return (1);
	return (1);
}

static void	render_idle_player(t_game *game)
{
	render_image(game, "textures/bg_64n.xpm", game->player->x_pos,
		game->player->y_pos);
	render_image(game, "textures/player/p_idle/down/idle_down_00.xpm",
		game->player->x_pos, game->player->y_pos);
	mlx_put_image_to_window(game->window->mlx, game->window->win,
		game->base_img->img_ptr, 0, 0);
}

int	handle_player_movement(t_game *game)
{
	t_movement	move;

	move.old_x = game->player->x_pos;
	move.old_y = game->player->y_pos;
	handle_key_input(game, &move);
	check_and_render_exit(game);
	if (check_conditions(game, &move))
	{
		mlx_put_image_to_window(game->window->mlx, game->window->win,
			game->base_img->img_ptr, 0, 0);
		return (0);
	}
	render_idle_player(game);
	mlx_put_image_to_window(game->window->mlx, game->window->win,
		game->base_img->img_ptr, 0, 0);
	return (0);
}

void	render_exit(t_game *game)
{
	render_image(game, "textures/env/exit_wall.xpm", game->map->exit_x - 2,
		game->map->exit_y - 2);
	render_image(game, "textures/env/exit_door.xpm", game->map->exit_x + 12,
		game->map->exit_y + 13);
	mlx_put_image_to_window(game->window->mlx, game->window->win,
		game->base_img->img_ptr, 0, 0);
}
