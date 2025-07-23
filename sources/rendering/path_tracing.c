/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:26:40 by natallia          #+#    #+#             */
/*   Updated: 2025/07/23 15:19:48 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	sample_direct_light(t_data *data, t_hit *hit)
{
	t_vec3		to_light;
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	t_light		*light;
	float		distance;
	float		n_dot_l;
	t_color		result;

	light = data->scene.lights;
	if (!light)
		return (new_colour(0.0f, 0.0f, 0.0f));

	to_light = vec_subtract(light->pos, hit->location);
	distance = vec_length(to_light);
	to_light = vec_normalize(to_light);

	n_dot_l = vec_dot(hit->surface_norm, to_light);
	if (n_dot_l <= 0.0f)
		return (new_colour(0.0f, 0.0f, 0.0f));

	shadow_ray.origin = vec_add(hit->location, vec_scale(hit->surface_norm, 0.001f));
	shadow_ray.direction = to_light;
	shadow_ray.hit_data = &shadow_hit;

	ft_memset(&shadow_hit, 0, sizeof(t_hit));
	find_closest_object(data, &shadow_ray, &shadow_hit);

	if (shadow_hit.hit_occurred && shadow_hit.type != OBJ_LIGHT
		&& shadow_hit.distance < distance)
		return (new_colour(0.0f, 0.0f, 0.0f));

	result = multiply_colours(light->color, hit->obj_colour);
	return (colour_scale(result, n_dot_l));
}

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

t_vec3	reflect_ray(t_vec3 surface_normal, t_vec3 incoming)
{
	t_vec3	reflected;

	reflected = vec_subtract(incoming, vec_scale(surface_normal,
		2.0f * vec_dot(incoming, surface_normal)));
	return (reflected);
}

static void	sample_direct_once(t_data *data, t_ray *ray,
	t_pixel *pxl, t_color *throughput)
{
	t_color	direct;
	t_color	contrib;

	direct = sample_direct_light(data, ray->hit_data);
	contrib = multiply_colours(*throughput, direct);
	pxl->colour_sum = colour_add(pxl->colour_sum, contrib);
}

static void	bounce_ray(t_data *d, t_ray *r, t_hit *hit)
{
	t_vec3	diffuse_dir;
	t_vec3	specular_dir;

	diffuse_dir = generate_random_ray(r->rng);
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

static void	process_bounces(t_data *data, t_ray *ray, t_pixel *pxl)
{
	int		bounces;
	t_color	throughput;
	t_color	inc;
	t_color	contrib;

	bounces = 0;
	throughput = new_colour(1.0f, 1.0f, 1.0f);
	while (bounces < data->max_bounces)
	{
		ft_memset(ray->hit_data, 0, sizeof(t_hit));
		bounce_ray(data, ray, ray->hit_data);
		if (ray->hit_data->hit_occurred == false)
			break ;
		if (bounces == 0)
			sample_direct_once(data, ray, pxl, &throughput);
		if (ray->hit_data->type == OBJ_LIGHT)
		{
			inc = ray->hit_data->colour;
			contrib = multiply_colours(inc, throughput);
			pxl->colour_sum = colour_add(pxl->colour_sum, contrib);
			break ;
		}
		throughput = multiply_colours(throughput, ray->hit_data->obj_colour);
		ray->origin = ray->hit_data->location;
		bounces++;
	}
}

static void	prepare_ray(t_data *d, t_ray *r, uint32_t y, uint32_t x)
{
	t_pixel	*pxl;

	pxl = &d->pixels[y][x];
	r->hit_data->is_shiny = is_shiny(r->rng, (*pxl).shininess);
	r->direction = (*pxl).ray_direction;
	r->hit_data->specular = (*pxl).specular;
	r->hit_data->colour = lerp_colour((*pxl).obj_colour,
		new_colour(1.0f, 1.0f, 1.0f), r->hit_data->is_shiny);
	r->origin = (*pxl).location;
	r->hit_data->surface_norm = (*pxl).surface_norm;
	r->hit_data->inside_obj = false;
	r->hit_data->type = OBJ_NONE;
}

void	trace_paths(t_data *data, t_ray *ray, uint32_t y, uint32_t x)
{
	t_pixel	*pxl;
	int		rays;

	pxl = &data->pixels[y][x];
	pxl->colour_sum = new_colour(0.0f, 0.0f, 0.0f);
	rays = 0;
	while (rays < data->max_rays)
	{
		prepare_ray(data, ray, y, x);
		process_bounces(data, ray, pxl);
		rays++;
	}
	pxl->final_colour = colour_scale(pxl->colour_sum,
		1.0f / (float)(MAX_RAYS));
	gamma_adjust(&pxl->final_colour);
	pxl->final_colour = combine_colours(pxl->final_colour, pxl->ambient);
}
