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
# include <math.h>
#include <sys/types.h>
# include <unistd.h>
# include "mlx.h"
# include "libft.h"


#define WIN_WIDTH 1080
#define WIN_HEIGTH 640
#define MAP_WIDTH 16
#define MAP_HEIGHT 16
#define MAP_GRID_SIZE 16

#define ARROW_UP 65362
#define ARROW_DOWN 65364
#define ARROW_RIGHT 65361
#define ARROW_LEFT 65363
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100


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
unsigned int	get_pixel_img(t_mlx_image* img, int x, int y);
void	draw_square_to_img(uint side, uint x, uint y , uint color);
t_cub	*mlx_windows(int width, int height, char *title);

void	draw_line(t_mlx_image *buffer, t_2d_vector *from, t_2d_vector *to, uint color);

void	find_ray_vert_intersec(t_2d_vector *from, t_2d_vector *to, double angle, t_cub *cub);
void	find_ray_horz_intersec(t_2d_vector *from, t_2d_vector *to, double angle, t_cub *cub);

void minimaps_direction(const t_cub *cub , t_2d_vector zero);
void minimaps_player(t_cub *cub , t_2d_vector zero);
void minimaps(t_cub *cub , t_2d_vector zero);

void* static_cub(void * ptr);

float fract_part(float n);

void set_player_position(float dx , float dy);
void parallel_move(int code , t_cub * cub);
void perpedicular_move(int code , t_cub * cub);
void move_player(int code , void *ptr);
void rotate_player(int code , t_cub *cub);

void	threed_schene(t_cub *cub);
void render_floor_ceil(t_cub* cub , uint color_ceil , uint color_floor);
int	render_next_frame(void *ptr);
t_mlx_image* load_texture(t_cub* cub , char *path);
int	on_key_press(int code, void *ptr);

void	ray_vert_draw(t_cub *cub, int nth, t_2d_vector *from, t_2d_vector *to);
#endif
