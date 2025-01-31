/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:03:57 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/31 17:13:36 by zbakour          ###   ########.fr       */
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

size_t	map_row_count(char *filepath)
{
	int		fd;
	char	*line;
	char	*trimmed;
	size_t	row_count;

	fd = open(filepath, O_RDWR);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
	{
		show_err("Invalid Map.");
		exit(-1);
	}
	row_count = 0;
	while (line)
	{
		trimmed = ft_strtrim(line, "\n");
		if (trimmed)
		{
			row_count++;
			free(trimmed);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (row_count);
}

char	**load_map(t_map *map_data)
{
	int		fd;
	char	*line;
	char	**map;
	size_t	row;

	map = malloc(sizeof(char *) * map_row_count(map_data->filepath) * 100);
	if (!map)
		return (NULL);
	fd = open(map_data->filepath, O_RDWR);
	if (fd < 0)
		return (free_map(map), NULL);
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		map[row++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
	}
	map_data->x = ft_strlen(map[0]);
	map_data->y = row;
	map_data->size = map_data->y * map_data->x;
	map[row] = NULL;
	close(fd);
	return (map);
}

static void	render_tile_content(t_game *g, char c, int x, int y)
{
	if (c == 'C')
	{
		render_image(g, "textures/coins/coin.xpm", x + 10, y);
		g->map->coins_count++;
	}
	else if (c == 'P')
	{
		render_image(g, "textures/player/p_idle/down/idle_down_00.xpm", x, y);
		g->player->x_pos = x;
		g->player->y_pos = y;
	}
	else if (c == 'E')
	{
		g->map->exit_x = x;
		g->map->exit_y = y;
	}
	else if (c == 'T')
		render_image(g, "textures/env/enemy.xpm", x - 3, y - 3);
	else if (c == 'X')
		render_image(g, "textures/env/blue_hand.xpm", x - 3, y - 3);
	else if (c == 'G')
		render_image(g, "textures/env/green_hand.xpm", x - 3, y - 3);
}

static void	render_wall_texture(t_game *g, int i, int j)
{
	const int	x = j * TILE_SIZE;
	const int	y = i * TILE_SIZE;

	if (j > 0 && ft_strchr("0PCEXG", g->map->ptr[i][j - 1]) && g->map->ptr[i][j
		+ 1] == '1')
		render_image(g, "textures/xf_end.xpm", x, y);
	else if (!g->map->ptr[i + 1])
		render_image(g, "textures/wall_b.xpm", x, y);
	else if (!g->map->ptr[i][j + 1] || j == 0)
		render_image(g, "textures/wall_m.xpm", x, y);
	else if (i == 0)
		render_image(g, "textures/wall_b.xpm", x, y);
	else if (j > 0 && g->map->ptr[i][j - 1] == '1' && g->map->ptr[i][j
		+ 1] == '1')
		render_image(g, "textures/x_m_m.xpm", x, y);
	else if (g->map->ptr[i][j + 1] && ft_strchr("0PCEGX", g->map->ptr[i][j
			+ 1]))
		render_image(g, "textures/xe_end.xpm", x, y);
	else
		render_image(g, "textures/mid_wall.xpm", x, y);
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

void	map_render(t_game *g)
{
	int	i;
	int	j;
	int	x;
	int	y;

	render_ground(g, "textures/bg_64n.xpm");
	g->map->is_sp = !ft_strncmp(g->map->filepath, "maps/map3.ber",
			ft_strlen("maps/map3.ber"));
	i = -1;
	y = 0;
	while (++i < g->map->y)
	{
		j = -1;
		x = 0;
		while (g->map->ptr[i][++j])
		{
			if (g->map->ptr[i][j] == '1')
				render_wall_texture(g, i, j);
			else
				render_tile_content(g, g->map->ptr[i][j], x, y);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	if (g->map->is_sp)
		render_map_design(g);
}

void	render_map_design(t_game *game)
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	c;

	if (game->map->is_sp == 1)
	{
		i = 0;
		y = 0;
		while (i < game->map->y && game->map->ptr[i])
		{
			x = 0;
			j = 0;
			while (game->map->ptr[i][j])
			{
				c = game->map->ptr[i][j];
				if (c == '1')
				{
					if ((x / 64 == 25 && y / 64 == 7) || (x / 64 == 23 && y
							/ 64 == 6))
					{
						if ((x / 64 == 23 && y / 64 == 6))
							render_el_at(game, 14, x, y + 25);
						else
							render_el_at(game, 13, x, y);
					}
					if ((x / 64 == 18 && y / 64 == 3))
						render_el_at(game, 15, x - 12, y + 32);
					if ((x / 64 == 3 && y / 64 == 4))
						render_image(game, "textures/env/big_obj_1.xpm", x + 25,
							y);
					if ((x / 64 == 17 && y / 64 == 6))
						render_image(game, "textures/env/props/el_2.xpm", x, y);
					if ((x / 64 == 16 && y / 64 == 6))
					{
						render_image(game, "textures/env/props/el_4.xpm", x, y);
						render_image(game, "textures/env/props/el_14.xpm", x, y
							+ 45);
						render_image(game, "textures/env/plant/el_14.xpm", x, y
							+ 40);
						render_image(game, "textures/env/plant/el_7.xpm", x, y
							+ 85);
					}
					if ((x / 64 == 18 && y / 64 == 6))
					{
						render_image(game, "textures/env/props/el_1.xpm", x, y
							+ 10);
						render_image(game, "textures/env/plant/el_10.xpm", x, y
							+ 40);
						render_image(game, "textures/env/plant/el_16.xpm", x
							+ 40, y + 40);
					}
					if ((x / 64 == 17 && y / 64 == 7))
						render_image(game, "textures/env/props/el_12.xpm", x
							- 15, y + 25);
					if ((x / 64 == 20 && y / 64 == 5))
					{
						render_image(game, "textures/env/props/el_15.xpm", x,
							y);
						render_image(game, "textures/env/props/el_9.xpm", x
							+ 38, y + 23);
					}
					if ((x / 64 == 12 && y / 64 == 4))
					{
						render_image(game, "textures/env/el_5.xpm", x, y);
						render_image(game, "textures/env/el_2.xpm", x, y + 55);
						render_image(game, "textures/env/el_3.xpm", x + 10, y
							+ 40);
						render_image(game, "textures/env/el_4.xpm", x + 35, y
							+ 55);
					}
					if (x / 64 == 4 && y / 64 == 6)
						render_image(game, "textures/env/obj_3.xpm", x, y - 10);
					if (x / 64 == 2 && y / 64 == 4)
					{
						render_image(game, "textures/env/obj_2.xpm", x, y + 5);
						render_image(game, "textures/env/object_21.xpm", x + 74,
							y + 10);
						render_image(game, "textures/env/object_22.xpm", x, y
							+ 40);
					}
					if (x / 64 == 3 && y / 64 == 6)
						render_image(game, "textures/env/object_25.xpm", x, y
							+ 10);
				}
				x += 64;
				j++;
			}
			y += 64;
			i++;
		}
	}
}
