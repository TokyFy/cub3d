/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:57:27 by sravonin          #+#    #+#             */
/*   Updated: 2024/03/18 11:36:38 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	w_count(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	len;
	int		i;

	ret = (char **)malloc((w_count(s, c) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				len = ft_strlen(s);
			else
				len = ft_strchr(s, c) - s;
			ret[i++] = ft_substr(s, 0, len);
			s += len;
		}
	}
	ret[i] = NULL;
	return (ret);
}
