/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:26:40 by natallia          #+#    #+#             */
/*   Updated: 2025/10/17 16:22:14 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static bool	apply_russian_roulette(t_ray *r, t_color *throughput, int bounces)
{
	float	path_luminance;
	float	survival_prob;
	float	random_value;

	if (bounces < 2)
		return (true);
	path_luminance = 0.2126f * (*throughput).r
		+ 0.7152f * (*throughput).g
		+ 0.0722f * (*throughput).b;
	survival_prob = fminf(0.95f, fmaxf(0.05f, path_luminance));
	random_value = pcg_random_float(r->rng);
	if (random_value > survival_prob)
		return (false);
	*throughput = colour_scale(*throughput, 1.0f / survival_prob);
	return (true);
}

static bool	accumulate_emission(t_ray *ray, t_pixel *pxl, t_color *throughput)
{
	t_color	inc;
	t_color	contrib;

	if (ray->hit_data->type != OBJ_LIGHT)
		return (false);
	inc = ray->hit_data->colour;
	contrib = multiply_colours(inc, *throughput);
	pxl->colour_sum = colour_add(pxl->colour_sum, contrib);
	return (true);
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
			integrate_direct_lighting(data, ray, pxl, &throughput);
		if (accumulate_emission(ray, pxl, &throughput))
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

void	trace_paths(t_data *d, t_ray *r, uint32_t y, uint32_t x)
{
	int		rays;
	t_pixel	*px;
	t_color	avg;

	rays = 0;
	px = &d->pixels[y][x];
	while (rays < d->max_rays)
	{
		r->hit_data->is_shiny = random_is_specular(r->rng, (*px).shininess);
		r->hit_data->specular = (*px).specular;
		r->hit_data->colour = lerp_colour((*px).obj_colour,
			new_colour(1.0f, 1.0f, 1.0f), r->hit_data->is_shiny);
		r->origin = (*px).location;
		r->direction = (*px).ray_direction;
		r->hit_data->surface_norm = (*px).surface_norm;
		r->hit_data->inside_obj = false;
		r->hit_data->type = OBJ_NONE;
		offset_ray_origin(r->origin, r->hit_data->surface_norm, &r->origin);
		process_bounces(d, r, px);
		rays++;
	}
	px->spp += d->max_rays;
	avg = colour_scale(px->colour_sum, 1.0f / (float)px->spp);
	gamma_adjust(&avg);
	px->final_colour = combine_colours(avg, px->ambient);
}
