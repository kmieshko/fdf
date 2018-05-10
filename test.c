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

t_dot		*ft_create_dot_elem(void)
{
	t_dot	*dot;

	dot = (t_dot *)malloc(sizeof(t_dot));
	dot->x = 0;
	dot->y = 0;
	dot->color = 0xffffff;
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
	map->high = 500;
	map->width = 500;
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
			//map->dot[j][i]->color = добаить поддержку цвета
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
		map->z = 200 / (map->high / map->width) * ((1.0f * map->high) / (1.0f * map->width));
	else
		map->z = 200 / (map->max - map->min) * ((1.0f * map->high) / (1.0f * map->width));
}

t_map	*ft_read_map(char *arr, t_map *map)
{
	int		fd;

	if (!ft_get_rows_col(fd, arr, map))
		return (NULL);
	map->dot = ft_create_dot(map->rows, map->col);
	map->tab = ft_fill_tab(arr, map, fd);
	map->x = (map->width / 2.0f) / map->col;
	map->y = (map->high / 2.0f) / map->rows;
	ft_map_z(map);
	map->scale = 1;
	map->horiz = map->x * 20;
	map->vertic = map->y * 10;
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
			tmp_x = map->scale * (i * map->x - map->mid_x) * cos(RAD * gamma_z) - (j * map->y - map->mid_y) * sin(RAD * gamma_z);
			map->dot[j][i]->x = map->horiz + tmp_x * cos(RAD * teta_y) + 
			map->scale * map->tab[j][i] * map->z * sin(RAD * teta_y);
			tmp_y = map->scale * ((i * map->x - map->mid_x) * sin(RAD * gamma_z) + (j * map->y - map->mid_y) * cos(RAD * gamma_z));
			tmp_z = map->scale * (-tmp_x * sin(RAD * teta_y) + map->tab[j][i] * map->z * cos(RAD * teta_y));
			map->dot[j][i]->y = map->vertic + tmp_y * cos(RAD * fi_x) + tmp_z * sin(RAD * fi_x);
			i++;
		}
		j++;
	}
}

void ft_create_color(int col0, int col1, t_color *color)
{
	color->r = abs(col0 - col1) >> 16;
	color->g = abs(col0 - col1) >> 8;
	color->b = abs(col0 - col1);
	// printf("color.r = %d\n", color->r);
	// printf("color.g = %d\n", color->g);
	// printf("color.b = %d\n", color->b);
}

void	ft_bresenham(t_dot *dot0, t_dot *dot1, t_map *map)
{
	int		col0;
	int		col1;
	int		error;
	int		error2;
	t_line	line;
	t_color	color;

	col0 = dot0->color;
	col1 = dot1->color;
	line.x0 = dot0->x;
	line.x1 = dot1->x;
	line.y0 = dot0->y;
	line.y1 = dot1->y;
	line.dx = abs(line.x1 - line.x0);
	line.dy = abs(line.y1 - line.y0);
	line.sx = line.x1 >= line.x0 ? 1 : -1;
	line.sy = line.y1 >= line.y0 ? 1 : -1;
	ft_create_color(col0, col1, &color);
	error = line.dx - line.dy;
	//mlx_pixel_put(map->mlx, map->win, line.x1, line.y1, 0xff0000);
	while (line.x0 != line.x1 || line.y0 != line.y1)
	{
		mlx_pixel_put(map->mlx, map->win, line.x0, line.y0, 0xffffff);
		error2 = error * 2;
		if (error2 > -line.dy)
		{
			error -= line.dy;
			line.x0 += line.sx;
		}
		if (error2 < line.dx)
		{
			error += line.dx;
			line.y0 += line.sy;
		}
	}
}

// закончил на ft_map2d_fill
// нужно сделать алгоритм

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
				ft_bresenham(map->dot[j][i], map->dot[j][i + 1], map);
			if (j < map->rows - 1)
				ft_bresenham(map->dot[j][i], map->dot[j + 1][i], map);
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
		rot.fi_x = 30;
		rot.teta_y = 0;
		rot.gamma_z = 30;
	}
	map->flag = 1;
	if (key == 53)
		exit (0);
	if (key == 49)
	{
		map->horiz = map->x * 20;
		map->vertic = map->y * 10;
		map->scale = 1;
		ft_map_z(map);
		rot.fi_x = 30;
		rot.teta_y = 0;
		rot.gamma_z = 30;
	}

	if (key == 87)
	{
		map->horiz = map->x * 20;
		map->vertic = map->y * 10;
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
	ft_rot_map(map, rot.fi_x, rot.teta_y, rot.gamma_z);
	ft_paint(map);
	
	//ft_key(key, map);
	return (0);
}

int main(int argc, char **argv)
{
	t_map	*map;
	t_rot	rot;

	rot.fi_x = 30;
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
	//ft_print_res(map);
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->width, map->high, "42");
	ft_paint(map);
	mlx_hook(map->win, 2, 5, ft_manage, map);
	mlx_loop(map->mlx);
	free(map);
	return (0);
}

void	ft_print_res(t_map *map)
{
	printf("col = %d\n", map->col);
	printf("rows = %d\n", map->rows);
	for(int i = 0; i < map->rows; i++)
	{
		for(int j = 0; j < map->col; j++)
		{
			if (map->tab[i][j] != 0)
				map->tab[i][j] = 130;
			printf("%c ", map->tab[i][j] + 48);
		}
		printf("\n");
	}
}
