/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:40:35 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 14:32:06 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_win
{
	int			width;
	int			hight;
	void		*mlx;
	void		*win;
}				t_win;

typedef struct s_map
{
	char		**ptr;
	int			x;
	int			y;
	int			size;
	char		*filepath;
	int			coins_count;
	int			player_x;
	int			player_y;
	int			exit_x;
	int			exit_y;
	int			enemy_count;
	int			is_valid;
	int			is_sp;
	int			wall_count;
}				t_map;

typedef struct s_player
{
	int			x_pos;
	size_t		y_pos;
	int			moves_count;
	int			hp;
	int			sleep_time;
	int			items_collected;
}				t_player;

typedef struct s_img
{
	t_win		win;
	void		*img_ptr;
	char		*addr;
	int			h;
	int			w;
	int			x;
	int			y;
	int			bits_per_pixel;
	int			endian;
	int			line_length;
}				t_img;

typedef struct s_game
{
	t_win		*window;
	t_map		*map;
	t_player	*player;
	t_img		*base_img;
	int			key_states[1000000];
}				t_game;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

# define TILE_SIZE 64

// Map_utils.c
void			render_ground(t_game *game, char *filepath);

// utils.c
void			show_err(char *err);
void			render_image(t_game *game, char *file_path, int x, int y);
void			destroy_image(t_img img);
int				exit_game(t_game *game);
char			*ft_strjoin_free(char *s1, char const *s2);

// image_utils.c
t_win			new_window(int w, int h, char *str);
t_img			new_img(int w, int h, t_win window);
void			put_pixel_img(t_img img, int x, int y, int color);
t_img			new_file_img(char *path, t_win window);
void			put_img_to_img(t_img dst, t_img src, int x, int y);

// movement.c
int				is_move_valid(t_game *game, int new_x, int new_y);
int				handle_player_movement(t_game *game);

// keys_manage.c
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			int_keystate(t_game *game);

//  animation.c
void			animate_player(t_game *game, int old_x, int old_y, int new_x,
					int new_y, char *direction);

// handle_map.c
void			free_map(char **map);
char			**load_map(t_map *map_data);
size_t			map_row_c(char *filepath);
int				check_is_rectangular(t_map *map);
int				check_psec_dup(t_map *map_data);
void			map_render(t_game *game);

void			fill(char **map, t_point size, t_point current, char to_fill);
char			**make_new_map(t_map *map);
void			flood_fill(char **map, t_point size, int x, int y);
int				map_check(t_map *map);

int				is_coin(t_game *game, int new_x, int new_y);
int				is_the_curse(t_game *game, int new_x, int new_y);
int				is_the_curse_remover(t_game *game, int new_x, int new_y);
int				is_exit_and_valid(t_game *game, int new_x, int new_y);

// game_init.c
void			init_window(t_win *window, int map_y, int map_x);
// void			init_game(t_game *game);
// t_player		*init_player(t_player *player);
void			map_init(t_map *map, char *filepath);
#endif