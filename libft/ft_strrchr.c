/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:18:47 by sravonin          #+#    #+#             */
/*   Updated: 2024/03/02 16:13:58 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	*ret;

	ret = (char *)s;
	last = NULL;
	while (*ret != '\0')
	{
		if (*ret == (char)c)
			last = ret;
		ret++;
	}
	if (*ret == (char)c)
		return (ret);
	return (last);
}
