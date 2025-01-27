/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:12:24 by sravonin          #+#    #+#             */
/*   Updated: 2024/03/16 13:15:13 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		start;
	char	*ret;

	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	start = 0;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	ret = malloc(end - start + 2);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, &s1[start], end - start + 2);
	return (ret);
}
