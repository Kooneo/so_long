/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:07:02 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/11 16:25:49 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**get_frames_up(void)
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

	return (frames_up);
}

char	**get_frames_down(void)
{
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

	return (frames_down);
}

char	**get_frames_left(void)
{
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

	return (frames_left);
}

char	**get_frames_right(void)
{
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

	return (frames_right);
}
