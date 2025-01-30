/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:12:36 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 15:31:57 by zbakour          ###   ########.fr       */
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
	int	digit;

	movement_count = game->player->moves_count;
	digit_x = 10;
	digit_y = 10;
	m = 1;
	render_image(game, "textures/wall_m.xpm", 0, 0);
	while (m < game->map->x - 2)
	{
		render_image(game, "textures/wall_b.xpm", 64 * m, 0);
		m++;
	}
	// Break the movement count into individual digits and render them
	if (movement_count == 0)
	{
		render_digit(game, 0, digit_x, digit_y); // Render '0' if the count is 0
		return ;
	}
	// Find the number of digits in movement_count
	divisor = 1;
	while (movement_count / divisor >= 10)
	{
		divisor *= 10;
	}
	// Render each digit one by one
	while (divisor > 0)
	{
		digit = movement_count / divisor;
		render_digit(game, digit, digit_x, digit_y);
		digit_x += 30;
		movement_count %= divisor; // Remove the most significant digit
		divisor /= 10;             // Reduce divisor by one order of magnitude
	}
}

int	handle_player_movement(t_game *game)
{
	int		new_x;
	int		new_y;
	int		old_x;
	int		old_y;
	char	*direction;

	new_x = game->player->x_pos;
	new_y = game->player->y_pos;
	old_x = game->player->x_pos;
	old_y = game->player->y_pos;
	direction = NULL;
	if (game->key_states[119])
	{
		new_y -= 64;
		direction = "up";
	}
	else if (game->key_states[115])
	{
		new_y += 64;
		direction = "down";
	}
	else if (game->key_states[100])
	{
		new_x += 64;
		direction = "right";
	}
	else if (game->key_states[97])
	{
		new_x -= 64;
		direction = "left";
	}
	else if (game->key_states[65307])
		exit_game(game);
	if (game->player->items_collected == game->map->coins_count)
		render_exit(game);
	if (direction && is_exit_and_valid(game, new_x, new_y))
	{
		ft_printf("\nI came, I played, I won! 🎉👑\n");
		exit_game(game);
	}
	else if (game->map->ptr[new_y / 64][new_x / 64] == 'T')
	{
		ft_printf("\nGame over, you gave it your all... but 🏁 you lose! 😜\n");
		exit_game(game);
	}
	else if (direction && is_move_valid(game, new_x, new_y)
		&& is_the_curse(game, new_x, new_y))
	{
		game->player->sleep_time = game->player->sleep_time / 2;
		game->map->ptr[new_y / 64][new_x / 64] = '0';
		render_image(game, "textures/bg_64n.xpm", new_x, new_y);
	}
	else if (direction && is_move_valid(game, new_x, new_y)
		&& is_the_curse_remover(game, new_x, new_y))
	{
		if (game->player->sleep_time < 45000)
		{
			game->player->sleep_time = game->player->sleep_time * 2;
			game->map->ptr[new_y / 64][new_x / 64] = '0';
		}
		render_image(game, "textures/bg_64n.xpm", new_x, new_y);
	}
	else if (direction && is_move_valid(game, new_x, new_y) && is_coin(game,
			new_x, new_y))
	{
		game->player->items_collected += 1;
		game->map->ptr[new_y / 64][new_x / 64] = '0';
		render_image(game, "textures/bg_64n.xpm", new_x, new_y);
	}
	else if (direction && is_move_valid(game, new_x, new_y))
	{
		game->player->moves_count++;
		animate_player(game, old_x, old_y, new_x, new_y, direction);
		game->player->x_pos = new_x;
		game->player->y_pos = new_y;
		render_movement_count(game);
	}
	else
	{
		render_image(game, "textures/bg_64n.xpm", game->player->x_pos,
			game->player->y_pos);
		render_image(game, "textures/player/p_idle/down/idle_down_00.xpm",
			game->player->x_pos, game->player->y_pos);
		mlx_put_image_to_window(game->window->mlx, game->window->win,
			game->base_img->img_ptr, 0, 0);
	}
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