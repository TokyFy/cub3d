/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:07:54 by sravonin          #+#    #+#             */
/*   Updated: 2024/03/16 11:26:40 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ret;

	ret = (char *)s;
	while (*ret != '\0')
	{
		if (*ret == (char)c)
			return (ret);
		ret++;
	}
	if (*ret == (char)c)
		return (ret);
	return (NULL);
}
