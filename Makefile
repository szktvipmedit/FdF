# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 16:07:31 by kousuzuk          #+#    #+#              #
#    Updated: 2023/10/07 17:00:30 by kousuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fdf.c \
	   draw.c \
	   input_map.c \
	   #operation.c
	

OBJS = ${SRCS:.c=.o}

NAME = fdf
LIBFT = libftex/libft.a
MLX = minilibx_macos/libmlx.a
CC	= cc
CFLAGS = -Wall -Wextra -Werror

all: ${NAME} $(LIBFT) $(MLX) ;

#cflagsは今はいいや
%.o: %.c
	$(CC) -c $< -o $@

#gcc *.c libft/libft.a minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
#cflagsは今はいいや
${NAME}: ${OBJS} $(LIBFT)
	$(CC) -c $(SRCS)
	${CC} -o $@ $(SRCS) $(LIBFT) $(MLX) -framework OpenGL -framework AppKit 


$(LIBFT):
	make -C libftex

$(MLX):
	make -C minilibx_macos

clean: 
	rm -rf $(LIBFT)
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean clean all ;

.PHONY: all clean fclean re