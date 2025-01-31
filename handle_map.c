/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:03:57 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/31 20:54:17 by zbakour          ###   ########.fr       */
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
		trimmed_line = ft_strtrim(read_line, "\n");
		if (trimmed_line)
		{
			row_c++;
			free(trimmed_line);
		}
		free(read_line);
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
		return (NULL);
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

static void	render_player(t_game *g, int x, int y)
{
	render_image(g, "textures/player/p_idle/down/idle_down_00.xpm", x, y);
	g->player->x_pos = x;
	g->player->y_pos = y;
	g->map->player_x = x;
	g->map->player_y = y;
}

static bool	is_special_wall(int tx, int ty)
{
	return ((tx == 12 && ty == 5) || (tx == 18 && ty == 4));
}

static bool	is_special_background(int tx, int ty)
{
	return ((tx >= 2 && tx <= 5 && (ty == 4 || ty == 5)) || (tx >= 16
			&& ((ty == 6 && tx <= 18) || (ty == 7 && tx <= 17))) || tx == 20
		|| tx == 12 || tx == 4 || (tx >= 3 && tx <= 4 && ty == 6));
}

static bool	is_special_decor(int tx, int ty)
{
	return ((tx >= 23 && tx <= 27) && (ty == 5 || ty == 6 || ty == 7));
}

static void	handle_special_decor(t_game *g, int tx, int ty, int xy[2])
{
	const int	x = xy[0];
	const int	y = xy[1];

	if (tx == 25 || tx == 27 || tx == 23)
	{
		if (tx == 23 && ty == 7)
		{
			render_el_at(g, 2, x + TILE_SIZE - 15, y - 15);
			render_el_at(g, 1, x + 10, y - 20);
		}
		if (tx == 25 && ty == 6)
			render_el_at(g, 2, x, y - 15);
		render_el_at(g, 10, x, y);
	}
	else
		render_el_at(g, 9, x, y);
}

static void	handle_wall(t_game *g, int tx_ty[4], int xy[2])
{
	const int	tx = tx_ty[0];
	const int	ty = tx_ty[1];
	const int	x = xy[0];
	const int	y = xy[1];

	if (is_special_wall(tx, ty))
		render_image(g, "textures/env/wall_001.xpm", x, y);
	else if (is_special_background(tx, ty))
		render_image(g, "textures/bg_64n.xpm", x, y);
	else if (is_special_decor(tx, ty))
		handle_special_decor(g, tx, ty, xy);
	else
		render_wall(g, tx_ty[2], tx_ty[3], x, y);
}

static void	render_enemies(t_game *g, char c, int x, int y)
{
	if (c == 'T')
		render_image(g, "textures/env/enemy.xpm", x - 3, y - 3);
	else if (c == 'X')
		render_image(g, "textures/env/blue_hand.xpm", x - 3, y - 3);
	else if (c == 'G')
		render_image(g, "textures/env/green_hand.xpm", x - 3, y - 3);
}

static void	render_collectible(t_game *g, int x, int y)
{
	render_image(g, "textures/coins/coin.xpm", x + 10, y);
	g->map->coins_count++;
}

void	process_tile(t_game *g, char c, int x, int y, int i, int j)
{
	const int	tx = x / TILE_SIZE;
	const int	ty = y / TILE_SIZE;
	int	tx_ty[4] = {tx, ty, i, j};

	if (c == '1')
		handle_wall(g, tx_ty, (int [2]){x, y});
	else if (c == 'T' || c == 'X' || c == 'G')
		render_enemies(g, c, x, y);
	else if (c == 'C')
		render_collectible(g, x, y);
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
	int	i;
	int	j;
	int	x;
	int	y;

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

// static void	process_tile(t_game *g, char c, int x, int y, int i, int j)
// {
// 	if (c == '1')
// 	{
// 		if (g->map->is_sp == 1 && ((x / 64 == 12 && y / 64 == 5)
// 				|| (x / 64 == 18 && y / 64 == 4)))
// 			render_image(g, "textures/env/wall_001.xpm", x, y);
// 		else if (g->map->is_sp == 1 &&
// 		(
// 			((x / 64 >= 2 && x / 64 <= 5) && (y / 64 == 4 || y / 64 == 5))
// 			|| ((x / 64 >= 16 && x / 64 <= 18) && y / 64 == 6)
// 			|| ((x / 64 >= 16 && x / 64 <= 17) && y / 64 == 7)
// 			|| (x / 64 == 20 && y / 64 == 5)
// 			|| (x / 64 == 12 && y / 64 == 4)
// 			|| (x / 64 == 4 && y / 64 == 6)
// 			|| ((x / 64 >= 3 && x / 64 <= 4) && y / 64 == 6)
// 		))
// 			render_image(g, "textures/bg_64n.xpm", x, y);
// 		else if ( g->map->is_sp == 1 &&
// 				(	((x / 64 >= 23 && y / 64 == 6) && (x / 64 <= 27 && y
// / 64 == 6))
// 					|| ((x / 64 >= 23 && y / 64 == 7) && (x / 64 <= 27 && y
// / 64 == 7))
// 					|| ((x / 64 >= 23 && y / 64 == 5) && (x / 64 <= 27 && y
// / 64 == 5))
// 				))
// 		{
// 			if ((x / 64 == 25 && y / 64 == 6)
// 				|| ((x / 64 == 27 || x / 64 == 23) && y / 64 == 7)
// 			)
// 			{
// 				if ((x / 64 == 23 && y / 64 == 7))
// 				{
// 					render_el_at(g, 2, x + 64 - 15, y - 15);
// 					render_el_at(g, 1, x + 10, y - 20);
// 				}
// 				if ((x / 64 == 25 && y / 64 == 6))
// 					render_el_at(g, 2, x, y - 15);
// 				render_el_at(g, 10, x, y);
// 			}
// 			else
// 				render_el_at(g, 9, x, y);
// 		}
// 		else
// 			render_wall(g, i, j, x, y);

// 	}
// 	else if (c == 'T' || c == 'X' || c == 'G')
// 	{
// 		if (c == 'T')
// 			render_image(g, "textures/env/enemy.xpm", x - 3, y - 3);
// 		else if (c == 'X')
// 			render_image(g, "textures/env/blue_hand.xpm", x - 3, y - 3);
// 		else
// 			render_image(g, "textures/env/green_hand.xpm", x - 3, y - 3);
// 	}
// 	else if (c == 'C')
// 	{
// 		render_image(g, "textures/coins/coin.xpm", x + 10, y);
// 		g->map->coins_count++;
// 	}
// 	else if (c == 'P')
// 		render_player(g, x, y);
// 	else if (c == 'E')
// 	{
// 		g->map->exit_x = x;
// 		g->map->exit_y = y;
// 	}
// }
