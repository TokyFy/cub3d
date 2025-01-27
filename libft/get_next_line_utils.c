/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:09:46 by sravonin          #+#    #+#             */
/*   Updated: 2024/04/12 09:17:44 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ret;

	if (!s)
		return (0);
	ret = (char *)s;
	if (c == '\0')
		return (&ret[ft_strlen(s)]);
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

size_t	ft_strlen(const char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
		index++;
	return (index);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	ret = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			ret[i] = s1[i];
	while (s2[j] != '\0')
		ret[i++] = s2[j++];
	ret[i] = '\0';
	free(s1);
	return (ret);
}

char	*ft_strdup(const char *src)
{
	char	*ret;
	int		i;

	i = 0;
	if (!src[i])
		return (NULL);
	while (src[i] && src[i] != '\n')
		i++;
	ret = (char *)malloc((i + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		ret[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
