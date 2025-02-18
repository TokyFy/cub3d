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

int	main(void)
{
	t_cub		*cub;
	t_mlx_image	*buffer;
	uint			i;
	uint			j;

	cub = mlx_windows(WIN_WIDTH, WIN_HEIGTH, "cub3D");
	if (!cub)
		return (1);

	char maps[3][17] = {
	    {"11111111111111111"},
	    {"10000000000000001"},
	    {"11111111111111111"}
	};

	buffer = ft_calloc(sizeof(t_mlx_image), 1);
	buffer->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGTH);
	buffer->width = WIN_WIDTH;
	buffer->heigth = WIN_HEIGTH;
	buffer->addr = mlx_get_data_addr(buffer->img, &buffer->bits_per_pixel,
			&buffer->line_length, &buffer->endian);
	cub->buffer = buffer;
	cub->player = ft_calloc(sizeof(t_player), 1);
	cub->player->pos_x = 1.5;
	cub->player->pos_y = 1.5;
	cub->player->direction = 0;
	i = 0;
	j = 0;
	cub->map_height = 3;
	cub->map_width = 17;
	cub->maps = ft_calloc(sizeof(char *), cub->map_height);
	while (j < cub->map_height)
	{
		i = 0;
		cub->maps[j] = ft_calloc(sizeof(char), cub->map_width);
		while (i < cub->map_width)
		{
			cub->maps[j][i] = maps[j][i];
			i++;
		}
		j++;
	}
	cub->floor_color = 0xbdbae3;
	cub->ceil_color = 0x000000;

	cub->texture[0] = load_texture(cub ,"./textures/void_2.xpm");
	cub->texture[1] = load_texture(cub ,"./textures/void_2.xpm");
	cub->texture[2] = load_texture(cub ,"./textures/void_1.xpm");
	cub->texture[3] = load_texture(cub ,"./textures/void_1.xpm");;
	static_cub(cub);
	mlx_hook(cub->win, 02, 1L << 0, on_key_press, cub);
	mlx_loop_hook(cub->mlx, render_next_frame, cub);
	mlx_loop(cub->mlx);
	free(cub);
	return (0);
}
