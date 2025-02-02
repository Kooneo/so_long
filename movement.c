/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:12:36 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/02 13:32:40 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	handle_player_movement(t_game *game)
// {
// 	int		new_x;
// 	int		new_y;
// 	int		old_x;
// 	int		old_y;
// 	char	*direction;

// 	new_x = game->player->x_pos;
// 	new_y = game->player->y_pos;
// 	old_x = game->player->x_pos;
// 	old_y = game->player->y_pos;
// 	direction = NULL;
// 	if (game->key_states[119])
// 	{
// 		new_y -= 64;
// 		direction = "up";
// 	}
// 	else if (game->key_states[115])
// 	{
// 		new_y += 64;
// 		direction = "down";
// 	}
// 	else if (game->key_states[100])
// 	{
// 		new_x += 64;
// 		direction = "right";
// 	}
// 	else if (game->key_states[97])
// 	{
// 		new_x -= 64;
// 		direction = "left";
// 	}
// 	else if (game->key_states[65307])
// 		exit_game(game);
// 	if (game->player->items_collected == game->map->coins_count)
// 		render_exit(game);
// 	if (direction && is_exit_and_valid(game, new_x, new_y))
// 	{
// 		ft_printf("\nI came, I played, I won! 🎉👑\n");
// 		exit_game(game);
// 	}
// 	else if (game->map->ptr[new_y / 64][new_x / 64] == 'T')
// 	{
// 		ft_printf("\nGame over, you gave it your all... but 🏁 you lose! 😜\n");
// 		exit_game(game);
// 	}
// 	else if (direction && is_move_valid(game, new_x, new_y)
// 		&& is_the_curse(game, new_x, new_y))
// 	{
// 		game->player->sleep_time = game->player->sleep_time / 2;
// 		game->map->ptr[new_y / 64][new_x / 64] = '0';
// 		render_image(game, "textures/bg_64n.xpm", new_x, new_y);
// 	}
// 	else if (direction && is_move_valid(game, new_x, new_y)
// 		&& is_the_curse_remover(game, new_x, new_y))
// 	{
// 		if (game->player->sleep_time < 45000)
// 		{
// 			game->player->sleep_time = game->player->sleep_time * 2;
// 			game->map->ptr[new_y / 64][new_x / 64] = '0';
// 		}
// 		render_image(game, "textures/bg_64n.xpm", new_x, new_y);
// 	}
// 	else if (direction && is_move_valid(game, new_x, new_y) && is_coin(game,
// 			new_x, new_y))
// 	{
// 		game->player->items_collected += 1;
// 		game->map->ptr[new_y / 64][new_x / 64] = '0';
// 		render_image(game, "textures/bg_64n.xpm", new_x, new_y);
// 	}
// 	else if (direction && is_move_valid(game, new_x, new_y))
// 	{
// 		game->player->moves_count++;
// 		animate_player(game, old_x, old_y, new_x, new_y, direction);
// 		game->player->x_pos = new_x;
// 		game->player->y_pos = new_y;
// 		render_movement_count(game);
// 	}
// 	else
// 	{	
// 	}
// 	mlx_put_image_to_window(game->window->mlx, game->window->win,
// 		game->base_img->img_ptr, 0, 0);
// 	return (0);
// }

// void	render_exit(t_game *game)
// {
// 	render_image(game, "textures/env/exit_wall.xpm", game->map->exit_x - 2,
// 		game->map->exit_y - 2);
// 	render_image(game, "textures/env/exit_door.xpm", game->map->exit_x + 12,
// 		game->map->exit_y + 13);
// 	mlx_put_image_to_window(game->window->mlx, game->window->win,
// 		game->base_img->img_ptr, 0, 0);
// }

static void	handle_idle_animation(t_game *g)
{
	render_image(g, "textures/bg_64n.xpm", g->player->x_pos,
		g->player->y_pos);
	render_image(g, "textures/player/p_idle/down/idle_down_00.xpm",
		g->player->x_pos, g->player->y_pos);
	mlx_put_image_to_window(g->window->mlx, g->window->win,
		g->base_img->img_ptr, 0, 0);
}

static int	handle_movement_keys(int *new_xy, t_game *g, char **dir)
{
	const int	keys[] = {119, 115, 100, 97};
	const int	mov[] = {-64, 64, 64, -64};
	const char	*directions[] = {"up", "down", "right", "left"};
	int			i;

	i = -1;
	while (++i < 4)
	{
		if (g->key_states[keys[i]])
		{
			if (i < 2)
				new_xy[1] += mov[i];
			else
				new_xy[0] += mov[i];
			*dir = (char *)directions[i];
			return (1);
		}
	}
	if (g->key_states[65307])
		exit_game(g);
	return (0);
}

static void	handle_special_cases(t_game *g, int new_x, int new_y, char *dir)
{
	if (is_exit_and_valid(g, new_x, new_y) && dir)
	{
		ft_printf("\nI came, I played, I won! 🎉👑\n");
		exit_game(g);
	}
	else if (g->map->ptr[new_y / 64][new_x / 64] == 'T' && dir)
	{
		ft_printf("\nGame over... 🏁 you lose! 😜\n");
		exit_game(g);
	}
}

static void	handle_collectibles(t_game *g, int new_x, int new_y)
{
	const int	x = new_x / 64;
	const int	y = new_y / 64;

	if (is_coin(g, new_x, new_y))
	{
		g->player->items_collected++;
		g->map->ptr[y][x] = '0';
	}
	else if (is_the_curse(g, new_x, new_y))
	{
		g->player->sleep_time /= 2;
		g->map->ptr[y][x] = '0';
	}
	else if (is_the_curse_remover(g, new_x, new_y))
	{
		if (g->player->sleep_time < 45000)
			g->player->sleep_time *= 2;
		g->map->ptr[y][x] = '0';
	}
	render_image(g, "textures/bg_64n.xpm", new_x, new_y);
}

static void	handle_move_execution(t_game *g, int new_xy[2],
								int old_xy[2], char *d)
{
	if (is_move_valid(g, new_xy[0], new_xy[1]))
	{
		g->player->moves_count++;
		animate_player(g, old_xy[0], old_xy[1], new_xy[0], new_xy[1], d);
		g->player->x_pos = new_xy[0];
		g->player->y_pos = new_xy[1];
		render_movement_count(g);
	}
}

int	handle_player_movement(t_game *game)
{
	int		new_xy[2];
	int		old_xy[2];
	char	*direction;

	new_xy[0] = game->player->x_pos;
	new_xy[1] = game->player->y_pos;
	old_xy[0] = new_xy[0];
	old_xy[1] = new_xy[1];
	direction = NULL;
	if (!handle_movement_keys(new_xy, game, &direction))
		return (handle_idle_animation(game), 0);
	if (game->player->items_collected == game->map->coins_count)
		render_exit(game);
	handle_special_cases(game, new_xy[0], new_xy[1], direction);
	if (is_move_valid(game, new_xy[0], new_xy[1]))
	{
		handle_collectibles(game, new_xy[0], new_xy[1]);
		handle_move_execution(game, new_xy, old_xy, direction);
	}
	else
		handle_idle_animation(game);
	mlx_put_image_to_window(game->window->mlx, game->window->win,
		game->base_img->img_ptr, 0, 0);
	return (0);
}

