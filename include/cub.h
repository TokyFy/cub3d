/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <sravonin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:01:05 by sravonin          #+#    #+#             */
/*   Updated: 2025/01/27 11:32:35 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
#include <sys/types.h>
# include <unistd.h>
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"


#define WIN_WIDTH 1080
#define WIN_HEIGTH 640
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define MAP_GRID_SIZE 8

#define ARROW_UP 65362
#define ARROW_DOWN 65364
#define ARROW_RIGHT 65361
#define ARROW_LEFT 65363


typedef struct s_2d_vector
{
	float	x;
	float	y;
}			t_2d_vector;

typedef struct s_mlx_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			heigth;
	int			width;
}				t_mlx_image;

typedef struct s_player
{
	float pos_x;
	float pos_y;
	float direction;
} t_player;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_mlx_image	*buffer;
	char**		maps;
	t_player*	player;
	t_mlx_image* texture[4];
}				t_cub;

float	vect_dist(t_2d_vector *from, t_2d_vector *to);
float	normalize_angle(float angle);
void translate_2d_vector(t_2d_vector *from , t_2d_vector *to);
void copy_2d_vector(t_2d_vector *from , t_2d_vector *to);

void	put_pixel_img(t_mlx_image *img, unsigned int x, unsigned int y,
		int color);
void	fill_pixel_img(t_mlx_image *img, int color);
void	draw_square_to_img(t_mlx_image *img, uint side, uint x, uint y);
t_cub	*mlx_windows(int width, int height, char *title);

void	draw_line(t_mlx_image *buffer, t_2d_vector *from, t_2d_vector *to, uint color);

void	find_ray_vert_intersec(t_2d_vector *from, t_2d_vector *to, double angle, t_cub *cub);
void	find_ray_horz_intersec(t_2d_vector *from, t_2d_vector *to, double angle, t_cub *cub);

void minimaps_direction(const t_cub *cub , t_2d_vector zero);
void minimaps_player(t_cub *cub , t_2d_vector zero);
void minimaps(t_cub *cub , t_2d_vector zero);
#endif
