/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:00:17 by kmieshko          #+#    #+#             */
/*   Updated: 2018/03/30 14:00:19 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line.h" 
# include "libft/libft.h"
# include "mlx.h"

# define RAD (M_PI / 180)

// red		#FF0000
// green	#00FF00
// blue		#0000FF

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
	int			col0;
	int			col1;
}				t_color;

typedef struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			error;
	int			error2;
}				t_line;

typedef struct 	s_rot
{
	int	fi_x;
	int teta_y;
	int gamma_z;
}				t_rot;

typedef struct	s_dot
{
	int		x;
	int		y;
	int		color;
	int		orig;
}				t_dot;

typedef	struct	s_map
{
	void	*mlx;
	void	*win;
	int		col;
	int		rows;
	int		**tab;
	t_dot	***dot;
	float		x;
	float		y;
	float	z;
	float	scale;
	int		min;
	int		max;
	float		vertic;
	float		horiz;
	int		flag;
	float		width;
	float		high;
	float		mid_x;
	float		mid_y;
}				t_map;

int					get_next_line(int const fd, char **line);
long long int			ft_atoi_base(char *str, int base);

void	ft_print_res(t_map *map);

#endif