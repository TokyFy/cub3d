/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:25:40 by sravonin          #+#    #+#             */
/*   Updated: 2024/02/28 14:29:51 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (src[i])
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
