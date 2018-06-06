/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:30:26 by kmieshko          #+#    #+#             */
/*   Updated: 2018/05/30 16:30:27 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

t_dot	*ft_create_dot_elem(void)
{
	t_dot	*dot;

	dot = (t_dot *)malloc(sizeof(t_dot));
	dot->x = 0;
	dot->y = 0;
	dot->orig = 0xffffff;
	return (dot);
}

t_dot	***ft_create_dot(int rows, int col)
{
	t_dot	***dot;
	int		i;
	int		j;

	dot = (t_dot ***)malloc(sizeof(t_dot **) * (rows + 1));
	j = 0;
	while (j < rows)
	{
		i = 0;
		dot[j] = (t_dot **)malloc(sizeof(t_dot *) * (col + 1));
		while (i < col)
		{
			dot[j][i] = ft_create_dot_elem();
			i++;
		}
		j++;
	}
	return (dot);
}

t_map	*ft_create_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	map->mlx = NULL;
	map->win = NULL;
	map->col = 0;
	map->rows = 0;
	map->tab = NULL;
	map->dot = NULL;
	map->x = 0;
	map->y = 0;
	map->z = 0;
	map->scale = 0;
	map->max = 0;
	map->min = 0;
	map->flag = 0;
	map->mid_x = 0;
	map->mid_y = 0;
	map->high = 1000;
	map->width = 1000;
	map->flag = 0;
	map->flag_dot = 0;
	return (map);
}
