/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:39:14 by franaivo          #+#    #+#             */
/*   Updated: 2025/02/10 09:39:17 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	on_key_press(int code, void *ptr)
{
	t_cub	*cub;

	cub = ptr;
	if (code <= KEY_W)
	{
		move_player(code, ptr);
		return (1);
	}
	if (code == ARROW_RIGHT || code == ARROW_LEFT)
	{
		rotate_player(code, cub);
		return (1);
	}
	return (1);
}
