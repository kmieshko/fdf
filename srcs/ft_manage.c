/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:15:52 by kmieshko          #+#    #+#             */
/*   Updated: 2018/05/30 16:15:53 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void		ft_fill_rot(t_rot *rot, int x, int y, int z)
{
	rot->fi_x = x;
	rot->teta_y = y;
	rot->gamma_z = z;
}

static void		ft_reset_top_scale_exit(int key, t_map *map, t_rot *rot)
{
	if (key == 44)
	{
		map->horiz = map->width / 2;
		map->vertic = map->high / 2 + map->high / 8;
		map->scale = 1;
		ft_map_z(map);
		ft_fill_rot(rot, -30, 0, 30);
	}
	if (key == 87)
	{
		map->horiz = map->width / 2;
		map->vertic = map->high / 2 + map->high / 8;
		map->scale = 1;
		ft_map_z(map);
		ft_fill_rot(rot, 0, 0, 0);
	}
	if (key == 78)
		map->scale /= 1.25;
	else if (key == 69)
		map->scale *= 1.25;
	if (key == 53)
		exit(0);
}

static void		ft_arrows_rot_z(int key, t_map *map, t_rot *rot)
{
	if (key == 125)
		map->vertic += 10;
	else if (key == 126)
		map->vertic -= 10;
	else if (key == 124)
		map->horiz += 10;
	else if (key == 123)
		map->horiz -= 10;
	if (key == 91)
		rot->fi_x -= 5;
	else if (key == 84)
		rot->fi_x += 5;
	else if (key == 86)
		rot->teta_y -= 5;
	else if (key == 88)
		rot->teta_y += 5;
	else if (key == 92 || key == 85)
		rot->gamma_z += 5;
	else if (key == 89 || key == 83)
		rot->gamma_z -= 5;
	if (key == 7)
		map->z *= 1.25;
	else if (key == 6)
		map->z /= 1.25;
}

static void		ft_swap_color(t_map *map)
{
	int i;
	int j;

	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->col)
		{
			ft_swap(&map->dot[j][i]->color, &map->dot[j][i]->orig);
			i++;
		}
		j++;
	}
}

int				ft_manage(int key, t_map *map)
{
	static t_rot	rot;
	static int		flag = 1;

	if (map->flag == 0)
		ft_fill_rot(&rot, -30, 0, 30);
	map->flag = 1;
	ft_reset_top_scale_exit(key, map, &rot);
	ft_arrows_rot_z(key, map, &rot);
	if (key == 8)
	{
		if (map->flag_dot == 0)
		{
			ft_paint_up(map);
			map->flag_dot = 1;
		}
		ft_swap_color(map);
	}
	if (key == 2)
		flag = -flag;
	ft_rot_map(map, rot.fi_x, rot.teta_y, rot.gamma_z);
	mlx_clear_window(map->mlx, map->win);
	ft_draw_map(map, flag);
	ft_print_text(map);
	return (0);
}
