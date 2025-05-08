/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:27:23 by iriadyns          #+#    #+#             */
/*   Updated: 2025/05/08 14:48:18 by natallia         ###   ########.fr       */
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

# define ERR_MEM "Failed to allocate memory"

typedef struct s_hit
{
	bool		hit_occurred;
	t_obj_type	type;
	void		*obj_ptr;
	bool		inside_obj;
	bool		caps;
	float		distance;
	t_vec3		location;
	float		specular;
	float		shininess;
	float		reflectivity;
	t_color		colour;
	t_color		obj_colour;
	t_vec3		surface_norm;
}	t_hit;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_hit	*hit_data;
}	t_ray;

typedef struct s_pixel
{
	t_vec3	ray_direction;
	t_color	obj_colour;
	t_color	final_colour;
	t_vec3	location;
	t_vec3	surface_norm;
	float	specular;
	float	shininess;
	t_color	ambient;
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
void	cast_rays(t_data *data);
void	render(t_data *data, uint32_t y, uint32_t x);
bool	quadratic_equation(t_vec3 quad_coeff, float *roots);
bool	valid_intersection(float *low, float *high);
void	update_hit(t_ray *ray, float distance, t_object *obj);
void	intersect_sphere(t_hit *hit, t_ray *ray, t_object *obj);
void	update_orientation(t_hit *hit, t_vec3 normal, float denominator);
bool	is_within_cylinder_height(t_ray *ray, t_cylinder *c, float root);
bool	is_within_circular_area(t_ray *ray, float radius,
			t_vec3 top_center, float distance);
void	intersect_cone(t_hit *hit, t_ray *ray, t_object *obj);
void	intersect_plane(t_hit *hit, t_ray *ray, t_object *obj);
void	intersect_cylinder(t_hit *hit, t_ray *ray, t_object *obj);

#endif
