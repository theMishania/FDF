# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chorange <chorange@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/04 19:45:35 by chorange          #+#    #+#              #
#    Updated: 2019/02/08 19:53:56 by chorange         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
OBJ = get_next_line.o main.o map_drawing.o read_map.o
#FLAGS = -Wextra -Werror -Wall




all: $(NAME)

$(NAME) : $(OBJ)
	#gcc $(OBJ) $(LIBS) -o $(NAME) 
$(OBJ): %.o: %.c
	gcc  -g *.c -L. -lmlx -lm -framework OpenGL -framework AppKit -o fdf

clean:
	rm -rf *.o

fclean: clean
	rm -rf fdf
re: fclean all