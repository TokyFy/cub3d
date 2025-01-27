/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:57:09 by sravonin          #+#    #+#             */
/*   Updated: 2024/03/19 13:46:48 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	if (n == 0)
		i = 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			l;
	long int	num;

	num = n;
	l = count_size(n);
	if (n < 0)
	{
		num *= -1;
		l++;
	}
	str = (char *)malloc((l + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[l] = '\0';
	while (l--)
	{
		str[l] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

/*#include <stdio.h>

int	main()
{
	printf("%s", ft_itoa(-21));
}*/
