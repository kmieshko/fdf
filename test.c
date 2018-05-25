/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:32:33 by kmieshko          #+#    #+#             */
/*   Updated: 2018/03/30 10:32:39 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define LEAK system("leaks $(ps | grep a.out | cut -d ' ' -f 1)")

t_dot		*ft_create_dot_elem(void)
{
	t_dot	*dot;

	dot = (t_dot *)malloc(sizeof(t_dot));
	dot->x = 0;
	dot->y = 0;
	dot->orig = 0xffffff;
	return (dot);
}

t_dot		***ft_create_dot(int rows, int col)
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
	map->dot = 0;
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
	return (map);
}

int		ft_count_col(char *line)
{
	int	col;
	int	i;

	col = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			while (line[i + 1] != ' ' && line[i + 1])
				i++;
			col++;
		}
		i++;
	}
	return (col);
}

int		ft_check_rows(t_map *map, char *line)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	while (line[i] != '\0')
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			while (line[i + 1] != ' ' && line[i + 1])
				i++;
			col++;
		}
		i++;
	}
	if (col != map->col)
		return (0);
	return (1);
}

int		ft_count_rows(int fd, char *line, t_map *map)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_check_rows(map, line))
			rows++;
		else
			return (0);
	}
	return (rows);
}

t_map	*ft_get_rows_col(int fd, char *arr, t_map *map)
{
	char	*line;

	fd = open(arr, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Error: Can't open the map\n");
		return (NULL);
	}
	if (get_next_line(fd, &line) == -1)
	{
		ft_putstr("Error: Wrong map\n");
		return (NULL);
	}
	map->col = ft_count_col(line);
	map->rows = 1 + ft_count_rows(fd, line, map);
	if (!map->rows || !map->col)
	{
		ft_putstr("Error: Wrong map\n");
		return (NULL);
	}
	close(fd);
	return (map);
}

int		ft_count_nb(int nb)
{
	int i;

	i = 0;
	while (nb > 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

int		ft_save_color(char	*str)
{
	int	i;
	int	flag;
	int	orig;

	i = 0;
	flag = 0;
	orig = 0xffffff;
	while (str[i] != '\0')
	{
		if (str[i] == 'x')
		{
			orig = ft_atoi_base(str + i + 1, 16);
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		orig = 0xffffff;
	return (orig);
}

int		**ft_fill_tab(char *arr, t_map *map, int fd)
{
	int		**tab;
	char	*line;
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	fd = open(arr, O_RDONLY);
	tab = (int **)malloc(sizeof(int *) * map->rows);
	while(get_next_line(fd, &line))
	{
		tab[j] = (int *)malloc(sizeof(int) * map->col);
		tmp = ft_strsplit(line, ' ');
		i = 0;
		while (tmp[i] != NULL)
		{
			tab[j][i] = ft_atoi(tmp[i]);
			map->dot[j][i]->orig = ft_save_color(tmp[i]);
			i++;
		}
		j++;
	}
	close(fd);
	return (tab);
}

void	ft_map_z(t_map *map)
{
	int		i;
	int		j;

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
		map->z = 200 * (map->high / map->width);
	else
		map->z = 200 / (map->max - map->min) * (map->high / map->width);
}

t_map	*ft_read_map(char *arr, t_map *map)
{
	int		fd;

	if (!ft_get_rows_col(fd, arr, map))
		return (NULL);
	map->dot = ft_create_dot(map->rows, map->col);
	map->dot[0][0]->color = 0;
	map->tab = ft_fill_tab(arr, map, fd);
	map->x = (500 / map->col) * (map->high / map->width);
	map->y = (500 / map->rows) * (map->high / map->width);
	ft_map_z(map);
	map->scale = 1;
	map->horiz = map->width / 2;
	map->vertic = map->high / 2 + map->high / 8;
	map->mid_x = (map->x * (map->col - 1)) / 2;
	map->mid_y = (map->y * (map->rows - 1)) / 2;
	return (map);
}

void	ft_rot_map(t_map *map, int fi_x, int teta_y, int gamma_z)
{
	int		i;
	int		j;
	int		tmp_x;
	int		tmp_y;
	int		tmp_z;

	j = 0;
	i = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->col)
		{
			tmp_x = map->scale * ((i * map->x - map->mid_x) * cos(RAD * gamma_z) - (j * map->y - map->mid_y) * sin(RAD * gamma_z));
			map->dot[j][i]->x = map->horiz + tmp_x * cos(RAD * teta_y) + map->scale * map->tab[j][i] * map->z * sin(RAD * teta_y);
			tmp_y = map->scale * ((i * map->x - map->mid_x) * sin(RAD * gamma_z) + (j * map->y - map->mid_y) * cos(RAD * gamma_z));
			tmp_z = map->scale * (-tmp_x * sin(RAD * teta_y) + map->tab[j][i] * map->z * cos(RAD * teta_y));
			map->dot[j][i]->y = map->vertic + tmp_y * cos(RAD * fi_x) + tmp_z * sin(RAD * fi_x);
			i++;
		}
		j++;
	}
}

void ft_create_color(t_color *color)
{

}

int		ft_get_color(int sub, t_color *color, int old_coord, int line_coord)
{
	int tmp;

	tmp = 0;
	if (sub == 0)
		sub = 1;
	tmp = (((color->r * (line_coord - old_coord) / sub) << 16) + ((color->g * (line_coord - old_coord) / sub) << 8) + (color->b * (line_coord - old_coord) / sub));
	return (tmp);
}

void	ft_init_line(t_dot *dot0, t_dot *dot1, t_map *map, t_line *line)
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

void	ft_condition_bras(t_line *line)
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

void	ft_bresenham(t_dot *dot0, t_dot *dot1, t_map *map, int grad)
{
	int sub;
	int	old_coord;
	t_line	line;
	t_color	col;

	ft_init_line(dot0, dot1, map, &line);
	col.col0 = dot0->orig;
	col.col1 = dot1->orig;
	col.r = ((col.col0 & 0xff0000) >> 16) - ((col.col1 & 0xff0000) >> 16);
	col.g = ((col.col0 & 0x00ff00) >> 8) - ((col.col1 & 0x00ff00) >> 8);
	col.b = (col.col0 & 0x0000ff) - (col.col1 & 0x0000ff);
	sub = line.dx > line.dy ? line.x0 - line.x1 : line.y0 - line.y1;
	old_coord = line.dx > line.dy ? line.x0 : line.y0;
	while (line.x0 != line.x1 || line.y0 != line.y1)
	{
		if (line.dx > line.dy)
			grad = col.col0 + ft_get_color(sub, &col, old_coord, line.x0);
		else if (line.dx <= line.dy)
			grad = col.col0 + ft_get_color(sub, &col, old_coord, line.y0);
		mlx_pixel_put(map->mlx, map->win, line.x0, line.y0, grad);
		line.error2 = line.error * 2;
		ft_condition_bras(&line);
	}
}

void	ft_paint(t_map *map)
{
	int i;
	int j;

	j = 0;
	mlx_clear_window(map->mlx, map->win);
	while (j < map->rows)
	{
		i = 0;
		while (i < map->col)
		{
			if (i < map->col - 1)
				ft_bresenham(map->dot[j][i], map->dot[j][i + 1], map, 0);
			if (j < map->rows - 1)
				ft_bresenham(map->dot[j][i], map->dot[j + 1][i], map, 0);
			i++;
		}
		j++;
	}
}

void	ft_print_text(int key, t_map *map)
{
	if (map->high >= 500 && map->width >= 1000)
	{
		mlx_string_put(map->mlx, map->win, map->width / 2 - 50, map->high / 100, 0xff9f00, "Control");
		mlx_string_put(map->mlx, map->win, map->width / 100, map->high / 20, 0x68e601, "Sift:");
		mlx_string_put(map->mlx, map->win, map->width / 100, map->high / 15 + 15, 0xc0c401, "Arrow Left  - [Left]");
		mlx_string_put(map->mlx, map->win, map->width / 100, map->high / 15 + 30, 0xc0c401, "Arrow Right - [Right]");
		mlx_string_put(map->mlx, map->win, map->width / 100, map->high / 15 + 45, 0xc0c401, "Arrow Up    - [Up]");
		mlx_string_put(map->mlx, map->win, map->width / 100, map->high / 15 + 60, 0xc0c401, "Arrow Down  - [Down]");
		mlx_string_put(map->mlx, map->win, map->width / 4, map->high / 20, 0x68e601, "Rotate:");
		mlx_string_put(map->mlx, map->win, map->width / 4, map->high / 15 + 15, 0xc0c401, "X-axis     - [Num 8]   or [Num 2]");
		mlx_string_put(map->mlx, map->win, map->width / 4, map->high / 15 + 30, 0xc0c401, "Y-ordinat  - [Num 4]   or [Num 6]");
		mlx_string_put(map->mlx, map->win, map->width / 4, map->high / 15 + 45, 0xc0c401, "Z-applikat - [Num 7,1] or [Num 9, 3]");
		mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 20, 0x68e601, "Appearance:");
		mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 15, 0xc0c401, "Scale            - [Num -] or [Num +]");
		mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 30, 0xc0c401, "High Up / Down   - [Z]     or [X]");
		mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 45, 0xc0c401, "Color            - [C]");
		mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 60, 0xc0c401, "Reset            - [Space]");
		mlx_string_put(map->mlx, map->win, map->width / 1.6f, map->high / 15 + 75, 0xc0c401, "Top View         - [Num 5]");
	}
}


void	ft_color_switch(t_map *map)
{
	int i;
	int j;
	int buf;

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

int	ft_rainbow(int nb)
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

void	ft_paint_up(t_map *map)
{
	int i;
	int j;
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
			map->dot[j][i]->color = ft_rainbow(((map->tab[j][i] - map->min) * count) / sub);
			i++;
		}
		j++;
	}
}

int		ft_manage(int key, t_map *map)
{	
	static t_rot rot;

	if (map->flag == 0)
	{
		rot.fi_x = -30;
		rot.teta_y = 0;
		rot.gamma_z = 30;
	}
	map->flag = 1;
	if (key == 53)
		exit (0);
	if (key == 49)
	{
		map->horiz = map->width / 2;
		map->vertic = map->high / 2 + map->high / 8;
		map->scale = 1;
		ft_map_z(map);
		rot.fi_x = -30;
		rot.teta_y = 0;
		rot.gamma_z = 30;
	}

	if (key == 87)
	{
		map->horiz = map->width / 2;
		map->vertic = map->high / 2 + map->high / 8;
		map->scale = 1;
		ft_map_z(map);
		rot.fi_x = 0;
		rot.teta_y = 0;
		rot.gamma_z = 0;
	}

//high
	if (key == 7)
		map->z *= 1.25;
	else if (key == 6)
		map->z /= 1.25;

//rotation
	if (key == 91)
		rot.fi_x -= 5;
	else if (key == 84)
		rot.fi_x += 5;
	else if (key == 86)
		rot.teta_y -= 5;	
	else if (key == 88)
		rot.teta_y += 5;
	else if (key == 92 || key == 85)
		rot.gamma_z += 5;
	else if (key == 89 || key == 83)
		rot.gamma_z -= 5;

//scale
	if (key == 78)
		map->scale /= 1.25;
	else if (key == 69)
		map->scale *= 1.25;

//arrows
	if (key == 125)
		map->vertic += 10;
	else if (key == 126)
		map->vertic -= 10;
	else if (key == 124)
		map->horiz += 10;
	else if (key == 123)
		map->horiz -= 10;

//color
	if (key == 8)
	{
		if (!map->dot[0][0]->color)
			ft_paint_up(map);
		ft_color_switch(map);
	}
	ft_rot_map(map, rot.fi_x, rot.teta_y, rot.gamma_z);
	ft_paint(map);
	ft_print_text(key, map);
	return (0);
}

int ft_exit_mouse(void)
{
	exit(1);
}

int main(int argc, char **argv)
{
	t_map	*map;
	t_rot	rot;

	rot.fi_x = -30;
	rot.teta_y = 0;
	rot.gamma_z = 30;

	map = NULL;
	if (argc != 2)
	{
		ft_putstr("Error: no arguments found\n");
		return (0);
	}
	map = ft_create_map();
	if (!ft_read_map(argv[1], map))
		return (0);
	ft_rot_map(map, rot.fi_x, rot.teta_y, rot.gamma_z);
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->width, map->high, "42");
	ft_paint(map);
	ft_print_text(0, map);
	mlx_hook(map->win, 2, 5, ft_manage, map);
	mlx_hook(map->win, 17, 1L << 17, ft_exit_mouse, map);
	mlx_loop(map->mlx);

	while (map->rows > 0)
	{
		free(map->dot[map->rows]);
		map->rows--;
	}
	free(map->tab);
	free(map);
	LEAK;
	return (0);
}
