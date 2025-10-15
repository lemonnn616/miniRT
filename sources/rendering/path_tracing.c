/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:26:40 by natallia          #+#    #+#             */
/*   Updated: 2025/10/03 12:21:30 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_shiny(t_pcg *rng, float shininess)
{
	float	random;

	random = pcg_random_float(rng);
	if (random <= shininess)
		return (true);
	return (false);
}

static inline void offset_ray_origin(const t_vec3 p, const t_vec3 n, t_vec3 *origin_out)
{
	/* Small push along the normal to avoid self-intersections */
	const float eps = 2e-3f;
	*origin_out = vec_add(p, vec_scale(n, eps));
}

// t_color	sample_direct_light(t_data *data, t_hit *hit)
// {
// 	t_light	*light;
// 	t_vec3	to_light;
// 	t_ray	shadow;
// 	t_hit	sh;
// 	float	dist;

// 	light = data->scene.lights;
// 	if (!light)
// 		return (new_colour(0.0f, 0.0f, 0.0f));
// 	to_light = vec_subtract(light->pos, hit->location);
// 	dist = vec_length(to_light);
// 	if (dist <= 0.0f)
// 		return (new_colour(0.0f, 0.0f, 0.0f));
// 	to_light = vec_scale(to_light, 1.0f / dist);

// 	if (vec_dot(hit->surface_norm, to_light) <= 0.0f)
// 		return (new_colour(0.0f, 0.0f, 0.0f));
// 	shadow.direction = to_light;
// 	shadow.hit_data = &sh;
// 	ft_memset(&sh, 0, sizeof(sh));
// 	offset_ray_origin(hit->location, hit->surface_norm, &shadow.origin);
// 	find_closest_object(data, &shadow, &sh);
// 	if (sh.hit_occurred && sh.type != OBJ_LIGHT && sh.distance < dist)
// 		return (new_colour(0.0f, 0.0f, 0.0f));
// 	return colour_scale(multiply_colours(light->color, hit->obj_colour),
// 		vec_dot(hit->surface_norm, to_light));
// }

/* Evaluate one light's direct contribution with a shadow test */
static t_color	eval_light_contrib(t_data *data, t_hit *hit, t_light *light)
{
	t_vec3	to_light;
	float	distance_to_light;
	float	n_dot_l;
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	t_color	contribution;

	to_light = vec_subtract(light->pos, hit->location);
	distance_to_light = vec_length(to_light);
	if (distance_to_light <= 0.0f)
		return (new_colour(0.0f, 0.0f, 0.0f));
	to_light = vec_scale(to_light, 1.0f / distance_to_light);
	n_dot_l = vec_dot(hit->surface_norm, to_light);
	if (n_dot_l <= 0.0f)
		return (new_colour(0.0f, 0.0f, 0.0f));
	shadow_ray.direction = to_light;
	shadow_ray.hit_data = &shadow_hit;
	ft_memset(&shadow_hit, 0, sizeof(shadow_hit));
	offset_ray_origin(hit->location, hit->surface_norm, &shadow_ray.origin);
	find_closest_object(data, &shadow_ray, &shadow_hit);
	if (shadow_hit.hit_occurred && shadow_hit.type != OBJ_LIGHT
		&& shadow_hit.distance < distance_to_light)
		return (new_colour(0.0f, 0.0f, 0.0f));
	contribution = multiply_colours(light->color, hit->obj_colour);
	return (colour_scale(contribution, n_dot_l));
}

/* Now supports multiple lights by summing each visible light's term */
t_color	sample_direct_light(t_data *data, t_hit *hit)
{
	t_light	*light;
	t_color	total;

	total = new_colour(0.0f, 0.0f, 0.0f);
	light = data->scene.lights;
	while (light)
	{
		total = colour_add(total, eval_light_contrib(data, hit, light));
		light = light->next;
	}
	return (total);
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
	t_vec3	incoming;
	t_vec3	diffuse_dir;
	t_vec3	specular_dir;
	t_vec3	blended;

	incoming = r->direction;
	diffuse_dir = cosine_weighted_hemisphere(r->rng, hit->surface_norm);
	if (hit->is_shiny == true)
	{
		specular_dir = vec_subtract(incoming, vec_scale(hit->surface_norm,
			2.0f * vec_dot(incoming, hit->surface_norm)));
		if (vec_dot(specular_dir, hit->surface_norm) <= 0.0f)
			specular_dir = vec_scale(specular_dir, -1.0f);
		blended = lerp_vec(diffuse_dir, specular_dir, hit->specular);
		r->direction = vec_normalize(blended);
	}
	else
		r->direction = diffuse_dir;
	offset_ray_origin(hit->location, hit->surface_norm, &r->origin);
	find_closest_object(d, r, hit);
	compute_surface_interaction(hit, r->direction);
}

static int	apply_russian_roulette(t_ray *ray, t_color *throughput, int bounces)
{
	float	p;
	float	r;
	float	colour_luminance;

	if (bounces < 2)
		return (1);
	colour_luminance = 0.2126f * (*throughput).r
		+ 0.7152f * (*throughput).g + 0.0722f * (*throughput).b;
	p = fminf(0.95f, fmaxf(0.05f, colour_luminance));
	r = pcg_random_float(ray->rng);
	if (r > p)
		return (0);
	*throughput = colour_scale(*throughput, 1.0f / p);
	return (1);
}

static int	accumulate_if_light(t_ray *ray, t_pixel *pxl, t_color *throughput)
{
	t_color	inc;
	t_color	contrib;

	if (ray->hit_data->type != OBJ_LIGHT)
		return (0);
	inc = ray->hit_data->colour;
	contrib = multiply_colours(inc, *throughput);
	pxl->colour_sum = colour_add(pxl->colour_sum, contrib);
	return (1);
}

static void	process_bounces(t_data *data, t_ray *ray, t_pixel *pxl)
{
	int		bounces;
	t_color	throughput;

	bounces = 0;
	throughput = new_colour(1.0f, 1.0f, 1.0f);
	while (bounces < data->max_bounces)
	{
		ft_memset(ray->hit_data, 0, sizeof(t_hit));
		find_closest_object(data, ray, ray->hit_data);
		compute_surface_interaction(ray->hit_data, ray->direction);
		if (ray->hit_data->hit_occurred == false)
			break ;
		if (bounces == 0 && ray->hit_data->type != OBJ_LIGHT)
			sample_direct_once(data, ray, pxl, &throughput);
		if (accumulate_if_light(ray, pxl, &throughput))
			break ;
		throughput = multiply_colours(throughput, ray->hit_data->obj_colour);
		if (!apply_russian_roulette(ray, &throughput, bounces))
			break ;
		ray->origin = ray->hit_data->location;
		bounce_ray(data, ray, ray->hit_data);
		if (ray->hit_data->hit_occurred == false)
			break ;
		bounces++;
	}
}

void	trace_paths(t_data *d, t_ray *ray, uint32_t y, uint32_t x)
{
	int		rays;
	t_pixel	*px;
	t_color	avg;

	rays = 0;
	px = &d->pixels[y][x];
	while (rays < d->max_rays)
	{
		ray->hit_data->is_shiny = is_shiny(ray->rng, (*px).shininess);
		ray->hit_data->specular = (*px).specular;
		ray->hit_data->colour = lerp_colour((*px).obj_colour,
			new_colour(1.0f, 1.0f, 1.0f), ray->hit_data->is_shiny);
		ray->origin = (*px).location;
		ray->direction = (*px).ray_direction;
		ray->hit_data->surface_norm = (*px).surface_norm;
		ray->hit_data->inside_obj = false;
		ray->hit_data->type = OBJ_NONE;
		process_bounces(d, ray, px);
		rays++;
	}
	px->spp += d->max_rays;
	avg = colour_scale(px->colour_sum, 1.0f / (float)px->spp);
	gamma_adjust(&avg);
	px->final_colour = combine_colours(avg, px->ambient);
}
