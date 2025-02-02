/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 13:20:25 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/02 13:20:32 by zbakour          ###   ########.fr       */
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

static void	render_wall_background(t_game *game)
{
	int	x;
	int	max_x;

	x = 0;
	max_x = (game->map->x - 2) * 64;
	render_image(game, "textures/wall_m.xpm", x, 0);
	x += 64;
	while (x < max_x)
	{
		render_image(game, "textures/wall_b.xpm", x, 0);
		x += 64;
	}
}

static void	handle_digits(int count, t_game *game, int start_x, int y)
{
	int	divisor;
	int	digit;

	divisor = 1;
	while (count / divisor >= 10)
		divisor *= 10;
	while (divisor > 0)
	{
		digit = count / divisor;
		render_digit(game, digit, start_x, y);
		start_x += 30;
		count %= divisor;
		divisor /= 10;
	}
}

void	render_movement_count(t_game *game)
{
	const int	movement_count = game->player->moves_count;
	const int	digit_y = 10;
	int			digit_x;

	render_wall_background(game);
	digit_x = 10;
	if (movement_count == 0)
	{
		render_digit(game, 0, digit_x, digit_y);
		return ;
	}
	handle_digits(movement_count, game, digit_x, digit_y);
}
