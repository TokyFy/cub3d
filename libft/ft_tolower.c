/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:30:19 by sravonin          #+#    #+#             */
/*   Updated: 2024/02/21 15:35:52 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	int	a;

	if (c >= 'A' && c <= 'Z')
	{
		a = c + 32;
		return (a);
	}
	else
		return (c);
}
