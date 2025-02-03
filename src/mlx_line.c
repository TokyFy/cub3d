/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:52:40 by franaivo          #+#    #+#             */
/*   Updated: 2025/02/03 08:52:42 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static void	calculate_line_params(t_2d_vector *start, t_2d_vector *end,
		float *x_increment, float *y_increment)
{
	t_2d_vector	delta;
	int			step_count;

	delta.x = (int)(end->x - start->x);
	delta.y = (int)(end->y - start->y);
	if (abs((int)delta.x) > abs((int)delta.y))
		step_count = abs((int)delta.x);
	else
		step_count = abs((int)delta.y);
	*x_increment = delta.x / (float)step_count;
	*y_increment = delta.y / (float)step_count;
}

void	draw_line(t_mlx_image *buffer, t_2d_vector *from, t_2d_vector *to,
		uint color)
{
	t_2d_vector	current_pos;
	t_2d_vector	step;
	int			step_count;
	int			i;

	calculate_line_params(from, to, &step.x, &step.y);
	current_pos = *from;
	if (abs((int)(to->x - from->x)) > abs((int)(to->y - from->y)))
		step_count = abs((int)(to->x - from->x));
	else
		step_count = abs((int)(to->y - from->y));
	i = 0;
	while (i++ <= step_count)
	{
		put_pixel_img(buffer, current_pos.x, current_pos.y, color);
		current_pos.x += step.x;
		current_pos.y += step.y;
	}
}
