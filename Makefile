NAME := miniRT

SRC_DIRS := sources sources/parsing sources/math sources/utils
VPATH := $(SRC_DIRS)
SRCS := \
	main.c \
	vec_normalize.c \
	free_scene.c \
	parse_ambient.c \
	parse_camera.c \
	parse_color.c \
	parse_cone.c \
	parse_cylinder.c \
	parse_light.c \
	parse_line.c \
	parse_plane.c \
	parse_resolution.c \
	parse_scene.c \
	parse_sphere.c \
	parse_vector.c \
	free_tokens.c \
	ft_strtol.c \
	ft_strtof.c \
	ft_strtok.c \
	split_whitespace.c

OBJ_DIR := objects
OBJECTS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR := includes/libft
MLX42_DIR := includes/MLX42
MLX42_BUILD:= $(MLX42_DIR)/build

INCLUDES := -Iincludes/headers -I$(MLX42_DIR)/include -I$(LIBFT_DIR)
CC := cc
CFLAGS := -Wall -Wextra -Werror $(INCLUDES)
MLX42_LIB := $(MLX42_BUILD)/libmlx42.a
LDFLAGS := -L$(MLX42_BUILD) -lmlx42 -lglfw -ldl -pthread -lm \
				$(LIBFT_DIR)/libft.a

all: git-submodule MLX42 $(NAME)

git-submodule:
	@git submodule update --init --recursive

$(MLX42_LIB):
	@echo "[Info] Building MLX42…"
	@mkdir -p $(MLX42_BUILD)
	@cd $(MLX42_BUILD) && cmake .. && make
	@echo "[Success] MLX42 built."

MLX42: $(MLX42_LIB)

$(LIBFT_DIR)/libft.a:
	@echo "[Info] Building libft…"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "[Success] libft built."

$(NAME): $(MLX42_LIB) $(LIBFT_DIR)/libft.a $(OBJECTS)
	@echo "[Build] Linking $(NAME)…"
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
	@echo "[Success] $(NAME) created!"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "[Compile] $< → $@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "[Clean] Removing object files…"
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "[Clean] Done."

fclean: clean
	@echo "[Fclean] Removing binary $(NAME)…"
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re git-submodule MLX42
