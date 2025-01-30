/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:39:10 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 13:39:13 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	show_err(char *err)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err, 2);
	exit(1);
}

void	render_image(t_game *game, char *file_path, int x, int y)
{
	t_img	tile;

	tile = new_file_img(file_path, *(game->window));
	if (!tile.img_ptr)
		return ;
	put_img_to_img(*(game->base_img), tile, x, y);
	destroy_image(tile);
}

void	destroy_image(t_img img)
{
	if (img.img_ptr && img.win.mlx)
	{
		mlx_destroy_image(img.win.mlx, img.img_ptr);
		img.img_ptr = NULL;
	}
}

int	exit_game(t_game *game)
{
	int	i;

	if (game->map && game->map->ptr)
	{
		i = 0;
		while (game->map->ptr[i])
		{
			free(game->map->ptr[i]);
			i++;
		}
		free(game->map->ptr);
	}
	if (game->base_img)
		mlx_destroy_image(game->window->mlx, game->base_img->img_ptr);
	if (game->window && game->window->win)
		mlx_destroy_window(game->window->mlx, game->window->win);
	mlx_destroy_display(game->window->mlx);
	free(game->window->mlx);
	exit(0);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*string;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	if (s1 != NULL)
		len_s1 = ft_strlen(s1);
	if (s2 != NULL)
		len_s2 = ft_strlen(s2);
	string = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!string)
		return (NULL);
	if (s1)
		ft_strlcpy(string, s1, len_s1 + 1);
	else
		string[0] = '\0';
	if (s2)
		ft_strlcat(string, s2, len_s1 + len_s2 + 1);
	free(s1);
	return (string);
}
