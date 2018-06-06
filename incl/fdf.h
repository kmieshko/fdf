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
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include "mlx.h"

# define RAD (M_PI / 180)

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
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

typedef struct	s_rot
{
	int			fi_x;
	int			teta_y;
	int			gamma_z;
}				t_rot;

typedef struct	s_dot
{
	int			x;
	int			y;
	int			orig;
	int			color;
}				t_dot;

typedef	struct	s_map
{
	void		*mlx;
	void		*win;
	int			col;
	int			rows;
	int			**tab;
	t_dot		***dot;
	float		x;
	float		y;
	float		z;
	float		scale;
	int			min;
	int			max;
	float		vertic;
	float		horiz;
	int			flag;
	float		width;
	float		high;
	float		mid_x;
	float		mid_y;
	int			flag_dot;
}				t_map;

int				get_next_line(int const fd, char **line);
long long int	ft_atoi_base(char *str, int base);
int				ft_manage(int key, t_map *map);
void			ft_print_text(t_map *map);
t_dot			*ft_create_dot_elem(void);
t_dot			***ft_create_dot(int rows, int col);
t_map			*ft_create_map(void);
t_map			*ft_get_rows_col(int fd, char *arr, t_map *map);
void			ft_draw_map(t_map *map, int key);
t_map			*ft_read_map(char *arr, t_map *map);
int				ft_map_z(t_map *map);
void			ft_rot_map(t_map *map, int fi_x, int teta_y, int gamma_z);
void			ft_paint_up(t_map *map);
int				**ft_fill_tab(char *arr, t_map *map, int fd, int j);
char			*join(char *s1, char *s2);

#endif
