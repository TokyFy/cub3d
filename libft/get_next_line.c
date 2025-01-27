/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:49:18 by sravonin          #+#    #+#             */
/*   Updated: 2024/04/07 16:25:28 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_new_post(char *w_post)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (w_post[i] && w_post[i] != '\n')
		i++;
	if (!w_post[i])
	{
		free(w_post);
		return (NULL);
	}
	ret = (char *)malloc(sizeof(char) * (ft_strlen(w_post) - i + 1));
	if (!ret)
		return (NULL);
	i++;
	j = 0;
	while (w_post[i])
		ret[j++] = w_post[i++];
	ret[j] = '\0';
	free(w_post);
	return (ret);
}

char	*ft_read(int fd, char *w_post)
{
	char	*buf;
	int		i;

	i = 1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_strchr(w_post, '\n') && i != 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[i] = '\0';
		w_post = ft_strjoin(w_post, buf);
	}
	free(buf);
	return (w_post);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*w_post;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	w_post = ft_read(fd, w_post);
	if (!w_post)
		return (NULL);
	ret = ft_strdup(w_post);
	w_post = ft_new_post(w_post);
	return (ret);
}
