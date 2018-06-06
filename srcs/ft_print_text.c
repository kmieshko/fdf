/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:19:46 by kmieshko          #+#    #+#             */
/*   Updated: 2018/05/30 16:19:47 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void	ft_print_text2(t_map *map)
{
	mlx_string_put(map->mlx, map->win, map->width / 4, map->high / 20,
		0x68e601, "Rotate:");
	mlx_string_put(map->mlx, map->win, map->width / 4, map->high / 15 + 15,
		0xc0c401, "X-axis     - [Num 8]   or [Num 2]");
	mlx_string_put(map->mlx, map->win, map->width / 4, map->high / 15 + 30,
		0xc0c401, "Y-ordinat  - [Num 4]   or [Num 6]");
	mlx_string_put(map->mlx, map->win, map->width / 4, map->high / 15 + 45,
		0xc0c401, "Z-applikat - [Num 7,1] or [Num 9, 3]");
	mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 20,
		0x68e601, "Appearance:");
	mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 15,
		0xc0c401, "Scale            - [Num -] or [Num +]");
	mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 30,
		0xc0c401, "High Up / Down   - [Z]     or [X]");
	mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 45,
		0xc0c401, "Color            - [C]");
	mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 60,
		0xc0c401, "Reset            - [Space]");
	mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 75,
		0xc0c401, "Top View         - [Num 5]");
	mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 90,
		0xc0c401, "Only Dot         - [D]");
}

void		ft_print_text(t_map *map)
{
	if (map->high >= 500 && map->width >= 1000)
	{
		mlx_string_put(map->mlx, map->win, map->width / 2 - 50,
			map->high / 100, 0xff9f00, "Control");
		mlx_string_put(map->mlx, map->win, map->width / 100,
			map->high / 20, 0x68e601, "Sift:");
		mlx_string_put(map->mlx, map->win, map->width / 100,
			map->high / 15 + 15, 0xc0c401, "Arrow Left  - [Left]");
		mlx_string_put(map->mlx, map->win, map->width / 100,
			map->high / 15 + 30, 0xc0c401, "Arrow Right - [Right]");
		mlx_string_put(map->mlx, map->win, map->width / 100,
			map->high / 15 + 45, 0xc0c401, "Arrow Up    - [Up]");
		mlx_string_put(map->mlx, map->win, map->width / 100,
			map->high / 15 + 60, 0xc0c401, "Arrow Down  - [Down]");
		ft_print_text2(map);
	}
}
