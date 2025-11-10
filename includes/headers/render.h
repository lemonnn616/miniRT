/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:25:36 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 12:50:27 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <float.h>
# include "libft.h"
# include "rt_math.h"
# include "object.h"
# include "color.h"

# define ERR_MEM "Failed to allocate memory"
# define ERR_THREAD "Failed to create thread"
# define ERR_MUTEX "Failed to initialise mutex"
# define ERR_COND "Failed to initialise condition variable"
# define OFFSET 0.001f
# define SEED_BASE 0x9E3779B97F4A7C15ULL
# define ETERNITY 1

typedef struct s_data		t_data;
typedef struct s_cylinder	t_cylinder;

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
	t_color		color;
	t_color		obj_color;
	t_vec3		surface_norm;
	bool		reflection_ray;
	bool		is_shiny;
}	t_hit;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_hit	*hit_data;
	t_pcg	*rng;
}	t_ray;

typedef struct s_pixel
{
	t_vec3		ray_direction;
	t_color		obj_color;
	t_color		final_color;
	t_vec3		location;
	t_vec3		surface_norm;
	float		specular;
	float		shininess;
	float		reflectivity;
	t_color		ambient;
	t_color		color_sum;
	uint32_t	spp;
}	t_pixel;

typedef struct s_thread_ctx
{
	t_data		*data;
	uint32_t	y_start;
	uint32_t	y_stride;
	t_pcg		rng;
}	t_thread_ctx;

typedef struct s_dlctx
{
	t_data	*data;
	t_hit	*hit;
	t_vec3	view_dir;
	t_pcg	*rng;
}	t_dlctx;

// Progressive rendering lifecycle & orchestration
void	start_progressive_render(t_data *data);
void	cast_rays(t_data *data);
void	render_pass(t_data *data, uint32_t y_start,
			uint32_t y_stride, t_pcg *rng);
void	trace_paths(t_data *data, t_ray *ray, uint32_t y, uint32_t x);
void	cleanup_threads(t_data *data);

// Frame prep: buffers, camera orientation, preview
void	reset_pixel_buffer(t_data *d);
void	recalc_rays_with_orientation(t_data *data);
void	prepare_preview(t_data *data, t_ray *ray,
			uint32_t y_start, uint32_t x);

// Ray–object intersection routines
void	find_closest_object(t_data *data, t_ray *ray, t_hit *hit);
bool	valid_intersection(float *low, float *high);
void	update_hit(t_ray *ray, float distance, t_object *obj);
void	intersect_sphere(t_hit *hit, t_ray *ray, t_object *obj);
void	intersect_plane(t_hit *hit, t_ray *ray, t_object *obj);
void	intersect_cylinder(t_hit *hit, t_ray *ray, t_object *obj);
void	intersect_cone(t_hit *hit, t_ray *ray, t_object *obj);
void	intersect_light_globe(t_hit *hit, t_ray *ray, t_object *obj);

// Geometric helpers for intersections
bool	is_within_cylinder_height(t_ray *ray, t_cylinder *c, float root);
bool	is_within_circular_area(t_ray *ray, float radius,
			t_vec3 top_center, float distance);

// Surface interaction & shading setup
void	compute_surface_interaction(t_hit *hit, t_vec3 ray_direction);
void	handle_sphere_surface_interaction(t_hit *hit);
void	handle_plane_surface_interaction(t_hit *hit);
void	handle_cylinder_surface_interaction(t_hit *hit);
void	handle_cone_surface_interaction(t_hit *hit);
void	handle_light_globe_interaction(t_hit *hit, t_vec3 ray_direction);
void	update_orientation(t_hit *hit, t_vec3 normal, float denominator);
void	offset_ray_origin(const t_vec3 p, const t_vec3 n, t_vec3 *origin_out);

#endif
