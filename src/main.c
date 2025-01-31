/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <sravonin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:57:24 by sravonin          #+#    #+#             */
/*   Updated: 2025/01/27 08:48:31 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#define WIN_WIDTH 1080
#define  WIN_HEIGTH 640
#define MAP_WIDTH 16
#define MAP_HEIGHT 16
#define MAP_GRID_SIZE 16

#define ARROW_UP 65362
#define ARROW_DOWN 65364
#define ARROW_RIGHT 65361
#define ARROW_LEFT 65363

void	put_pixel_img(t_mlx_image *img, unsigned int x, unsigned int y,
		int color)
{
	char	*dst;

	if ((unsigned int)color == 0xFF000000)
		return ;
	if (x > (unsigned int)img->width || y > (unsigned int)img->heigth)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fill_pixel_img(t_mlx_image *img, int color)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < img->heigth)
	{
		x = 0;
		while (x < img->width)
		{
			put_pixel_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

void draw_square_to_img(t_mlx_image *img , uint side ,uint x , uint y)
{
	uint i = x;
	uint j = y;

	uint color = 0x5A52A3;
	if(side < MAP_GRID_SIZE)
		color = 0x000022;

	while (j < y + side) {
		i = x;
		while(i < x + side)
		{
			put_pixel_img(img, i , j , color);
			i++;
		}
		j++;
	}
}

t_cub	*mlx_windows(int width, int height, char *title)
{
	t_cub	*cub;
	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		free(cub);
		return (NULL);
	}
	cub->win = mlx_new_window(cub->mlx, width, height, title);
	if (!cub->win)
	{
		free(cub);
		return (NULL);
	}
	return (cub);
}

typedef struct s_2d_vector
{
	double x;
	double y;
} t_2d_vector;

void draw_line(t_mlx_image *buffer , t_2d_vector *from, t_2d_vector *to) {
    int dx = to->x - from->x;
    int dy = to->y - from->y;

    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    float x = from->x;
    float y = from->y;
    int i = 0;
    while (i <= steps) {
    	put_pixel_img(buffer, x, y, 0x000000);
        x += x_inc;
        y += y_inc;
        i++;
    }
}

void find_ray_vert_intersec(t_2d_vector *from, t_2d_vector *to, double angle, t_cub *cub)
{
    double ix;
    double iy;
    double step_x = 1.0;
    double step_y;

    // Normalize angle to 0-360 range
    angle = fmod(angle, 360.0);
    if (angle < 0) angle += 360.0;

    // Convert angle to radians
    double angle_rad = angle * (M_PI / 180.0);

    // Determine direction and initial intersection
    if (angle > 90.0 && angle < 270.0) {
        step_x = -1.0;
        ix = floor(from->x / MAP_GRID_SIZE);
    } else {
        ix = ceil(from->x / MAP_GRID_SIZE);
    }

    // Calculate step_y using proper trigonometry
    step_y = step_x * tan(angle_rad);

    // Calculate initial y-intersection
    iy = from->y / MAP_GRID_SIZE + (ix * MAP_GRID_SIZE - from->x) * tan(angle_rad) / MAP_GRID_SIZE;

    // Ray casting loop
    while (iy >= 0 && iy < MAP_HEIGHT && ix >= 0 && ix < MAP_WIDTH) {
        int map_x = (int)(step_x < 0 ? ix - 1 : ix);
        int map_y = (int)iy;

        // Bounds checking
        if (map_y < 0 || map_y >= MAP_HEIGHT || map_x < 0 || map_x >= MAP_WIDTH)
            break;

        // Check for wall collision
        if (cub->maps[map_y][map_x] == '1')
            break;

        // Move to next intersection
        ix += step_x;
        iy += step_y;
    }

    // Store intersection point
    to->x = ix * MAP_GRID_SIZE;
    to->y = iy * MAP_GRID_SIZE;
}

void find_ray_horz_intersec(t_2d_vector *from, t_2d_vector *to, double angle, t_cub *cub)
{
    double iy;
    double ix;
    double step_y = 1.0;
    double step_x;

    angle = fmod(angle, 360.0);
    if (angle < 0) angle += 360.0;
    double angle_rad = angle * (M_PI / 180.0);
    if (angle > 180.0) {
        step_y = -1.0;
        iy = floor(from->y / MAP_GRID_SIZE);
    } else {
        iy = ceil(from->y / MAP_GRID_SIZE);
    }
    step_x = step_y / tan(angle_rad);
    ix = from->x / MAP_GRID_SIZE + (iy * MAP_GRID_SIZE - from->y) / (tan(angle_rad) * MAP_GRID_SIZE);
    while (iy >= 0 && iy < MAP_HEIGHT && ix >= 0 && ix < MAP_WIDTH) {
        int map_y = (int)(step_y < 0 ? iy - 1 : iy);
        int map_x = (int)ix;
        if (map_y < 0 || map_y >= MAP_HEIGHT || map_x < 0 || map_x >= MAP_WIDTH)
            break;
        if (cub->maps[map_y][map_x] == '1')
            break;
        iy += step_y;
        ix += step_x;
    }
    to->x = ix * MAP_GRID_SIZE;
    to->y = iy * MAP_GRID_SIZE;
}

double vect_dist(t_2d_vector *from, t_2d_vector *to)
{
    double dx = to->x - from->x;
    double dy = to->y - from->y;
    return sqrt(dx * dx + dy * dy);
}


int render_next_frame(void *ptr)
{
	t_cub *cub = ptr;
	fill_pixel_img(cub->buffer, 0xF6F2FF);
	int i = 0;
	int j = 0;
	while(j < MAP_HEIGHT)
	{
		i = 0;
		while(i < MAP_WIDTH)
		{
			if(cub->maps[j][i] == '1')
			{
				draw_square_to_img(cub->buffer, MAP_GRID_SIZE, i * MAP_GRID_SIZE , j * MAP_GRID_SIZE);
			}
			i++;
		}
		j++;
	}
	draw_square_to_img(cub->buffer, 6,
	cub->player->pos_x * MAP_GRID_SIZE - 3,
	cub->player->pos_y * MAP_GRID_SIZE - 3);
	t_2d_vector from;
	t_2d_vector direction;
	from.x = cub->player->pos_x * MAP_GRID_SIZE;
	from.y = cub->player->pos_y * MAP_GRID_SIZE;
	direction.x = from.x + 6 * cos(cub->player->direction * (M_PI / 180));
	direction.y = from.y + 6 * sin(cub->player->direction * (M_PI / 180));
	draw_line(cub->buffer, &from, &direction);

	t_2d_vector to_horz;
	t_2d_vector to_vert;
	double a = (int)cub->player->direction - 30;

	while(a < (int)cub->player->direction + 30)
	{
		find_ray_horz_intersec(&from, &to_horz, a , cub);
		find_ray_vert_intersec(&from, &to_vert, a , cub);

		if(vect_dist(&from, &to_horz) < vect_dist(&from, &to_vert))
			draw_line(cub->buffer, &from, &to_horz);
		else
			draw_line(cub->buffer, &from, &to_vert);
		a += .1;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, (cub->buffer)->img , 0, 0);
	return 0;
}

int on_key_press(int code , void* ptr)
{
	t_cub* cub = ptr;
	if(code == ARROW_UP)
	{
		cub->player->pos_x += 0.2 * cos(cub->player->direction * (M_PI / 180));
		cub->player->pos_y += 0.2 * sin(cub->player->direction * (M_PI / 180));
	}
	else if (code == ARROW_DOWN)
	{
		cub->player->pos_x -= 0.2 * cos(cub->player->direction * (M_PI / 180));
		cub->player->pos_y -= 0.2 * sin(cub->player->direction * (M_PI / 180));
	}
	else if (code == ARROW_LEFT)
	{
		cub->player->direction += 2;
		if(cub->player->direction > 360)
			cub->player->direction = 0;
	}
	else if (code == ARROW_RIGHT)
	{
		if(cub->player->direction <= 0)
			cub->player->direction = 360;
		else
			cub->player->direction -= 2;
	}
	return 1;
}


int	main(void)
{
	t_cub	*cub;

	cub = mlx_windows(WIN_WIDTH, WIN_HEIGTH, "cub3D");
	if (!cub)
		return (1);

	char maps[MAP_HEIGHT][MAP_WIDTH] = {
		{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
		{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
		{'1','0','0','0','1','1','1','0','1','0','0','0','0','0','0','1'},
		{'1','0','0','0','0','0','1','1','1','0','0','0','0','0','0','1'},
		{'1','0','0','0','0','0','1','1','1','0','0','0','0','0','0','1'},
		{'1','0','0','1','0','0','1','0','0','0','0','0','0','0','0','1'},
		{'1','0','0','1','0','0','1','0','0','0','0','0','0','0','0','1'},
		{'1','0','0','1','1','0','1','1','0','0','0','0','0','0','0','1'},
		{'1','0','0','1','1','0','1','0','0','0','0','0','0','0','0','1'},
		{'1','0','0','1','0','0','1','0','0','0','0','0','1','0','0','1'},
		{'1','0','0','1','0','0','1','0','0','0','0','0','0','0','0','1'},
		{'1','0','0','0','0','0','0','0','0','0','0','1','0','0','0','1'},
		{'1','0','0','0','0','0','0','0','1','0','1','0','0','0','0','1'},
		{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
		{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
	};

	t_mlx_image *buffer = ft_calloc(sizeof(t_mlx_image), 1);
	buffer->img = mlx_new_image(cub->mlx, WIN_WIDTH , WIN_HEIGTH);
	buffer->width = WIN_WIDTH;
	buffer->heigth = WIN_HEIGTH;
	buffer->addr = mlx_get_data_addr(buffer->img, &buffer->bits_per_pixel, &buffer->line_length, &buffer->endian);
	cub->buffer = buffer;

	cub->maps = ft_calloc( sizeof(char*) , MAP_HEIGHT);
	cub->player = ft_calloc(sizeof(t_player), 1);
	cub->player->pos_x = 6;
	cub->player->pos_y = 6;
	cub->player->direction = 90;
	int i = 0;
	int j = 0;

	while(j < MAP_HEIGHT)
	{
		i = 0;
		cub->maps[j] = ft_calloc(sizeof(char), MAP_WIDTH);
		while(i < MAP_WIDTH)
		{
			cub->maps[j][i] = maps[j][i];
			i++;
		}
		j++;
	}

	mlx_hook(cub->win, 02, 1L << 0, on_key_press , cub);
	mlx_loop_hook(cub->mlx, render_next_frame , cub);
	mlx_loop(cub->mlx);
	free(cub);
	return (0);
}
