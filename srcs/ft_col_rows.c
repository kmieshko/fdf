/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_col_rows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:31:49 by kmieshko          #+#    #+#             */
/*   Updated: 2018/05/30 16:31:50 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int	ft_count_col(char *line)
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

static int	ft_check_rows(t_map *map, char *line)
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

static int	ft_count_rows(int fd, char *line, t_map *map)
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
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (rows);
}

t_map		*ft_get_rows_col(int fd, char *arr, t_map *map)
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
	free(line);
	close(fd);
	return (map);
}
