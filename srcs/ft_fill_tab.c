/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:37:57 by kmieshko          #+#    #+#             */
/*   Updated: 2018/05/30 16:37:58 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int	ft_save_color(char *str)
{
	int	i;
	int	flag;
	int	orig;

	i = 0;
	flag = 0;
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

int			**ft_fill_tab(char *arr, t_map *map, int fd, int j)
{
	int		**tab;
	char	*line;
	char	**tmp;
	int		i;

	fd = open(arr, O_RDONLY);
	tab = (int **)malloc(sizeof(int *) * map->rows);
	while (get_next_line(fd, &line))
	{
		tab[j] = (int *)malloc(sizeof(int) * map->col);
		tmp = ft_strsplit(line, ' ');
		free(line);
		i = 0;
		while (tmp[i] != NULL)
		{
			tab[j][i] = ft_atoi_base(tmp[i], 10);
			map->dot[j][i]->orig = ft_save_color(tmp[i]);
			free(tmp[i]);
			i++;
		}
		free(tmp);
		j++;
	}
	close(fd);
	return (tab);
}
