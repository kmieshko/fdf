# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/30 16:09:26 by kmieshko          #+#    #+#              #
#    Updated: 2018/05/30 16:09:32 by kmieshko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

INCL = ./incl/fdf.h \
		./incl/get_next_line.h

SRCS = ./srcs/ft_atoi_base.c \
		./srcs/ft_col_rows.c \
		./srcs/ft_create.c \
		./srcs/ft_draw_map.c \
		./srcs/ft_fill_tab.c \
		./srcs/ft_manage.c \
		./srcs/ft_paint_up.c \
		./srcs/ft_print_text.c \
		./srcs/ft_read_map.c \
		./srcs/ft_rot_map.c \
		./srcs/get_next_line.c \
		./srcs/main.c \
		./srcs/join.c

OBJ = $(SRCS:.c=.o)

LIB = libft/libft.a

COMPILE = gcc -c 

FLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(OBJ) $(FLAGS) $(LIB) -o $(NAME)

%.o: %.c
	$(COMPILE) -o $@ $< -Wall -Werror -Wextra 
	
clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
	make re -C ./libft