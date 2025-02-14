/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:12:36 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/14 20:32:42 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_exit(t_game *game)
{
	render_image(game, "textures/env/exit_wall.xpm", game->map->exit_x - 2,
		game->map->exit_y - 2);
	render_image(game, "textures/env/exit_door.xpm", game->map->exit_x + 12,
		game->map->exit_y + 13);
	mlx_put_image_to_window(game->window->mlx, game->window->win,
		game->base_img->img_ptr, 0, 0);
}

static void	handle_idle_animation(t_game *g)
{
	render_image(g, "textures/bg_64n.xpm", g->player->x_pos, g->player->y_pos);
	render_image(g, "textures/player/p_idle/down/idle_down_00.xpm",
		g->player->x_pos, g->player->y_pos);
	mlx_put_image_to_window(g->window->mlx, g->window->win,
		g->base_img->img_ptr, 0, 0);
}

static void	handle_move_execution(t_game *g, int new_xy[2], int old_xy[2],
		char *d)
{
	if (is_move_valid(g, new_xy[0], new_xy[1]))
	{
		g->player->moves_count++;
		animate_player(g, (t_paramholder){old_xy[0], old_xy[1], new_xy[0],
			new_xy[1]}, d);
		g->player->x_pos = new_xy[0];
		g->player->y_pos = new_xy[1];
		render_movement_count(g);
	}
}

void	handle_valid_move(t_game *game, int *new_xy, int *old_xy,
		char *direction)
{
	move_enemies(game);
	handle_collectibles(game, new_xy[0], new_xy[1]);
	handle_move_execution(game, new_xy, old_xy, direction);
}

int	handle_player_movement(t_game *game)
{
	int			new_xy[2];
	int			old_xy[2];
	char		*direction;
	static int	frame;

	new_xy[0] = game->player->x_pos;
	new_xy[1] = game->player->y_pos;
	old_xy[0] = new_xy[0];
	old_xy[1] = new_xy[1];
	direction = NULL;
	frame = 0;
	if (frame++ % 150 == 0)
		move_enemies(game);
	if (!handle_movement_keys(new_xy, game, &direction))
		return (handle_idle_animation(game), 0);
	if (game->player->items_collected == game->map->coins_count)
		render_exit(game);
	handle_special_cases(game, new_xy[0], new_xy[1], direction);
	if (is_move_valid(game, new_xy[0], new_xy[1]))
		handle_valid_move(game, new_xy, old_xy, direction);
	else
		handle_idle_animation(game);
	mlx_put_image_to_window(game->window->mlx, game->window->win,
		game->base_img->img_ptr, 0, 0);
	return (0);
}
