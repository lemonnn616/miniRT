/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:26:40 by natallia          #+#    #+#             */
/*   Updated: 2025/06/20 13:44:08 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	sum(t_color colour)
{
	return (colour.r + colour.g + colour.b);
}

bool	is_shiny(t_pcg *rng, float shininess)
{
	float	random;

	random = pcg_random_float(rng);
	if (random <= shininess)
		return (true);
	return (false);
}

static void	prepare_ray(t_data *d, t_ray *r, uint32_t y, uint32_t x)
{
	t_pixel	*pxl;

	pxl = &d->pixels[y][x];
	r->hit_data->is_shiny = is_shiny(&r->rng, (*pxl).shininess);
	r->direction = (*pxl).ray_direction;
	r->hit_data->specular = (*pxl).specular;
	r->hit_data->colour = lerp_colour((*pxl).obj_colour,
		new_colour(1.0f, 1.0f, 1.0f), r->hit_data->is_shiny);
	r->origin = (*pxl).location;
	r->hit_data->surface_norm = (*pxl).surface_norm;
	r->hit_data->inside_obj = false;
	r->hit_data->type = OBJ_NONE;
}

t_vec3	reflect_ray(t_vec3 surface_normal, t_vec3 incoming)
{
	t_vec3	reflected;

	reflected = vec_subtract(incoming, vec_scale(surface_normal,
		2.0f * vec_dot(incoming, surface_normal)));
	return (reflected);
}

void	bounce_ray(t_data *d, t_ray *r, t_hit *hit)
{
	t_vec3	diffuse_dir;
	t_vec3	specular_dir;

	diffuse_dir = generate_random_ray(&r->rng);
	if (vec_dot(diffuse_dir, hit->surface_norm) < 0)
		diffuse_dir = vec_scale(diffuse_dir, -1.0f);
	diffuse_dir = lerp_vec(diffuse_dir, hit->surface_norm, 0.5f);
	diffuse_dir = vec_normalize(diffuse_dir);
	r->direction = diffuse_dir;
	if (hit->is_shiny == true)
	{
		specular_dir = reflect_ray(hit->surface_norm, r->direction);
		if (vec_dot(specular_dir, hit->surface_norm) < 0)
			specular_dir = vec_scale(specular_dir, -1.0f);
		specular_dir = lerp_vec(diffuse_dir, specular_dir, hit->specular);
		r->direction = vec_normalize(specular_dir);
	}
	find_closest_object(d, r, hit);
	compute_surface_interaction(hit, r->direction);
}

void	trace_paths(t_data *data, t_ray *ray, uint32_t y, uint32_t x)
{
	t_pixel	*pxl;
	int		rays;
	int		bounces;

	pxl = &data->pixels[y][x];
	rays = 0;
	while (rays < data->max_rays)
	{
		prepare_ray(data, ray, y, x);
		bounces = 0;
		while (bounces < data->max_bounces && ray->hit_data->type != OBJ_LIGHT)
		{
			bounce_ray(data, ray, ray->hit_data);
			bounces++;
			ray->origin = ray->hit_data->location;
		}
		if (ray->hit_data->type == OBJ_LIGHT)
			(*pxl).colour_sum = colour_add(ray->hit_data->colour,
				(*pxl).colour_sum);
		rays++;
	}
	(*pxl).final_colour = colour_scale((*pxl).colour_sum,
		1.0f / (float)(MAX_RAYS));
	gamma_adjust(&(*pxl).final_colour);
	(*pxl).final_colour = combine_colours((*pxl).final_colour, (*pxl).ambient);
}
