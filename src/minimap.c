/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:39:30 by franaivo          #+#    #+#             */
/*   Updated: 2025/02/10 09:40:12 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <sys/types.h>

void	minimaps_direction(const t_cub *cub, t_2d_vector zero)
{
	t_2d_vector	from;
	t_2d_vector	direction;

	from.x = (cub->player->pos_x - ((int)cub->player->pos_x - 3))
		* MAP_GRID_SIZE;
	from.y = (cub->player->pos_y - ((int)cub->player->pos_y - 3))
		* MAP_GRID_SIZE;
	direction.x = from.x + MAP_GRID_SIZE * cos(cub->player->direction * (M_PI
				/ 180));
	direction.y = from.y + MAP_GRID_SIZE * sin(cub->player->direction * (M_PI
				/ 180));
	translate_2d_vector(&from, &zero);
	translate_2d_vector(&direction, &zero);
	draw_line(cub->buffer, &from, &direction, cub->floor_color);
}

char	get_map_type(int x, int y)
{
	t_cub	*cub;

	cub = static_cub(NULL);
	if (x < 0 || x >= (int)cub->map_width || y < 0 || y >= (int)cub->map_height)
		return (0);
	return (cub->maps[y][x]);
}

void	minimaps(t_cub *cub, t_2d_vector zero)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	draw_square_to_img(MAP_GRID_SIZE * 6, zero.x, zero.y, cub->ceil_color);
	while (j < 6)
	{
		i = 0;
		while (i < 6)
		{
			if (get_map_type((int)cub->player->pos_x - 3 + i,
					(int)cub->player->pos_y - 3 + j) == '1')
				draw_square_to_img(MAP_GRID_SIZE, i * MAP_GRID_SIZE + zero.x, j
					* MAP_GRID_SIZE + zero.y, cub->floor_color);
			i++;
		}
		j++;
	}
	draw_square_to_img(4, (cub->player->pos_x - ((int)cub->player->pos_x - 3))
		* MAP_GRID_SIZE + zero.x - 2, (cub->player->pos_y
			- ((int)cub->player->pos_y - 3)) * MAP_GRID_SIZE + zero.y - 2,
		cub->floor_color);
	minimaps_direction(cub, zero);
}
