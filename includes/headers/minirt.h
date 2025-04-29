/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:27:23 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/29 21:58:54 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "MLX42.h"
# include "libft.h"
# include "vec3.h"
# include "color.h"
# include "material.h"
# include "sphere.h"
# include "plane.h"
# include "cylinder.h"
# include "triangle.h"
# include "square.h"
# include "object.h"
# include "camera.h"
# include "light.h"
# include "ambient.h"
# include "scene.h"
# include "parser.h"
# include "utils.h"

# include <math.h>

# include "debug.h"

# define PI 3.1415927f
# define ERR_MEM "Failed to allocate memory"

typedef struct s_pixel
{
	t_vec3	ray_direction;
	t_vec3	base_colour;
	t_vec3	final_colour;
	t_vec3	location;
	t_vec3	surface_norm;
}	t_pixel;

typedef struct s_data
{
	t_scene			scene;
	mlx_t			*mlx;
	mlx_image_t		*image_buffer;
	t_pixel			**pixels;

} t_data;

void	exit_error(t_data *data, char *msg);
void	exit_success(t_data *data);

void	camera_compute_basis(t_camera *cam);
void	free_scene(t_scene *scene);

void	initialise_mlx_window(t_data *data);
void	free_pixels(t_pixel ***pixels, uint32_t y);

#endif
