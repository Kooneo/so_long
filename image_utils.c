/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:19:40 by zbakour           #+#    #+#             */
/*   Updated: 2025/01/30 16:36:55 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img	new_img(int w, int h, t_win window)
{
	t_img	image;

	image.win = window;
	image.img_ptr = mlx_new_image(window.mlx, w, h);
	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bits_per_pixel),
			&(image.line_length), &(image.endian));
	image.w = w;
	image.h = h;
	return (image);
}

t_img	new_file_img(char *path, t_win window)
{
	t_img	image;

	image.win = window;
	image.img_ptr = mlx_xpm_file_to_image(window.mlx, path, &image.w, &image.h);
	if (!image.img_ptr)
		write(2, "File could not be read\n", 23);
	else
		image.addr = mlx_get_data_addr(image.img_ptr, &image.bits_per_pixel,
				&image.line_length, &image.endian);
	return (image);
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_length) + (x
				* img.bits_per_pixel / 8))));
}

void	put_img_to_img(t_img dst, t_img src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src.w)
	{
		j = 0;
		while (j < src.h)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}
