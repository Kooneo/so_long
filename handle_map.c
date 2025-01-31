/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:03:57 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/31 20:31:46 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

size_t	map_row_c(char *filepath)
{
	size_t	row_c;
	char	*read_line;
	char	*trimmed_line;
	int		fd;

	fd = open(filepath, O_RDWR);
	if (fd < 0)
		return (0);
	read_line = get_next_line(fd);
	if (!read_line)
	{
		show_err("Invalid Map.");
		exit(-1);
	}
	row_c = 0;
	while (read_line)
	{
		trimmed_line = ft_strtrim(read_line, "\n"); // Store the trimmed result
		if (trimmed_line)
		// If the result is not NULL (non-empty line)
		{
			row_c++;
			free(trimmed_line); // Free the trimmed string
		}
		free(read_line); // Free the original read_line (after using it)
		read_line = get_next_line(fd);
	}
	close(fd);
	return (row_c);
}

char	**load_map(t_map *map_data)
{
	char	*read_line;
	size_t	row_c;
	char	*trimed_line;
	char	**map;
	int		fd;

	map = malloc(sizeof(char *) * map_row_c(map_data->filepath) * 100);
	if (!map)
		return (NULL);
	fd = open(map_data->filepath, O_RDWR);
	if (fd < 0)
		return (NULL);
	read_line = get_next_line(fd);
	if (!read_line)
	{
		return (NULL);
	}
	trimed_line = ft_strtrim(read_line, "\n");
	row_c = 0;
	while (read_line)
	{
		map[row_c++] = ft_strtrim(read_line, "\n");
		free(read_line);
		read_line = get_next_line(fd);
	}
	map_data->x = ft_strlen(trimed_line);
	map_data->y = row_c;
	map_data->size = map_data->y * map_data->x;
	map[row_c] = NULL;
	free(trimed_line);
	close(fd);
	return (map);
}

void	render_wall(t_game *game, int i, int j, int x, int y)
{
	if (j > 0 && ((game->map->ptr[i][j - 1] == '0' || game->map->ptr[i][j
				- 1] == 'P' || game->map->ptr[i][j - 1] == 'C'
				|| game->map->ptr[i][j - 1] == 'E' || game->map->ptr[i][j
				- 1] == 'X' || game->map->ptr[i][j - 1] == 'G'))
		&& game->map->ptr[i][j + 1] == '1')
		render_image(game, "textures/xf_end.xpm", x, y);
	else if (!game->map->ptr[i + 1])
		render_image(game, "textures/wall_b.xpm", x, y);
	else if (game->map->ptr[i][j + 1] == '\0' || j == 0)
		render_image(game, "textures/wall_m.xpm", x, y);
	else if (i == 0)
		render_image(game, "textures/wall_b.xpm", x, y);
	else if (j > 0 && game->map->ptr[i][j - 1] == '1' && game->map->ptr[i][j
		+ 1] == '1')
		render_image(game, "textures/x_m_m.xpm", x, y);
	else if (j > 0 && game->map->ptr[i][j - 1] == '1' && (game->map->ptr[i][j
			+ 1] == '0' || game->map->ptr[i][j + 1] == 'P'
			|| game->map->ptr[i][j + 1] == 'C' || game->map->ptr[i][j
			+ 1] == 'E' || game->map->ptr[i][j + 1] == 'G'
			|| game->map->ptr[i][j + 1] == 'X'))
		render_image(game, "textures/xe_end.xpm", x, y);
	else
		render_image(game, "textures/mid_wall.xpm", x, y);
}

void	render_el_at(t_game *game, int el, int x, int y)
{
	if (el == 1)
		render_image(game, "textures/env/el_1.xpm", x, y + 64 - 15);
	else if (el == 2)
		render_image(game, "textures/env/el_2.xpm", x, y + 64 - 15);
	else if (el == 3)
		render_image(game, "textures/env/el_3.xpm", x + 64 - 20, y + 64 - 15);
	else if (el == 9)
		render_image(game, "textures/env/el_9.xpm", x + 20, y);
	else if (el == 10)
		render_image(game, "textures/env/el_10.xpm", x + 25, y - 5);
	else if (el == 13)
		render_image(game, "textures/env/plant/el_1.xpm", x + 20, y - 80);
	else if (el == 14)
		render_image(game, "textures/env/plant/el_2.xpm", x + 20, y - 80);
	else if (el == 15)
		render_image(game, "textures/env/plant/el_3.xpm", x + 20, y - 80);
}

// void render_skipwall(t_game *game)
// {
	
// }

// void	render_env()
// {
	
// }
static void	render_player(t_game *g, int x, int y)
{
	render_image(g, "textures/player/p_idle/down/idle_down_00.xpm", x, y);
	g->player->x_pos = x;
	g->player->y_pos = y;
	g->map->player_x = x;
	g->map->player_y = y;
}

static void	process_tile(t_game *g, char c, int x, int y, int i, int j)
{
	if (c == '1')
	{
		if (g->map->is_sp == 1 && ((x / 64 == 12 && y / 64 == 5)
				|| (x / 64 == 18 && y / 64 == 4)))
			render_image(g, "textures/env/wall_001.xpm", x, y);
		else if (g->map->is_sp == 1 && 
		(	
			((x / 64 >= 2 && x / 64 <= 5) && (y / 64 == 4 || y / 64 == 5))
			|| ((x / 64 >= 16 && x / 64 <= 18) && y / 64 == 6) 
			|| ((x / 64 >= 16 && x / 64 <= 17) && y / 64 == 7) 
			|| (x / 64 == 20 && y / 64 == 5)
			|| (x / 64 == 12 && y / 64 == 4) 
			|| (x / 64 == 4 && y / 64 == 6) 
			|| ((x / 64 >= 3 && x / 64 <= 4) && y / 64 == 6)
		))
			render_image(g, "textures/bg_64n.xpm", x, y);
		else if ( g->map->is_sp == 1 && 
				(	((x / 64 >= 23 && y / 64 == 6) && (x / 64 <= 27 && y / 64 == 6))
					|| ((x / 64 >= 23 && y / 64 == 7) && (x / 64 <= 27 && y / 64 == 7)) 
					|| ((x / 64 >= 23 && y / 64 == 5) && (x / 64 <= 27 && y / 64 == 5))
				))
		{
			if ((x / 64 == 25 && y / 64 == 6) 
				|| ((x / 64 == 27 || x / 64 == 23) && y / 64 == 7)
			)
			{
				if ((x / 64 == 23 && y / 64 == 7))
				{
					render_el_at(g, 2, x + 64 - 15, y - 15);
					render_el_at(g, 1, x + 10, y - 20);
				}
				if ((x / 64 == 25 && y / 64 == 6))
					render_el_at(g, 2, x, y - 15);
				render_el_at(g, 10, x, y);
			}
			else
				render_el_at(g, 9, x, y);
		}
		else
			render_wall(g, i, j, x, y);
			
	}
	else if (c == 'T' || c == 'X' || c == 'G')
	{
		if (c == 'T')
			render_image(g, "textures/env/enemy.xpm", x - 3, y - 3);
		else if (c == 'X')
			render_image(g, "textures/env/blue_hand.xpm", x - 3, y - 3);
		else
			render_image(g, "textures/env/green_hand.xpm", x - 3, y - 3);
	}
	else if (c == 'C')
	{
		render_image(g, "textures/coins/coin.xpm", x + 10, y);
		g->map->coins_count++;
	}
	else if (c == 'P')
		render_player(g, x, y);
	else if (c == 'E')
	{
		g->map->exit_x = x;
		g->map->exit_y = y;
	}
}

void	map_render(t_game *g)
{
	int		i;
	int		j;
	int		x;
	int		y;
	
	i = -1;
	y = 0;
	render_ground(g, "textures/bg_64n.xpm");
	g->map->is_sp = (ft_strcmp(g->map->filepath, "maps/map3.ber") == 0);
	while (++i < g->map->y && g->map->ptr[i])
	{
		x = 0;
		j = -1;
		while (g->map->ptr[i][++j])
		{
			if (!ft_isalnum(g->map->ptr[i][j]))
				return ;
			process_tile(g, g->map->ptr[i][j], x, y, i, j);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	render_map_design(g);
}

// void	render_map_design(t_game *game)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;
// 	char c;
// 	if (game->map->is_sp == 1)
// 	{
// 		i = 0;
// 		y = 0;
// 		while (i < game->map->y && game->map->ptr[i])
// 		{
// 			x = 0;
// 			j = 0;
// 			while (game->map->ptr[i][j])
// 			{
// 				c = game->map->ptr[i][j];
// 				if (c == '1')
// 				{

// 					if ((x / 64 == 8 && y / 64 == 7) || (x / 64 == 12 && y / 64 == 2))
// 						render_el_at(game, 2, x, y);
// 					if ((x / 64 == 16 && y / 64 == 2) || (x / 64 == 21 && y / 64 == 4))
// 						render_el_at(game, 3, x, y);
// 					if ((x / 64 == 25 && y / 64 == 7) || (x / 64 == 23 && y / 64 == 6))
// 					{
// 						if ((x / 64 == 23 && y / 64 == 6))
// 							render_el_at(game, 14, x, y + 25);
// 						else
// 							render_el_at(game, 13, x, y);
// 					}
// 					if ((x / 64 == 18 && y / 64 == 3))
// 						render_el_at(game, 15, x - 12, y + 32);
// 					if ((x / 64 == 3 && y / 64 == 4))
// 						render_image(game, "textures/env/big_obj_1.xpm", x + 25,
// 							y);
// 					if ((x / 64 == 17 && y / 64 == 6))
// 						render_image(game, "textures/env/props/el_2.xpm", x, y);
// 					if ((x / 64 == 16 && y / 64 == 6))
// 					{
// 						render_image(game, "textures/env/props/el_4.xpm", x, y);
// 						render_image(game, "textures/env/props/el_14.xpm", x, y
// 							+ 45);
// 						render_image(game, "textures/env/plant/el_14.xpm", x, y
// 							+ 40);
// 						render_image(game, "textures/env/plant/el_7.xpm", x, y
// 							+ 85);
// 					}
// 					if ((x / 64 == 18 && y / 64 == 6))
// 					{
// 						render_image(game, "textures/env/props/el_1.xpm", x, y
// 							+ 10);
// 						render_image(game, "textures/env/plant/el_10.xpm", x, y
// 							+ 40);
// 						render_image(game, "textures/env/plant/el_16.xpm", x
// 							+ 40, y + 40);
// 					}
// 					if ((x / 64 == 17 && y / 64 == 7))
// 						render_image(game, "textures/env/props/el_12.xpm", x
// 							- 15, y + 25);
// 					if ((x / 64 == 20 && y / 64 == 5))
// 					{
// 						render_image(game, "textures/env/props/el_15.xpm", x,
// 							y);
// 						render_image(game, "textures/env/props/el_9.xpm", x
// 							+ 38, y + 23);
// 					}
// 					if ((x / 64 == 12 && y / 64 == 4))
// 					{
// 						render_image(game, "textures/env/el_5.xpm", x, y);
// 						render_image(game, "textures/env/el_2.xpm", x, y + 55);
// 						render_image(game, "textures/env/el_3.xpm", x + 10, y
// 							+ 40);
// 						render_image(game, "textures/env/el_4.xpm", x + 35, y
// 							+ 55);
// 					}
// 					if (x / 64 == 4 && y / 64 == 6)
// 						render_image(game, "textures/env/obj_3.xpm", x, y - 10);
// 					if (x / 64 == 2 && y / 64 == 4)
// 					{
// 						render_image(game, "textures/env/obj_2.xpm", x, y + 5);
// 						render_image(game, "textures/env/object_21.xpm", x + 74, y + 10);
// 						render_image(game, "textures/env/object_22.xpm", x, y + 40);
// 					}
// 					if (x / 64 == 3 && y / 64 == 6)
// 						render_image(game, "textures/env/object_25.xpm", x, y + 10);
// 				}
// 				x += 64;
// 				j++;
// 			}
// 			y += 64;
// 			i++;
// 		}
// 	}
// }
