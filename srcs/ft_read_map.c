/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:40:06 by kmieshko          #+#    #+#             */
/*   Updated: 2018/05/30 16:40:08 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int		ft_map_z(t_map *map)
{
	int		i;
	int		j;
	int		z;

	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->col)
		{
			if (map->tab[j][i] > map->max)
				map->max = map->tab[j][i];
			if (map->tab[j][i] < map->min)
				map->min = map->tab[j][i];
			i++;
		}
		j++;
	}
	if (map->max == map->min)
		z = -200 * (map->high / map->width);
	else
		z = -200 / (map->max - map->min) * (map->high / map->width);
	return (z);
}

t_map	*ft_read_map(char *arr, t_map *map)
{
	int fd;

	fd = 0;
	if (!ft_get_rows_col(fd, arr, map))
		return (NULL);
	map->dot = ft_create_dot(map->rows, map->col);
	map->tab = ft_fill_tab(arr, map, fd, 0);
	map->scale = 1;
	map->x = (500 / map->col) * (map->high / map->width);
	map->y = (500 / map->rows) * (map->high / map->width);
	map->z = ft_map_z(map);
	map->horiz = map->width / 2;
	map->vertic = map->high / 2 + map->high / 8;
	map->mid_x = (map->x * (map->col - 1)) / 2;
	map->mid_y = (map->y * (map->rows - 1)) / 2;
	return (map);
}
