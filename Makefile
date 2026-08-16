CC = cc
NAME = so_long

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a

CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(MLX_DIR)

LIBS = $(MLX) -framework OpenGL -framework AppKit

CFILES = so_long.c \
		map_check.c \
		image_utils.c \
		handle_map.c \
		map_utils.c \
		movement.c \
		keys_manage.c \
		animation.c \
		animation_utils.c \
		game_utils.c \
		game_utils_2.c \
		game_init.c \
		map_utils_2.c \
		map_utils_3.c \
		map_utils_4.c \
		special_design.c \
		map_design.c \
		counter.c \
		utils.c \
		enemy.c

OFILES = $(CFILES:.c=.o)


all: $(NAME)


$(NAME): $(OFILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT) $(LIBS) -o $(NAME)


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus


$(MLX):
	$(MAKE) -C $(MLX_DIR)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -f $(OFILES)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean


fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all


run: $(NAME)
	./$(NAME) ./maps/map2.ber


.PHONY: all clean fclean re run