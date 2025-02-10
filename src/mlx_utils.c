/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:01:20 by franaivo          #+#    #+#             */
/*   Updated: 2025/02/10 09:42:19 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	put_pixel_img(t_mlx_image *img, unsigned int x, unsigned int y,
		int color)
{
	char	*dst;

	if ((unsigned int)color == 0xFF000000)
		return ;
	if (x > (unsigned int)img->width || y > (unsigned int)img->heigth)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fill_pixel_img(t_mlx_image *img, int color)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < img->heigth)
	{
		x = 0;
		while (x < img->width)
		{
			put_pixel_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_square_to_img(t_mlx_image *img, uint side, uint x, uint y)
{
	uint	i;
	uint	j;
	uint	color;

	i = x;
	j = y;
	color = 0x5A52A3;
	if (side < MAP_GRID_SIZE)
		color = 0xFFFFFF;
	while (j < y + side)
	{
		i = x;
		while (i < x + side)
		{
			put_pixel_img(img, i, j, color);
			i++;
		}
		j++;
	}
}

t_cub	*mlx_windows(int width, int height, char *title)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		free(cub);
		return (NULL);
	}
	cub->win = mlx_new_window(cub->mlx, width, height, title);
	if (!cub->win)
	{
		free(cub);
		return (NULL);
	}
	return (cub);
}

unsigned int	get_pixel_img(t_mlx_image *img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->line_length) + (x
				* img->bits_per_pixel / 8))));
}
