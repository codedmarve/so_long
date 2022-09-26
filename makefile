NAME	=	so_long

SRC		=	main.c

OBJS	=	${SRCS:.c=.o}

CC		=	gcc

LIBFT_DIR =		./libft/
LIBFT	  =		./libft/libft.a

MLX_DIR= ./minilibx-linux/
MLX = ./minilibx-linux/libmlx.a



all:		$(NAME)

%.o: %.c	$(LIBFT)
	$(CC) -Wall -Wextra -Werror -I/usr/include -I$(MLX) -O3 -c $< -o $@


$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			$(CC) $(SRC) $(LIBFT) $(MLX) -L/usr/X11/lib -lXext -lX11 -o $(NAME)

$(MLX):
	make -C $(MLX_DIR)
	
$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all