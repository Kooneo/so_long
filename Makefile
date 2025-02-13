CC = cc
NAME = so_long
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
# CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3 
LIBS =  -lmlx -lXext -lX11 -lm -lbsd

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

$(NAME): $(OFILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT) $(LIBS) -o $(NAME)
	
$(LIBFT):
	make -C $(LIBFT_DIR) 
	make -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) -Imlx -c $< $(CFLAGS) -o $@

clean:
	rm -f $(OFILES)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

run: re
	./$(NAME) ./maps/map2.ber 

.PHONY: all clean fclean re run