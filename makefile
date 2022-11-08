NAME	=	so_long

SRC		=	main.c so_long_utils.c checks.c checks2.c launch_graphics.c moves.c

OBJS	=	$(SRC:.c=.o)

CC		=	gcc

LIBFT_DIR =		./libft/
LIBFT	  =		./libft/libft.a

MLX_DIR = ./minilibx-linux/
MLX = ./minilibx-linux/libmlx_Linux.a



all:		$(NAME)

%.o: %.c	$(LIBFT)
	$(CC) -Wall -Wextra -Werror -I/usr/include -Iminilibx-linux -O3 -c $< -o $@

$(NAME):	$(LIBFT) $(MLX) $(SRC) $(OBJS)
			$(CC) $(OBJS) $(LIBFT) -L$(MLX) $(MLX) -L/usr/lib -I$(MLX) -lXext -lX11 -lm -lz -o $(NAME)


$(MLX):
	make -C $(MLX_DIR)
	
$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS) 
	make clean -C $(LIBFT_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	$(RM) $(NAME)

re: fclean all