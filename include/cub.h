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
	double pos_x;
	double pos_y;
	uint direction;
} t_player;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_mlx_image	*buffer;
	char**		maps;
	t_player*	player;
}				t_cub;


#endif
