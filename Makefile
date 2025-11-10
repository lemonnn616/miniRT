NAME := miniRT

SRC_DIRS := sources sources/parsing sources/math sources/utils sources/debug sources/rendering/intersection \
			sources/rendering/surface_interaction sources/rendering \
			sources/hooks sources/math/quaternion sources/rendering/lighting
VPATH := $(SRC_DIRS)
SRCS := \
	main.c \
	free_scene.c \
	parse_ambient.c \
	parse_shininess.c \
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
	cleanup.c \
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
	color_math.c \
	light_utils.c \
	direct_lighting.c \
	light_evals.c \
	shadows.c \
	reflectance.c \
	handle_cone.c \
	handle_cylinder.c \
	handle_light_globe.c \
	handle_plane.c \
	handle_sphere.c \
	handle_surface_hit.c \
	rendering_pass.c \
	path_tracing.c \
	ray_casting.c \
	window.c \
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
	loop_hook.c \
	multithreading.c \
	cosine_hemisphere.c \
	parse_reflectivity.c \
	count_tokens.c \
	preview_mode.c \
	parse_scene_utils.c \
	parse_sphere_utils.c \
	parse_plane_utils.c \
	parse_cylinder_utils_1.c \
	parse_cylinder_utils_2.c \
	parse_cone_utils_1.c \
	parse_cone_utils_2.c \
	mouse_filters.c \
	mouse_input.c

OBJ_DIR := objects
OBJECTS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR	:= includes/libft
MLX42_DIR	:= includes/MLX42
MLX42_BUILD	:= $(MLX42_DIR)/build

INCLUDES	:= -Iincludes/headers -I$(MLX42_DIR)/include/MLX42 -I$(LIBFT_DIR)
CC			:= cc

CFLAGS		:= -Wall -Wextra -Werror -O3 -flto $(INCLUDES)
MLX42_LIB	:= $(MLX42_BUILD)/libmlx42.a

LDFLAGS		:= $(LIBFT_DIR)/libft.a

UNAME_S		:= $(shell uname -s)
UNAME_M		:= $(shell uname -m)

ifeq ($(UNAME_S),Darwin)
	ifeq ($(UNAME_M),arm64)
		CFLAGS  += -arch arm64
		LDFLAGS += -arch arm64 \
					-L$(MLX42_BUILD) -lmlx42 \
					-L/opt/homebrew/lib -lglfw \
					-framework Cocoa -framework IOKit -framework CoreVideo \
					-pthread -lm
	else
		LDFLAGS += -L$(MLX42_BUILD) -lmlx42 \
				-lglfw \
				-framework Cocoa -framework IOKit -framework CoreVideo \
				-pthread -lm
	endif
else
	LDFLAGS += -L$(MLX42_BUILD) -lmlx42 -lglfw -ldl -pthread -lm
endif

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
