/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:09:00 by sravonin          #+#    #+#             */
/*   Updated: 2024/03/05 11:40:51 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	full;

	full = nmemb * size;
	ptr = malloc(full);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, full);
	return (ptr);
}
