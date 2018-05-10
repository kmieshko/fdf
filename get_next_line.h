/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:13:30 by kmieshko          #+#    #+#             */
/*   Updated: 2018/01/25 17:20:43 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 4096

# include <fcntl.h>
# include "libft/libft.h"

typedef struct		s_gnl
{
	void			*content;
	size_t			content_size;
	struct s_gnl	*next;
	int				fd;
}					t_gnl;

int					get_next_line(int const fd, char **line);

#endif
