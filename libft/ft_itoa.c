/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 12:25:32 by kmieshko          #+#    #+#             */
/*   Updated: 2017/11/24 12:25:33 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(long int nb)
{
	int	count;

	count = 0;
	if (nb <= 0)
	{
		nb = -nb;
		count = 1;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static long int	ft_negativ(long int nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}

char			*ft_itoa(int nbr)
{
	long int	n;
	int			count;
	char		*arr;

	n = (long int)nbr;
	count = ft_count(n);
	n = ft_negativ(n);
	if (!(arr = (char *)malloc(sizeof(char) * count + 1)))
		return (NULL);
	arr[count] = '\0';
	while (count >= 0)
	{
		arr[count - 1] = n % 10 + 48;
		n = n / 10;
		count--;
	}
	if (nbr < 0)
		arr[0] = '-';
	return (arr);
}
