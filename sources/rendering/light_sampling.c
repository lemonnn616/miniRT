/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_sampling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:40:16 by natallia          #+#    #+#             */
/*   Updated: 2025/10/17 16:17:06 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	compute_specular(t_light *l, t_hit *h,
	t_vec3 view_dir, t_vec3 light_dir)
{
	t_vec3	half_vector;
	float	spec_angle;
	float	spec_power;
	float	spec_strength;
	t_color	specular;

	view_dir = vec_normalize(view_dir);
	half_vector = vec_normalize(vec_add(view_dir, light_dir));
	spec_angle = vec_dot(h->surface_norm, half_vector);
	if (spec_angle < 0.0f)
		spec_angle = 0.0f;
	spec_power = 8.0f + h->shininess * h->shininess * 1016.0f;
	spec_strength = fmaxf(h->specular, 0.04f);
	specular = colour_scale(l->color,
		l->intensity * spec_strength * powf(spec_angle, spec_power));
	return (specular);
}

static t_color	compute_diffuse(t_light *l, t_hit *h, float n_dot_l)
{
	t_color	diffuse;
	float	ks;
	float	kd;

	ks = fmaxf(h->specular, 0.04f);
	kd = 1.0f - ks;
	diffuse = multiply_colours(l->color, h->obj_colour);
	diffuse = colour_scale(diffuse, l->intensity * n_dot_l * kd);
	return (diffuse);
}

static bool	is_in_shadow(t_data *d, t_hit *hit, t_vec3 light_dir, float dist)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;

	shadow_ray.direction = light_dir;
	shadow_ray.hit_data = &shadow_hit;
	ft_memset(&shadow_hit, 0, sizeof(t_hit));
	offset_ray_origin(hit->location, hit->surface_norm, &shadow_ray.origin);
	find_closest_object(d, &shadow_ray, &shadow_hit);
	if (shadow_hit.hit_occurred
		&& shadow_hit.type != OBJ_LIGHT
		&& shadow_hit.distance > 1e-3f
		&& shadow_hit.distance < dist)
		return (true);
	return (false);
}

static t_color	eval_light_contrib(t_data *d, t_hit *hit,
	t_light *l, t_vec3 view_dir)
{
	float	dist;
	float	n_dot_l;
	t_vec3	light_dir;
	t_color	diffuse;
	t_color	spec;

	dist = vec_length(vec_subtract(l->pos, hit->location));
	if (dist <= 0.0f)
		return (new_colour(0.0f, 0.0f, 0.0f));
	light_dir = vec_scale(vec_subtract(l->pos, hit->location), 1.0f / dist);
	n_dot_l = vec_dot(hit->surface_norm, light_dir);
	if (n_dot_l <= 0.0f)
		return (new_colour(0.0f, 0.0f, 0.0f));
	if (is_in_shadow(d, hit, light_dir, dist))
		return (new_colour(0.0f, 0.0f, 0.0f));
	diffuse = compute_diffuse(l, hit, n_dot_l);
	spec = compute_specular(l, hit, view_dir, light_dir);
	return (colour_add(diffuse, spec));
}

t_color	sample_direct_lights(t_data *data, t_hit *hit, t_vec3 view_dir)
{
	t_light	*light;
	t_color	total;

	light = data->scene.lights;
	total = new_colour(0.0f, 0.0f, 0.0f);
	while (light)
	{
		total = colour_add(total,
			eval_light_contrib(data, hit, light, view_dir));
		light = light->next;
	}
	return (total);
}
