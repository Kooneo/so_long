/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_design.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:33:07 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/18 18:01:06 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_section_16_6(t_game *g, int x, int y)
{
	render_image(g, "textures/env/props/el_4.xpm", x, y);
	render_image(g, "textures/env/props/el_14.xpm", x, y + 45);
	render_image(g, "textures/env/plant/el_14.xpm", x, y + 40);
	render_image(g, "textures/env/plant/el_7.xpm", x, y + 85);
}

void	render_section_18_6(t_game *g, int x, int y)
{
	render_image(g, "textures/env/props/el_1.xpm", x, y + 10);
	render_image(g, "textures/env/plant/el_10.xpm", x, y + 40);
	render_image(g, "textures/env/plant/el_16.xpm", x + 40, y + 40);
}
