/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rot_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:41:32 by kmieshko          #+#    #+#             */
/*   Updated: 2018/05/30 16:41:33 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int	ft_tmp_x(t_map *map, int i, int j, int gamma_z)
{
	int		tmp_x;

	tmp_x = map->scale * ((i * map->x - map->mid_x) * cos(RAD * gamma_z)
		- (j * map->y - map->mid_y) * sin(RAD * gamma_z));
	return (tmp_x);
}

static int	ft_tmp_y(t_map *map, int i, int j, int gamma_z)
{
	int		tmp_y;

	tmp_y = map->scale * ((i * map->x - map->mid_x) * sin(RAD * gamma_z)
		+ (j * map->y - map->mid_y) * cos(RAD * gamma_z));
	return (tmp_y);
}

void		ft_rot_map(t_map *map, int fi_x, int teta_y, int gamma_z)
{
	int		i;
	int		j;
	int		tmp_x;
	int		tmp_y;
	int		tmp_z;

	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->col)
		{
			tmp_x = ft_tmp_x(map, i, j, gamma_z);
			map->dot[j][i]->x = map->horiz + tmp_x * cos(RAD * teta_y)
			+ map->scale * map->tab[j][i] * map->z * sin(RAD * teta_y);
			tmp_y = ft_tmp_y(map, i, j, gamma_z);
			tmp_z = map->scale * (-tmp_x * sin(RAD * teta_y)
				+ map->tab[j][i] * map->z * cos(RAD * teta_y));
			map->dot[j][i]->y = map->vertic + tmp_y * cos(RAD * fi_x)
			- tmp_z * sin(RAD * fi_x);
			i++;
		}
		j++;
	}
}
