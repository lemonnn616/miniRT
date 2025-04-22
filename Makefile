NAME = miniRT

SRC_DIRS = sources sources/parsing
VPATH = $(SRC_DIRS) includes/libft

SRCS = \
	main.c \
	parse_scene.c \
	render.c \
	shapes.c \
	utils.c

BONUS_SRCS  =

OBJ = $(SRCS:.c=.o)
OBJ_BONUS = $(BONUS_SRCS:.c=.o)

LIBFT_DIR   = includes/libft
MLX42_DIR   = includes/MLX42

INCLUDES = -Iincludes/headers -I$(MLX42_DIR)/include -I$(LIBFT_DIR)

CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
LDFLAGS = -L$(MLX42_DIR)/build -lmlx42 -lglfw -ldl -pthread -lm $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJ)
	@echo "[Build] Compiling and linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	@echo "[Success] $(NAME) has been created!"

bonus: CFLAGS += -DBONUS
bonus: $(NAME)
	@echo "[Build] Compiling with BONUS and linking $(NAME)..."
	@echo "[Success] $(NAME) (with bonus) has been created!"

$(LIBFT_DIR)/libft.a:
	@echo "[Info] Building libft library..."
	$(MAKE) -C $(LIBFT_DIR)
	@echo "[Success] libft built."

%.o: %.c
	@echo "[Compile] $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "[Clean] Removing object files..."
	rm -f $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "[Fclean] Removing binary $(NAME)..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
	@echo "[Rebuild] Complete!"

.PHONY: all bonus clean fclean re