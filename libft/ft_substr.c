/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:37:41 by sravonin          #+#    #+#             */
/*   Updated: 2024/03/05 13:10:38 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	s_len;

	s_len = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[s_len])
		s_len++;
	if (start > s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
