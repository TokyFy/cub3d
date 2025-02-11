/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:08:39 by franaivo          #+#    #+#             */
/*   Updated: 2025/02/10 10:08:40 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <sys/types.h>

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

void	render_floor_ceil(t_cub *cub, uint color_ceil, uint color_floor)
{
	int		screen_x;
	int		screen_y;
	uint	color;
	int waves = 6 * cos(5 * (cub->player->pos_x + cub->player->pos_y));

	screen_x = 0;
	screen_y = 0;
	color = color_ceil;
	while (screen_y < cub->buffer->heigth)
	{
		if (screen_y >= (cub->buffer->heigth / 2 + abs(waves)))
			color = color_floor;
		screen_x = 0;
		while (screen_x < cub->buffer->width)
		{
			put_pixel_img(cub->buffer, screen_x, screen_y, color);
			screen_x++;
		}
		screen_y++;
	}
}

int	render_next_frame(void *ptr)
{
	t_cub		*cub;
	t_2d_vector	zero;

	(void)zero;
	zero.x = 32;
	zero.y = WIN_HEIGTH - (MAP_GRID_SIZE * 6) - 32;
	cub = ptr;
	fill_pixel_img(cub->buffer, 0xFFFFFF);
	render_floor_ceil(cub, cub->ceil_color, cub->floor_color);
	threed_schene(cub);
	minimaps(cub, zero);
	mlx_put_image_to_window(cub->mlx, cub->win, (cub->buffer)->img, 0, 0);
	return (0);
}
