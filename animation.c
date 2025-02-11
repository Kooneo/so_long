/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:17:49 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/11 15:57:05 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**get_frames(char *direction, int *frame_count)
{
	static char	*frames_up[] = {
		"textures/player/p_up/p_up_00.xpm",
		"textures/player/p_up/p_up_01.xpm",
		"textures/player/p_up/p_up_02.xpm",
		"textures/player/p_up/p_up_03.xpm",
		"textures/player/p_up/p_up_04.xpm",
		"textures/player/p_up/p_up_05.xpm",
		"textures/player/p_up/p_up_06.xpm",
		"textures/player/p_up/p_up_07.xpm",
		NULL
	};
	static char	*frames_down[] = {
		"textures/player/p_down/p_down_00.xpm",
		"textures/player/p_down/p_down_01.xpm",
		"textures/player/p_down/p_down_02.xpm",
		"textures/player/p_down/p_down_03.xpm",
		"textures/player/p_down/p_down_04.xpm",
		"textures/player/p_down/p_down_05.xpm",
		"textures/player/p_down/p_down_06.xpm",
		"textures/player/p_down/p_down_07.xpm",
		NULL
	};
	static char	*frames_left[] = {
		"textures/player/p_left/xpm/p_left_00.xpm",
		"textures/player/p_left/xpm/p_left_01.xpm",
		"textures/player/p_left/xpm/p_left_02.xpm",
		"textures/player/p_left/xpm/p_left_03.xpm",
		"textures/player/p_left/xpm/p_left_04.xpm",
		"textures/player/p_left/xpm/p_left_05.xpm",
		"textures/player/p_left/xpm/p_left_06.xpm",
		"textures/player/p_left/xpm/p_left_07.xpm",
		NULL
	};
	static char	*frames_right[] = {
		"textures/player/p_right/p_right_00.xpm",
		"textures/player/p_right/p_right_01.xpm",
		"textures/player/p_right/p_right_02.xpm",
		"textures/player/p_right/p_right_03.xpm",
		"textures/player/p_right/p_right_04.xpm",
		"textures/player/p_right/p_right_05.xpm",
		"textures/player/p_right/p_right_06.xpm",
		"textures/player/p_right/p_right_07.xpm",
		NULL
	};
	if (ft_strncmp(direction, "up", 2) == 0)
		return (*frame_count = 8, frames_up);
	if (ft_strncmp(direction, "down", 4) == 0)
		return (*frame_count = 8, frames_down);
	if (ft_strncmp(direction, "left", 4) == 0)
		return (*frame_count = 8, frames_left);
	if (ft_strncmp(direction, "right", 5) == 0)
		return (*frame_count = 8, frames_right);
	return (NULL);
}

void	animate_player(t_game *game, t_paramholder p, char *direction)
{
	char	**frames;
	int		frame_count;
	char	*file_path;
	int		i;
	int		y;
	int		x;

	frames = get_frames(direction, &frame_count);
	if (!frames)
		return ;
	i = 0;
	while (i < frame_count)
	{
		x = p.i + (p.x - p.i) * (i + 1) / frame_count;
		y = p.j + (p.y - p.j) * (i + 1) / frame_count;
		file_path = frames[i];
		render_image(game, "textures/bg_64n.xpm", x, y);
		render_image(game, "textures/bg_64n.xpm", p.i, p.j);
		render_image(game, file_path, x, y);
		usleep(game->player->sleep_time);
		i++;
		mlx_put_image_to_window(game->window->mlx, game->window->win,
			game->base_img->img_ptr, 0, 0);
	}
}
