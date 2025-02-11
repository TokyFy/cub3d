/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:43:01 by franaivo          #+#    #+#             */
/*   Updated: 2025/02/10 09:43:02 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

void	draw_line_textured(t_2d_vector *start, t_2d_vector *end, float offset,
		t_mlx_image *texture)
{
	t_cub	*cub;
	uint	x;
	uint	line_height;
	uint	y;
	uint	i;

	cub = static_cub(NULL);
	x = (int)(texture->width * offset) % texture->width;
	line_height = vect_dist(start, end);
	i = 0;
	while (i <= line_height)
	{
		y = (uint)(texture->heigth * ((float)i / (float)line_height));
		put_pixel_img(cub->buffer, start->x, start->y + i,
			get_pixel_img(texture, x, y));
		i++;
	}
}

void	init_ray_vert_draw(int nth, t_2d_vector *from, t_2d_vector *to,
		t_2d_vector *line[2])
{
	t_cub	*cub;
	double	ray_angle;
	double	perp_dist;
	float	line_height;
	int		waves;

	cub = static_cub(NULL);
	waves = 6 * cos(5 * (cub->player->pos_x + cub->player->pos_y));
	ray_angle = (cub->player->direction - 30) + (nth * ((float)60 / WIN_WIDTH));
	perp_dist = vect_dist(from, to) * cos(M_PI / 180 * (cub->player->direction
				- ray_angle));
	line_height = MAP_GRID_SIZE / perp_dist * (((float)WIN_WIDTH / 2)
			/ tan((M_PI / 3) / 2));
	line[0]->x = nth;
	line[0]->y = ((float)WIN_HEIGTH / 2) - (line_height / 2) + waves;
	line[1]->x = nth;
	line[1]->y = line[0]->y + line_height;
}

void	ray_vert_north_south(t_2d_vector *start, t_2d_vector *end,
		t_2d_vector *to)
{
	t_cub	*cub;

	cub = static_cub(NULL);
	if (cub->maps[(int)floor(to->y / MAP_GRID_SIZE)][(int)floor(to->x
			/ MAP_GRID_SIZE)] == '1')
		draw_line_textured(start, end, 1 - fract_part(to->x / MAP_GRID_SIZE),
			cub->texture[0]);
	else
		draw_line_textured(start, end, fract_part(to->x / MAP_GRID_SIZE),
			cub->texture[1]);
}

void	ray_vert_east_west(t_2d_vector *start, t_2d_vector *end,
		t_2d_vector *to)
{
	t_cub	*cub;

	cub = static_cub(NULL);
	if (cub->maps[(int)floor(to->y / MAP_GRID_SIZE)][(int)floor(to->x
			/ MAP_GRID_SIZE)] == '1')
		draw_line_textured(start, end, fract_part(to->y / MAP_GRID_SIZE),
			cub->texture[2]);
	else
		draw_line_textured(start, end, 1 - fract_part(to->y / MAP_GRID_SIZE),
			cub->texture[3]);
}

void	ray_vert_draw(t_cub *cub, int nth, t_2d_vector *from, t_2d_vector *to)
{
	t_2d_vector	start;
	t_2d_vector	end;
	t_2d_vector	*line[2];

	line[0] = &start;
	line[1] = &end;
	(void)(cub);
	init_ray_vert_draw(abs(nth), from, to, line);
	if (nth <= 0)
	{
		ray_vert_north_south(&start, &end, to);
	}
	else
	{
		ray_vert_east_west(&start, &end, to);
	}
}
