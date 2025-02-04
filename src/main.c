/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <sravonin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:57:24 by sravonin          #+#    #+#             */
/*   Updated: 2025/01/27 08:48:31 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


float fract_part(float n)
{
	return n - floor(n);
}

unsigned int	get_pixel_img(t_mlx_image img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_length) + (x
				* img.bits_per_pixel / 8))));
}

void draw_line_textured(t_cub *cub , t_2d_vector *start , t_2d_vector* end , float offset)
{
	uint x = (int)(cub->texture_01->width * offset) % cub->texture_01->width;
	uint line_height = vect_dist(start, end);
	uint y;
	uint i = 0;

	while(i <= line_height)
	{
		y = (uint)(cub->texture_01->heigth * ((float)i / (float)line_height));
		put_pixel_img(cub->buffer, start->x , start->y + i, get_pixel_img(*cub->texture_01, x , y));
		i++;
	}
}

void	ray_vert_draw(t_cub *cub, int nth, t_2d_vector *from, t_2d_vector *to)
{
	t_2d_vector	start;
	t_2d_vector	end;
	double		ray_angle;
	double		perp_dist;
	float		line_height;

	ray_angle = (cub->player->direction - 30) + (nth * ((float)60 / WIN_WIDTH));
	perp_dist = vect_dist(from, to) * cos(M_PI / 180 * (cub->player->direction
				- ray_angle));
	line_height = MAP_GRID_SIZE / perp_dist * (((float)WIN_WIDTH / 2)
			/ tan((M_PI / 3) / 2));
	start.x = nth;
	start.y = ((float)WIN_HEIGTH / 2) - (line_height / 2);
	end.x = nth;
	end.y = start.y + line_height;
	static t_2d_vector* face;

	if(!face)
		face = to;

	if(to == face)
	{
		if(cub->maps[(int)floor(to->y / MAP_GRID_SIZE)][(int)floor(to->x / MAP_GRID_SIZE)] == '1')
			draw_line_textured(cub, &start, &end, 1 - fract_part(to->x / MAP_GRID_SIZE));
		else
			draw_line_textured(cub, &start, &end, fract_part(to->x / MAP_GRID_SIZE));
	}
	else
	{
		if(cub->maps[(int)floor(to->y / MAP_GRID_SIZE)][(int)floor(to->x / MAP_GRID_SIZE)] == '1')
			draw_line_textured(cub, &start, &end,  fract_part(to->y / MAP_GRID_SIZE));
		else
			draw_line_textured(cub, &start, &end, 1 - fract_part(to->y / MAP_GRID_SIZE));
	}
}

void	threed_schene(t_cub *cub)
{
	t_2d_vector	from;
	t_2d_vector	to_horz;
	t_2d_vector	to_vert;
	double		a;
	int			i;

	from.x = cub->player->pos_x * MAP_GRID_SIZE;
	from.y = cub->player->pos_y * MAP_GRID_SIZE;
	a = (int)cub->player->direction - 30;
	i = 0;
	while (a < (int)cub->player->direction + 30)
	{
		find_ray_horz_intersec(&from, &to_horz, a, cub);
		find_ray_vert_intersec(&from, &to_vert, a, cub);
		if (vect_dist(&from, &to_horz) < vect_dist(&from, &to_vert))
			ray_vert_draw(cub, i, &from, &to_horz);
		else
			ray_vert_draw(cub, i, &from, &to_vert);
		a += (float)60 / WIN_WIDTH;
		i++;
	}
}

int	render_next_frame(void *ptr)
{
	t_cub		*cub;
	t_2d_vector	zero;

	(void)zero;
	zero.x = MAP_GRID_SIZE;
	zero.y = MAP_GRID_SIZE * 4 * 12;
	cub = ptr;
	fill_pixel_img(cub->buffer, 0x141616);
	threed_schene(cub);
	//minimaps(cub, zero);
	mlx_put_image_to_window(cub->mlx, cub->win, (cub->buffer)->img, 0, 0);
	return (0);
}

int	on_key_press(int code, void *ptr)
{
	t_cub	*cub;

	cub = ptr;
	if (code == ARROW_UP)
	{
		cub->player->pos_x += 0.1 * cos(cub->player->direction * (M_PI / 180));
		cub->player->pos_y += 0.1 * sin(cub->player->direction * (M_PI / 180));
	}
	else if (code == ARROW_DOWN)
	{
		cub->player->pos_x -= 0.1 * cos(cub->player->direction * (M_PI / 180));
		cub->player->pos_y -= 0.1 * sin(cub->player->direction * (M_PI / 180));
	}
	else if (code == ARROW_LEFT)
	{
		cub->player->direction += 3;
		if (cub->player->direction > 360)
			cub->player->direction = 0;
	}
	else if (code == ARROW_RIGHT)
	{
		if (cub->player->direction <= 0)
			cub->player->direction = 360;
		else
			cub->player->direction -= 3;
	}
	return (1);
}

int	main(void)
{
	t_cub		*cub;
	t_mlx_image	*buffer;
	int			i;
	int			j;

	cub = mlx_windows(WIN_WIDTH, WIN_HEIGTH, "cub3D");
	if (!cub)
		return (1);
	char maps[MAP_HEIGHT][MAP_WIDTH] = {
		{'1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '1', '1'},
		{'1', '1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '0', '0', '0', '0', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1'},
	};
	buffer = ft_calloc(sizeof(t_mlx_image), 1);
	buffer->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGTH);
	buffer->width = WIN_WIDTH;
	buffer->heigth = WIN_HEIGTH;
	buffer->addr = mlx_get_data_addr(buffer->img, &buffer->bits_per_pixel,
			&buffer->line_length, &buffer->endian);
	cub->buffer = buffer;

	t_mlx_image *texture_n = malloc(sizeof(t_mlx_image));
	texture_n->img = mlx_xpm_file_to_image(cub->mlx, "./textures/texture_09.xpm", &texture_n->width, &texture_n->heigth);
	texture_n->addr = mlx_get_data_addr(texture_n->img , &texture_n->bits_per_pixel, &texture_n->line_length, &texture_n->endian);
	cub->texture_01 = texture_n;

	cub->maps = ft_calloc(sizeof(char *), MAP_HEIGHT);
	cub->player = ft_calloc(sizeof(t_player), 1);
	cub->player->pos_x = 3.5;
	cub->player->pos_y = 3.5;
	cub->player->direction = 270;
	i = 0;
	j = 0;
	while (j < MAP_HEIGHT)
	{
		i = 0;
		cub->maps[j] = ft_calloc(sizeof(char), MAP_WIDTH);
		while (i < MAP_WIDTH)
		{
			cub->maps[j][i] = maps[j][i];
			i++;
		}
		j++;
	}
	mlx_hook(cub->win, 02, 1L << 0, on_key_press, cub);
	mlx_loop_hook(cub->mlx, render_next_frame, cub);
	mlx_loop(cub->mlx);
	free(cub);
	return (0);
}
