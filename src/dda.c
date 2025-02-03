/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:52:20 by franaivo          #+#    #+#             */
/*   Updated: 2025/02/03 08:52:23 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static void	get_vertical_step(double angle, float *step_x, float *step_y)
{
	double	angle_rad;

	angle_rad = angle * (M_PI / 180.0);
	*step_x = 1.0;
	if (angle > 90.0 && angle < 270.0)
		*step_x = -1.0;
	*step_y = *step_x * tan(angle_rad);
}

static void	get_horizontal_step(double angle, float *step_x, float *step_y)
{
	double	angle_rad;

	angle_rad = angle * (M_PI / 180.0);
	*step_y = 1.0;
	if (angle > 180.0)
		*step_y = -1.0;
	*step_x = *step_y / tan(angle_rad);
}

int	check_wall(t_cub *cub, int x, int y)
{
	if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH)
		return (1);
	return (cub->maps[y][x] == '1');
}

void	find_ray_vert_intersec(t_2d_vector *from, t_2d_vector *to, double angle,
		t_cub *cub)
{
	t_2d_vector	intersec;
	t_2d_vector	step;
	int			map_x;

	angle = normalize_angle(angle);
	get_vertical_step(angle, &step.x, &step.y);
	if (step.x < 0)
		intersec.x = floor(from->x / MAP_GRID_SIZE);
	else
		intersec.x = ceil(from->x / MAP_GRID_SIZE);
	intersec.y = from->y / MAP_GRID_SIZE + (intersec.x * MAP_GRID_SIZE
			- from->x) * tan(angle * (M_PI / 180.0)) / MAP_GRID_SIZE;
	while (1)
	{
		if (step.x < 0)
			map_x = (int)intersec.x - 1;
		else
			map_x = (int)intersec.x;
		if (check_wall(cub, map_x, (int)intersec.y))
			break ;
		intersec.x += step.x;
		intersec.y += step.y;
	}
	to->x = intersec.x * MAP_GRID_SIZE;
	to->y = intersec.y * MAP_GRID_SIZE;
}

void	find_ray_horz_intersec(t_2d_vector *from, t_2d_vector *to, double angle,
		t_cub *cub)
{
	t_2d_vector	intersec;
	t_2d_vector	step;
	int			map_y;

	angle = normalize_angle(angle);
	get_horizontal_step(angle, &step.x, &step.y);
	if (step.y < 0)
		intersec.y = floor(from->y / MAP_GRID_SIZE);
	else
		intersec.y = ceil(from->y / MAP_GRID_SIZE);
	intersec.x = from->x / MAP_GRID_SIZE + (intersec.y * MAP_GRID_SIZE
			- from->y) / (tan(angle * (M_PI / 180.0)) * MAP_GRID_SIZE);
	while (1)
	{
		if (step.y < 0)
			map_y = (int)intersec.y - 1;
		else
			map_y = (int)intersec.y;
		if (check_wall(cub, (int)intersec.x, map_y))
			break ;
		intersec.x += step.x;
		intersec.y += step.y;
	}
	to->x = intersec.x * MAP_GRID_SIZE;
	to->y = intersec.y * MAP_GRID_SIZE;
}
