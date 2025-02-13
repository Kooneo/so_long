/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:40:35 by zbakour           #+#    #+#             */
/*   Updated: 2025/02/13 19:00:17 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdbool.h>
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
	size_t 		y_pos;
	int			moves_count;
	int			hp;
	int			sleep_time;
	int			items_collected;
}				t_player;

// typedef struct s_enemy
// {
// 	int			x_pos;
// 	int			y_pos;
// 	int			sleep_time;
// }				t_enemy;

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


typedef struct s_enemy
{
    int x;
    int y;
    int direction; // 1 for right/down, -1 for left/up
} t_enemy;

typedef struct s_game
{
	t_win		*window;
	t_map		*map;
	t_player	*player;
	t_img		*base_img;
	int			key_states[1000000];
	t_enemy     	*enemies;
}				t_game;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct t_paramholder
{
	int			i;
	int			j;
	int			x;
	int			y;
}				t_paramholder;

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
void				key_press(int keycode, t_game *game);
void				key_release(int keycode, t_game *game);
void			int_keystate(t_game *game);

//  animation.c
void			animate_player(t_game *game,
					t_paramholder params, char *direction);

// handle_map.c
void			free_map(char **map);
char			**load_map(t_map *map_data);
size_t			map_row_c(char *filepath);
int				check_is_rectangular(t_map *map);
int				check_psec_dup(t_map *map_data);
void			map_render(t_game *game);

void			fill(char **map, t_point size, t_point current);
char			**make_new_map(t_map *map);
void			flood_fill(char **map, t_point size, int x, int y);
int				map_check(t_map *map);

int				is_coin(t_game *game, int new_x, int new_y);
int				is_the_curse(t_game *game, int new_x, int new_y);
int				is_the_curse_remover(t_game *game, int new_x, int new_y);
int				is_exit_and_valid(t_game *game, int new_x, int new_y);

// game_init.c
void			init_window(t_win *window, int map_y, int map_x);
void			map_init(t_map *map, char *filepath);
void			init_game(t_game *game, t_map *map, t_win *window,
					t_player *player);
void			setup_hooks(t_win *window, t_game *game);
int				check_wall(char *wall);
int				check_is_surrounded(char *row);
void			render_map_design(t_game *game);

void			render_el_at(t_game *game, int el, int x, int y);
void			render_section_16_6(t_game *g, int x, int y);
void			render_section_18_6(t_game *g, int x, int y);

// counter.c
void			render_digit(t_game *game, int digit, int x, int y);
void			render_movement_count(t_game *game);

// game_utils_2.c
void			handle_special_cases(t_game *g,
					int new_x, int new_y, char *dir);
void			handle_collectibles(t_game *g, int new_x, int new_y);

void			render_others(t_game *g, int c, int x, int y);
void			render_wall(t_game *game, t_paramholder p);
void			render_player(t_game *g, int x, int y);

char			**get_frames_up(void);
char			**get_frames_down(void);
char			**get_frames_left(void);
char			**get_frames_right(void);
char			**get_frames(char *direction);

void		move_enemy(t_game *game, t_enemy *enemy);
void		move_enemy_vertical(t_game *game, t_enemy *enemy);
int			update_game(t_game *game);
#endif
