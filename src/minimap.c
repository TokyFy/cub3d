#include <cub.h>

void minimaps_direction(const t_cub *cub , t_2d_vector zero)
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
	// minimaps_player(cub, zero);
	minimaps_direction(cub, zero);
}
