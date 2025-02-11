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

	char maps[32][32] = {
	    {"11111111111111111111111111111111"},
	    {"10000001000000001000000000000001"},
	    {"10111001011111001011111110111001"},
	    {"10100001000001001000000010001001"},
	    {"10101111101001001111111010110001"},
	    {"10100000001000000000001010001001"},
	    {"10101111101111111111001010111001"},
	    {"10100000000000000001001010000001"},
	    {"10111111111101111101001010111001"},
	    {"10000000000100000001001010001001"},
	    {"10111110111111101101001010100001"},
	    {"10100010000000000001001010001001"},
	    {"10101111101111111001111010111001"},
	    {"10000000001000001000000010000001"},
	    {"10111110100011101011111010111001"},
	    {"10100010101000001000001010001001"},
	    {"10101110101111101111101010100001"},
	    {"10100000100000000000001010001001"},
	    {"10111111101111101111001010111001"},
	    {"10000000001000000001001010000001"},
	    {"10111111101111111001111010111001"},
	    {"10100000000000000000000010001001"},
	    {"10101111111011111111111010101001"},
	    {"10001000001000000000001010000001"},
	    {"10101111011111101111101010101001"},
	    {"10100000000000001000001010001001"},
	    {"10111111101111101011101010111001"},
	    {"10000000001000001000000010000001"},
	    {"10111111101111101111111010111001"},
	    {"10000000000000000000000010000001"},
	    {"11111111111111111111111111111111"}
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
	cub->map_height = 32;
	cub->map_width = 32;
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
	cub->floor_color = 0x31FBFE;
	cub->ceil_color = 0x0E1414;
	cub->texture[0] = load_texture(cub ,"./textures/wall_65.xpm");
	cub->texture[1] = load_texture(cub ,"./textures/wall_32.xpm");
	cub->texture[2] = load_texture(cub ,"./textures/wall_16.xpm");
	cub->texture[3] = load_texture(cub ,"./textures/wall_46.xpm");;

	static_cub(cub);
	mlx_hook(cub->win, 02, 1L << 0, on_key_press, cub);
	mlx_loop_hook(cub->mlx, render_next_frame, cub);
	mlx_loop(cub->mlx);
	free(cub);
	return (0);
}
