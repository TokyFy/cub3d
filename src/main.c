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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void translate_2d_vector(t_2d_vector *from , t_2d_vector *to)
{
	from->x += to->x;
	from->y += to->y;
}

void copy_2d_vector(t_2d_vector *from , t_2d_vector *to)
{
	to->x = from->x;
	to->y = from->y;
}
void minimaps_direction(t_cub *cub , t_2d_vector zero)
{
	t_2d_vector	from;
	t_2d_vector	direction;
	from.x = cub->player->pos_x * MAP_GRID_SIZE;
	from.y = cub->player->pos_y * MAP_GRID_SIZE;
	direction.x = from.x + 2 * MAP_GRID_SIZE * cos(cub->player->direction * (M_PI / 180));
	direction.y = from.y + 2 * MAP_GRID_SIZE * sin(cub->player->direction * (M_PI / 180));
	translate_2d_vector(&from, &zero);
	translate_2d_vector(&direction, &zero);
	draw_line(cub->buffer, &from, &direction, 0x000000);
}

void minimaps_player(t_cub *cub , t_2d_vector zero)
{
	t_2d_vector	from;
	t_2d_vector	to_horz;
	t_2d_vector	to_vert;
	double		a;
	t_2d_vector temp;

	from.x = cub->player->pos_x * MAP_GRID_SIZE;
	from.y = cub->player->pos_y * MAP_GRID_SIZE;
	a = (int)cub->player->direction - 45;
	copy_2d_vector(&from, &temp);
	translate_2d_vector(&temp, &zero);
	while (a < (int)cub->player->direction + 45)
	{
		find_ray_horz_intersec(&from, &to_horz, a, cub);
		find_ray_vert_intersec(&from, &to_vert, a, cub);
		if (vect_dist(&from, &to_horz) < vect_dist(&from, &to_vert))
		{
			translate_2d_vector(&to_horz, &zero);
			draw_line(cub->buffer, &temp, &to_horz, 0xB4ADEA);
		}
		else
		{
			translate_2d_vector(&to_vert, &zero);
			draw_line(cub->buffer, &temp, &to_vert, 0x5C4DD1);
		}
		a += .05;
	}
}


void ray_vert_draw(t_cub *cub , int nth , t_2d_vector *from , t_2d_vector *to)
{
	t_2d_vector start;
	t_2d_vector end;
	double ray_angle = (cub->player->direction - 30) + (nth * ((float)60 / WIN_WIDTH));
	double perp_dist = vect_dist(from, to) * cos(M_PI/180 * (cub->player->direction - ray_angle));
	float line_height = MAP_GRID_SIZE / perp_dist * (((float)WIN_WIDTH / 2) / tan((M_PI / 3)  / 2));

	start.x = nth;
	start.y = ((float)WIN_HEIGTH / 2) - (line_height / 2);
	end.x = nth;
	end.y = start.y + line_height;


	draw_line(cub->buffer, &start, &end, 0x5C4DD1);
}

void threed_schene(t_cub *cub)
{
	t_2d_vector	from;
	t_2d_vector	to_horz;
	t_2d_vector	to_vert;
	double		a;
	int i;

	from.x = cub->player->pos_x * MAP_GRID_SIZE;
	from.y = cub->player->pos_y * MAP_GRID_SIZE;
	a = (int)cub->player->direction - 30;
	i = 0;
	while (a < (int)cub->player->direction + 30)
	{
		find_ray_horz_intersec(&from, &to_horz, a, cub);
		find_ray_vert_intersec(&from, &to_vert, a, cub);
		if (vect_dist(&from, &to_horz) < vect_dist(&from, &to_vert))
		{
			ray_vert_draw(cub, i, &from, &to_horz);
		}
		else
		{
			ray_vert_draw(cub, i, &from, &to_vert);
		}
		a += (float)60 / WIN_WIDTH;
		i++;
	}
}

void minimaps(t_cub *cub , t_2d_vector zero)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < MAP_HEIGHT)
	{
		i = 0;
		while (i < MAP_WIDTH)
		{
			if (cub->maps[j][i] == '1')
				draw_square_to_img(cub->buffer, MAP_GRID_SIZE, i
					* MAP_GRID_SIZE + zero.x, j * MAP_GRID_SIZE + zero.y);
			i++;
		}
		j++;
	}
	minimaps_player(cub, zero);
	minimaps_direction(cub, zero);
}

int	render_next_frame(void *ptr)
{
	t_cub		*cub;
	t_2d_vector zero;
	zero.x = MAP_GRID_SIZE;
	zero.y = MAP_GRID_SIZE * 4 * 12;
	cub = ptr;
	fill_pixel_img(cub->buffer, 0xF6F2FF);
	threed_schene(cub);
	minimaps(cub, zero);
	mlx_put_image_to_window(cub->mlx, cub->win, (cub->buffer)->img, 0, 0);
	return (0);
}

int	on_key_press(int code, void *ptr)
{
	t_cub	*cub;

	cub = ptr;
	if (code == ARROW_UP)
	{
		cub->player->pos_x += 0.2 * cos(cub->player->direction * (M_PI / 180));
		cub->player->pos_y += 0.2 * sin(cub->player->direction * (M_PI / 180));
	}
	else if (code == ARROW_DOWN)
	{
		cub->player->pos_x -= 0.2 * cos(cub->player->direction * (M_PI / 180));
		cub->player->pos_y -= 0.2 * sin(cub->player->direction * (M_PI / 180));
	}
	else if (code == ARROW_LEFT)
	{
		cub->player->direction += 2;
		if (cub->player->direction > 360)
			cub->player->direction = 0;
	}
	else if (code == ARROW_RIGHT)
	{
		if (cub->player->direction <= 0)
			cub->player->direction = 360;
		else
			cub->player->direction -= 2;
	}

	printf("%f\n" , cub->player->direction);
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
	char maps[MAP_HEIGHT][MAP_WIDTH] =
	{
		{'1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
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
	cub->maps = ft_calloc(sizeof(char *), MAP_HEIGHT);
	cub->player = ft_calloc(sizeof(t_player), 1);
	cub->player->pos_x = 1.5;
	cub->player->pos_y = 2.5;
	cub->player->direction = 0;
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
