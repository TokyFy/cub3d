/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:53:04 by franaivo          #+#    #+#             */
/*   Updated: 2025/02/03 08:53:06 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <math.h>

float	vect_dist(t_2d_vector *from, t_2d_vector *to)
{
	float	dx;
	float	dy;

	dx = to->x - from->x;
	dy = to->y - from->y;
	return (sqrt(fabs(dx * dx + dy * dy)));
}

float	normalize_angle(float angle)
{
	angle = fmod(angle, 360.0);
	if (angle < 0)
		angle += 360.0;
	return (angle);
}
