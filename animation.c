/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:17:49 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 13:19:29 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_player(t_game *game, int old_x, int old_y, int new_x, int new_y,
		char *direction)
{
	char	**frames;
	int		frame_count;
	char	*file_path;
	int		i;

	// Define frames for each direction
	char *frames_up[] = {
		"textures/player/p_up/p_up_00.xpm",
		"textures/player/p_up/p_up_01.xpm",
		"textures/player/p_up/p_up_02.xpm",
		"textures/player/p_up/p_up_03.xpm",
		"textures/player/p_up/p_up_04.xpm",
		"textures/player/p_up/p_up_05.xpm",
		"textures/player/p_up/p_up_06.xpm",
		"textures/player/p_up/p_up_07.xpm",
	};
	char *frames_down[] = {
		"textures/player/p_down/p_down_00.xpm",
		"textures/player/p_down/p_down_01.xpm",
		"textures/player/p_down/p_down_02.xpm",
		"textures/player/p_down/p_down_03.xpm",
		"textures/player/p_down/p_down_04.xpm",
		"textures/player/p_down/p_down_05.xpm",
		"textures/player/p_down/p_down_06.xpm",
		"textures/player/p_down/p_down_07.xpm",
	};
	char *frames_left[] = {
		"textures/player/p_left/xpm/p_left_00.xpm",
		"textures/player/p_left/xpm/p_left_01.xpm",
		"textures/player/p_left/xpm/p_left_02.xpm",
		"textures/player/p_left/xpm/p_left_03.xpm",
		"textures/player/p_left/xpm/p_left_04.xpm",
		"textures/player/p_left/xpm/p_left_05.xpm",
		"textures/player/p_left/xpm/p_left_06.xpm",
		"textures/player/p_left/xpm/p_left_07.xpm",
	};
	char *frames_right[] = {
		"textures/player/p_right/p_right_00.xpm",
		"textures/player/p_right/p_right_01.xpm",
		"textures/player/p_right/p_right_02.xpm",
		"textures/player/p_right/p_right_03.xpm",
		"textures/player/p_right/p_right_04.xpm",
		"textures/player/p_right/p_right_05.xpm",
		"textures/player/p_right/p_right_06.xpm",
		"textures/player/p_right/p_right_07.xpm",
	};
	// Choose frames based on direction
	if (ft_strncmp(direction, "up", ft_strlen("up")) == 0)
	{
		frames = frames_up;
		frame_count = sizeof(frames_up) / sizeof(frames_up[0]);
	}
	else if (ft_strncmp(direction, "down", ft_strlen("down")) == 0)
	{
		frames = frames_down;
		frame_count = sizeof(frames_down) / sizeof(frames_down[0]);
	}
	else if (ft_strncmp(direction, "left", ft_strlen("left")) == 0)
	{
		frames = frames_left;
		frame_count = sizeof(frames_left) / sizeof(frames_left[0]);
	}
	else if (ft_strncmp(direction, "right", ft_strlen("right")) == 0)
	{
		frames = frames_right;
		frame_count = sizeof(frames_right) / sizeof(frames_right[0]);
	}
	else
		return ;
	i = 0;
	int y, x;
	while (i < frame_count)
	{
		x = old_x + (new_x - old_x) * (i + 1) / frame_count;
		y = old_y + (new_y - old_y) * (i + 1) / frame_count;
		file_path = frames[i];
		render_image(game, "textures/bg_64n.xpm", x, y);
		render_image(game, "textures/bg_64n.xpm", old_x, old_y);
		render_image(game, file_path, x, y);
		usleep(game->player->sleep_time);
		i++;
		mlx_put_image_to_window(game->window->mlx, game->window->win,
			game->base_img->img_ptr, 0, 0);
	}
}
