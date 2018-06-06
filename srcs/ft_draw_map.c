/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:35:11 by kmieshko          #+#    #+#             */
/*   Updated: 2018/05/30 16:35:13 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int	ft_get_color(int sub, t_color *color, int old, int line_coord)
{
	int tmp;

	tmp = (((color->r * (line_coord - old) / sub) << 16) +
			((color->g * (line_coord - old) / sub) << 8) +
			(color->b * (line_coord - old) / sub));
	return (tmp);
}

static void	ft_init_line(t_dot *dot0, t_dot *dot1, t_line *line)
{
	line->x0 = dot0->x;
	line->x1 = dot1->x;
	line->y0 = dot0->y;
	line->y1 = dot1->y;
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0);
	line->sx = line->x1 >= line->x0 ? 1 : -1;
	line->sy = line->y1 >= line->y0 ? 1 : -1;
	line->error = line->dx - line->dy;
}

static void	ft_condition_bres(t_line *line)
{
	if (line->error2 > -line->dy)
	{
		line->error -= line->dy;
		line->x0 += line->sx;
	}
	if (line->error2 < line->dx)
	{
		line->error += line->dx;
		line->y0 += line->sy;
	}
}

static void	ft_bresenham(t_dot *dot0, t_dot *dot1, t_map *map, int flag)
{
	int		sub;
	int		old_coord;
	t_line	line;
	t_color	col;
	int		grad;

	ft_init_line(dot0, dot1, &line);
	col.r = ((dot0->orig & 0xff0000) >> 16) - ((dot1->orig & 0xff0000) >> 16);
	col.g = ((dot0->orig & 0x00ff00) >> 8) - ((dot1->orig & 0x00ff00) >> 8);
	col.b = (dot0->orig & 0x0000ff) - (dot1->orig & 0x0000ff);
	sub = line.dx > line.dy ? line.x0 - line.x1 : line.y0 - line.y1;
	old_coord = line.dx > line.dy ? line.x0 : line.y0;
	mlx_pixel_put(map->mlx, map->win, line.x0, line.y0, dot0->orig);
	if (flag > 0)
	{
		while (line.x0 != line.x1 || line.y0 != line.y1)
		{
			grad = (line.dx > line.dy) ?
			dot0->orig + ft_get_color(sub, &col, old_coord, line.x0) :
			dot0->orig + ft_get_color(sub, &col, old_coord, line.y0);
			mlx_pixel_put(map->mlx, map->win, line.x0, line.y0, grad);
			line.error2 = line.error * 2;
			ft_condition_bres(&line);
		}
	}
}

void		ft_draw_map(t_map *map, int flag)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->col)
		{
			if (i < map->col - 1)
				ft_bresenham(map->dot[j][i], map->dot[j][i + 1], map, flag);
			if (j < map->rows - 1)
				ft_bresenham(map->dot[j][i], map->dot[j + 1][i], map, flag);
			i++;
		}
		j++;
	}
}
