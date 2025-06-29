NAME := miniRT

SRC_DIRS := sources sources/parsing sources/math sources/utils sources/debug sources/rendering/intersection \
			sources/rendering/surface_interaction sources/rendering/lighting sources/rendering sources/rotation \
			sources/hooks sources/math/quaternion
VPATH := $(SRC_DIRS)
SRCS := \
	main.c \
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
	split_whitespace.c \
	camera_compute_basis.c \
	degree_to_radian.c \
	lerp.c \
	random.c \
	vec_add.c \
	vec_cross.c \
	vec_distance.c \
	vec_dot.c \
	vec_length.c \
	vec_normalize.c \
	vec_scale.c \
	vec_subtract.c \
	debug_parser.c \
	exit.c \
	intersect_cone.c \
	intersect_cylinder.c \
	intersect_cylinder2.c \
	intersect_light_globe.c \
	intersect_plane.c \
	intersect_sphere.c \
	intersection_utils.c \
	colour_math.c \
	colours.c \
	handle_cone.c \
	handle_cylinder.c \
	handle_light_globe.c \
	handle_plane.c \
	handle_sphere.c \
	handle_surface_hit.c \
	draw.c \
	path_tracing.c \
	ray_casting.c \
	window.c \
	rotate_objects.c \
	conjugate.c \
	create_from_two_vectors.c \
	create_from_axis_angle.c \
	multiply.c \
	normalize.c \
	rotate_vector.c \
	solve_quadratic.c \
	mouse.c \
	wasd.c \
	recalculate_rays_with_orientation.c \
	reset_pixel_buffer.c \
	update_wasd.c \
	loop_hook.c

OBJ_DIR := objects
OBJECTS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR := includes/libft
MLX42_DIR := includes/MLX42
MLX42_BUILD:= $(MLX42_DIR)/build

INCLUDES := -Iincludes/headers -I$(MLX42_DIR)/include/MLX42 -I$(LIBFT_DIR)
CC := cc
CFLAGS := -Wall -Wextra -Werror $(INCLUDES) -O3 -flto
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
