/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:32:33 by kmieshko          #+#    #+#             */
/*   Updated: 2018/03/30 10:32:39 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int	ft_exit_mouse(void)
{
	exit(1);
}

static int	ft_error_argc(int argc)
{
	if (argc < 2)
		ft_putstr("Error: no arguments found\n");
	else if (argc > 2)
		ft_putstr("Error: too many arguments\n");
	return (0);
}

int			main(int argc, char **argv)
{
	t_map	*map;
	t_rot	rot;

	rot.fi_x = -30;
	rot.teta_y = 0;
	rot.gamma_z = 30;
	if (argc != 2)
		return (ft_error_argc(argc));
	map = ft_create_map();
	if (!ft_read_map(argv[1], map))
		return (0);
	ft_rot_map(map, rot.fi_x, rot.teta_y, rot.gamma_z);
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->width, map->high, "42");
	ft_draw_map(map, 1);
	ft_print_text(map);
	mlx_hook(map->win, 2, 5, ft_manage, map);
	mlx_hook(map->win, 17, 1L << 17, ft_exit_mouse, map);
	mlx_loop(map->mlx);
	return (0);
}
