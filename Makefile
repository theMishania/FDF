# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cocummin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/18 18:53:25 by chorange          #+#    #+#              #
#    Updated: 2019/02/23 10:39:50 by cocummin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FLAGS = -Wextra -Wall -Werror

OBJECTS = get_next_line.o main.o map_drawing.o read_map.o errors_handling.o \
			key_utils.o free_all.o provider.o guide_drawing.o fdf_init.o \
			image_operating.o point_init.o lines_drawing.o change_view_side.o

LIBS = -L./minilibx -lmlx -L./libft -lft -lm -framework OpenGL -framework AppKit

INCLUDES = -I./libft/libft.h -I./minilibx/mlx.h

MLXPATH = ./minilibx
FTPATH = ./libft

all: $(NAME)



$(NAME): $(OBJECTS)
	make -C $(FTPATH)
	make -C $(MLXPATH)

	gcc $(FLAGS) $(OBJECTS) $(INCLUDES) $(LIBS) -o $(NAME)

$(OBJECTS): %.o: %.c
	gcc $(FLAGS) -c  $< -o $@

clean:
	make -C $(FTPATH) clean
	make -C $(MLXPATH) clean
	/bin/rm -f $(OBJECTS)

fclean: clean
	make -C $(FTPATH) fclean
	make -C $(MLXPATH) clean
	/bin/rm -f $(NAME)

re: fclean all
