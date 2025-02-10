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

void	minimaps_direction(const t_cub *cub, t_2d_vector zero)
{
	t_2d_vector	from;
	t_2d_vector	direction;

	from.x = cub->player->pos_x * MAP_GRID_SIZE;
	from.y = cub->player->pos_y * MAP_GRID_SIZE;
	direction.x = from.x + 2 * MAP_GRID_SIZE * cos(cub->player->direction
			* (M_PI / 180));
	direction.y = from.y + 2 * MAP_GRID_SIZE * sin(cub->player->direction
			* (M_PI / 180));
	translate_2d_vector(&from, &zero);
	translate_2d_vector(&direction, &zero);
	draw_line(cub->buffer, &from, &direction, 0x000000);
}

void	minimaps(t_cub *cub, t_2d_vector zero)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < MAP_HEIGHT)
	{
		i = 0;
		while (i < MAP_WIDTH)
		{
			if (cub->maps[j][i] == '1')
				draw_square_to_img(cub->buffer, MAP_GRID_SIZE, i * MAP_GRID_SIZE
					+ zero.x, j * MAP_GRID_SIZE + zero.y);
			i++;
		}
		j++;
	}
	minimaps_direction(cub, zero);
}
