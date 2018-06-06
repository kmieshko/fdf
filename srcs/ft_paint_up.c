/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:43:36 by kmieshko          #+#    #+#             */
/*   Updated: 2018/05/30 16:43:38 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int	ft_rainbow(int nb)
{
	int tab[13];

	tab[0] = 0x4b0082;
	tab[1] = 0x6800b5;
	tab[2] = 0x8500e8;
	tab[3] = 0x0066cc;
	tab[4] = 0x0080ff;
	tab[5] = 0x009900;
	tab[6] = 0x00cc00;
	tab[7] = 0xffcc00;
	tab[8] = 0xffd633;
	tab[9] = 0xff7700;
	tab[10] = 0xff9233;
	tab[11] = 0xff0800;
	tab[12] = 0xff8d89;
	return (tab[nb]);
}

void		ft_paint_up(t_map *map)
{
	int	i;
	int	j;
	int	sub;
	int	count;

	count = 12;
	sub = map->max - map->min;
	if (sub < count)
		sub = count;
	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->col)
		{
			map->dot[j][i]->color =
			ft_rainbow(((map->tab[j][i] - map->min) * count) / sub);
			i++;
		}
		j++;
	}
}
