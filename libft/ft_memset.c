/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:58:56 by sravonin          #+#    #+#             */
/*   Updated: 2024/02/24 17:18:10 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*t;
	size_t	i;

	i = 0;
	t = (char *)s;
	while (i < n)
	{
		t[i] = c;
		i++;
	}
	return ((void *)t);
}
