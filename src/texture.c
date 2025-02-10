/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:08:47 by franaivo          #+#    #+#             */
/*   Updated: 2025/02/10 10:08:48 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

t_mlx_image	*load_texture(t_cub *cub, char *path)
{
	t_mlx_image	*texture_n;

	texture_n = malloc(sizeof(t_mlx_image));
	texture_n->img = mlx_xpm_file_to_image(cub->mlx, path, &texture_n->width,
			&texture_n->heigth);
	texture_n->addr = mlx_get_data_addr(texture_n->img,
			&texture_n->bits_per_pixel, &texture_n->line_length,
			&texture_n->endian);
	return (texture_n);
}
