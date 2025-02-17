/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:42:46 by franaivo          #+#    #+#             */
/*   Updated: 2025/02/10 09:42:47 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <math.h>
#include <stdio.h>

void	set_player_position(float dx, float dy)
{
	t_cub	*cub;

	cub = static_cub(NULL);
	if (!((int)dx < (int)cub->map_width && (int)dy < (int)cub->map_height))
		return ;
	if (cub->maps[(int)(cub->player->pos_y)][(int)(dx)] != '1')
	{
		cub->player->pos_x = dx;
	}
	if (cub->maps[(int)(dy)][(int)(cub->player->pos_x)] != '1')
	{
		cub->player->pos_y = dy;
	}
}

void	parallel_move(int code, t_cub *cub)
{
	float	dx;
	float	dy;

	dx = cub->player->pos_x;
	dy = cub->player->pos_y;
	if (!(code == KEY_S || code == KEY_W || code == ARROW_UP
			|| code == ARROW_DOWN))
		return ;
	if (code == KEY_W || code == ARROW_UP)
	{
		dx += 0.15 * cos(cub->player->direction * (M_PI / 180));
		dy += 0.15 * sin(cub->player->direction * (M_PI / 180));
	}
	else if (code == KEY_S || code == ARROW_DOWN)
	{
		dx -= 0.15 * cos(cub->player->direction * (M_PI / 180));
		dy -= 0.15 * sin(cub->player->direction * (M_PI / 180));
	}
	set_player_position(dx, dy);
}

void	perpedicular_move(int code, t_cub *cub)
{
	float	dx;
	float	dy;

	dx = cub->player->pos_x;
	dy = cub->player->pos_y;
	if (!(code == KEY_A || code == KEY_D))
		return ;
	if (code == KEY_A)
	{
		dx += 0.15 * cos(cub->player->direction * (M_PI / 180) - M_PI / 2);
		dy += 0.15 * sin(cub->player->direction * (M_PI / 180) - M_PI / 2);
	}
	else if (code == KEY_D)
	{
		dx += 0.15 * cos(cub->player->direction * (M_PI / 180) + M_PI / 2);
		dy += 0.15 * sin(cub->player->direction * (M_PI / 180) + M_PI / 2);
	}
	set_player_position(dx, dy);
}

void	move_player(int code, void *ptr)
{
	t_cub	*cub;

	cub = ptr;
	parallel_move(code, cub);
	perpedicular_move(code, cub);
	return ;
}

void	rotate_player(int code, t_cub *cub)
{
	if (!(code == ARROW_LEFT || code == ARROW_RIGHT))
		return ;
	if (code == ARROW_LEFT)
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
}
