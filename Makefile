# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chorange <chorange@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/04 19:45:35 by chorange          #+#    #+#              #
#    Updated: 2019/01/04 19:59:48 by chorange         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
OBJ = get_next_line.o main.o map_drawing.o read_map.o
FLAGS = -Wextra -Werror -Wall
LIBS = -L. -lmlx -lm -lX11 -lXext




all: $(NAME)

$(NAME) : $(OBJ)
	gcc $(OBJ) $(LIBS) -o $(NAME)
$(OBJ): %.o: %.c
	gcc -c *.c  $(LIBS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf fdf
re: fclean all