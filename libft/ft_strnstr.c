/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:59:25 by sravonin          #+#    #+#             */
/*   Updated: 2024/03/12 17:31:51 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (len == 0 && big == NULL)
		return (NULL);
	i = 0;
	len = (unsigned int)len;
	if (little[0] == '\0')
		return ((char *)big);
	if (big[0] == '\0')
		return (NULL);
	while (i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && j < ft_strlen(little)
			&& (i + j < len))
			j++;
		if (little[j] == '\0')
			return ((char *)(&big[i]));
		i++;
	}
	return (NULL);
}
