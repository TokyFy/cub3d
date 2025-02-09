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
#include <X11/Xlib.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void* static_cub(void * ptr)
{
    static void* cub;
    if(cub == NULL)
    {
        cub = ptr;
        return NULL;
    }
    return cub;
}

float fract_part(float n)
{
	return n - floor(n);
}

unsigned int	get_pixel_img(t_mlx_image* img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->line_length) + (x
				* img->bits_per_pixel / 8))));
}

void draw_line_textured(t_2d_vector *start , t_2d_vector* end , float offset , t_mlx_image* texture )
{
    t_cub *cub = static_cub(NULL);
	uint x = (int)(texture->width * offset) % texture->width;
	uint line_height = vect_dist(start, end);
	uint y;
	uint i = 0;

	while(i <= line_height)
	{
		y = (uint)(texture->heigth * ((float)i / (float)line_height));
		put_pixel_img(cub->buffer, start->x , start->y + i, get_pixel_img(texture, x , y));
		i++;
	}
}

void    init_ray_vert_draw(int nth , t_2d_vector* from , t_2d_vector *to , t_2d_vector *line[2])
{
    t_cub *cub = static_cub(NULL);
   	double		ray_angle;
	double		perp_dist;
	float		line_height;

   	ray_angle = (cub->player->direction - 30) + (nth * ((float)60 / WIN_WIDTH));
	perp_dist = vect_dist(from, to) * cos(M_PI / 180 * (cub->player->direction
				- ray_angle));
	line_height = MAP_GRID_SIZE / perp_dist * (((float)WIN_WIDTH / 2)
			/ tan((M_PI / 3) / 2));
	line[0]->x = nth;
	line[0]->y = ((float)WIN_HEIGTH / 2) - (line_height / 2);
	line[1]->x = nth;
	line[1]->y = line[0]->y + line_height;
}

void	ray_vert_draw(t_cub *cub, int nth, t_2d_vector *from, t_2d_vector *to)
{
	t_2d_vector	start;
	t_2d_vector	end;
	static t_2d_vector* face;
	t_2d_vector* line[2];

	line[0] = &start;
	line[1] = &end;
	init_ray_vert_draw(nth, from , to, line);
	if(!face)
		face = to;
	if(to == face)
	{
		if(cub->maps[(int)floor(to->y / MAP_GRID_SIZE)][(int)floor(to->x / MAP_GRID_SIZE)] == '1')
			draw_line_textured(&start, &end, 1 - fract_part(to->x / MAP_GRID_SIZE) , cub->texture[0]);
		else
			draw_line_textured(&start, &end, fract_part(to->x / MAP_GRID_SIZE) , cub->texture[1]);
	}
	else
	{
		if(cub->maps[(int)floor(to->y / MAP_GRID_SIZE)][(int)floor(to->x / MAP_GRID_SIZE)] == '1')
			draw_line_textured(&start, &end,  fract_part(to->y / MAP_GRID_SIZE) , cub->texture[2]);
		else
			draw_line_textured(&start, &end, 1 - fract_part(to->y / MAP_GRID_SIZE) , cub->texture[3]);
	}
}

void	threed_schene(t_cub *cub)
{
	t_2d_vector	from;
	t_2d_vector	to_horz;
	t_2d_vector	to_vert;
	double		a;
	int			i;

	from.x = cub->player->pos_x * MAP_GRID_SIZE;
	from.y = cub->player->pos_y * MAP_GRID_SIZE;
	a = (int)cub->player->direction - 30;
	i = 0;
	while (a < (int)cub->player->direction + 30)
	{
		find_ray_horz_intersec(&from, &to_horz, a, cub);
		find_ray_vert_intersec(&from, &to_vert, a, cub);
		if (vect_dist(&from, &to_horz) < vect_dist(&from, &to_vert))
			ray_vert_draw(cub, i, &from, &to_horz);
		else
			ray_vert_draw(cub, i, &from, &to_vert);
		a += (float)60 / WIN_WIDTH;
		i++;
	}
}

void render_floor(t_cub* cub) {
    uint screen_y = WIN_HEIGTH / 2;  // Commence au milieu de l'écran
    uint screen_x;

    // Conversion de l'angle du joueur en radians
    float player_dir_rad = cub->player->direction * (M_PI / 180.0);
    float dirX = cos(player_dir_rad);
    float dirY = sin(player_dir_rad);

    // Plan de la caméra (perpendiculaire à la direction du joueur)
    float planeX = -dirY;
    float planeY = dirX;

    while (screen_y < WIN_HEIGTH) {
        float rowDistance = (float)MAP_GRID_SIZE / ((screen_y - WIN_HEIGTH / 2) / (float)WIN_HEIGTH);

        screen_x = 0;
        while (screen_x < WIN_WIDTH) {
            // Calcul de la direction du rayon
            float rayDirX = dirX + planeX * (screen_x / (float)WIN_WIDTH - 1);
            float rayDirY = dirY + planeY * (screen_x / (float)WIN_WIDTH - 1);

            // Coordonnées du monde projetées correctement
            float worldX = (cub->player->pos_x * MAP_GRID_SIZE) + rowDistance * rayDirX;
            float worldY = (cub->player->pos_y * MAP_GRID_SIZE) + rowDistance * rayDirY;

            // Coordonnées de la grille

            // Fraction des coordonnées pour détecter les lignes de la grille
            float fracX = fmod(worldX, MAP_GRID_SIZE) / MAP_GRID_SIZE;
            float fracY = fmod(worldY, MAP_GRID_SIZE) / MAP_GRID_SIZE;

            uint color;

            // Affichage des lignes de la grille
            if ((fracX < 0.02f || fracX > 0.98f) || (fracY < 0.02f || fracY > 0.98f)) {
                color = 0x000000;  // Noir pour les lignes de la grille
            } else {
                color = 0x404040;  // Gris foncé pour le sol
            }

            put_pixel_img(cub->buffer, screen_x, screen_y, color);
            screen_x++;
        }
        screen_y++;
    }
}
void render_floor_ceil(t_cub* cub , uint color_ceil , uint color_floor)
{
    int screen_x = 0;
    int screen_y = 0;
    uint color = color_ceil;

    while(screen_y < cub->buffer->heigth)
    {
        if(screen_y >= (cub->buffer->heigth / 2))
            color = color_floor;
        screen_x = 0;
        while(screen_x < cub->buffer->width)
        {
            put_pixel_img(cub->buffer, screen_x, screen_y, color);
            screen_x++;
        }
        screen_y++;
    }
}


int	render_next_frame(void *ptr)
{
	t_cub		*cub;
	t_2d_vector	zero;

	(void)zero;
	zero.x = MAP_GRID_SIZE;
	zero.y = MAP_GRID_SIZE * 4 * 12;
	cub = ptr;
	fill_pixel_img(cub->buffer, 0xFFFFFF);
	render_floor(cub);
	// render_floor_ceil(cub , 0x979578 , 0x3E3936);
	// threed_schene(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, (cub->buffer)->img, 0, 0);
	return (0);
}

int	on_key_press(int code, void *ptr)
{
	t_cub	*cub;

	cub = ptr;
	if (code == ARROW_UP)
	{
		cub->player->pos_x += 0.1 * cos(cub->player->direction * (M_PI / 180));
		cub->player->pos_y += 0.1 * sin(cub->player->direction * (M_PI / 180));
	}
	else if (code == ARROW_DOWN)
	{
		cub->player->pos_x -= 0.1 * cos(cub->player->direction * (M_PI / 180));
		cub->player->pos_y -= 0.1 * sin(cub->player->direction * (M_PI / 180));
	}
	else if (code == ARROW_LEFT)
	{
		cub->player->direction += 3;
		if (cub->player->direction > 360)
			cub->player->direction = 0;
	}
	else if (code == ARROW_RIGHT)
	{
		if (cub->player->direction <= 0)
			cub->player->direction = 360;
		else
			cub->player->direction -= 3;
	}
	return (1);
}

t_mlx_image* load_texture(t_cub* cub , char *path)
{
    t_mlx_image *texture_n = malloc(sizeof(t_mlx_image));
	texture_n->img = mlx_xpm_file_to_image(cub->mlx, path, &texture_n->width, &texture_n->heigth);
	texture_n->addr = mlx_get_data_addr(texture_n->img , &texture_n->bits_per_pixel, &texture_n->line_length, &texture_n->endian);
    return texture_n;
}

int	main(void)
{
	t_cub		*cub;
	t_mlx_image	*buffer;
	int			i;
	int			j;

	cub = mlx_windows(WIN_WIDTH, WIN_HEIGTH, "cub3D");
	if (!cub)
		return (1);
	char maps[MAP_HEIGHT][MAP_WIDTH] = {
		{'1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '1', '1'},
		{'1', '1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '0', '0', '0', '0', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1'},
	};
	buffer = ft_calloc(sizeof(t_mlx_image), 1);
	buffer->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGTH);
	buffer->width = WIN_WIDTH;
	buffer->heigth = WIN_HEIGTH;
	buffer->addr = mlx_get_data_addr(buffer->img, &buffer->bits_per_pixel,
			&buffer->line_length, &buffer->endian);
	cub->buffer = buffer;
	cub->maps = ft_calloc(sizeof(char *), MAP_HEIGHT);
	cub->player = ft_calloc(sizeof(t_player), 1);
	cub->player->pos_x = 3.5;
	cub->player->pos_y = 3.5;
	cub->player->direction = 270;
	i = 0;
	j = 0;
	while (j < MAP_HEIGHT)
	{
		i = 0;
		cub->maps[j] = ft_calloc(sizeof(char), MAP_WIDTH);
		while (i < MAP_WIDTH)
		{
			cub->maps[j][i] = maps[j][i];
			i++;
		}
		j++;
	}
	static_cub(cub);
	cub->texture[0] = load_texture(cub ,"./textures/texture_26.xpm");
	cub->texture[1] = load_texture(cub ,"./textures/texture_27.xpm");
	cub->texture[2] = load_texture(cub ,"./textures/texture_23.xpm");
	cub->texture[3] = load_texture(cub ,"./textures/texture_22.xpm");

	mlx_hook(cub->win, 02, 1L << 0, on_key_press, cub);
	mlx_loop_hook(cub->mlx, render_next_frame, cub);
	mlx_loop(cub->mlx);
	free(cub);
	return (0);
}
