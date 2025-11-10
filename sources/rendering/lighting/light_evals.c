/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_evals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:40:16 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 12:33:18 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "light.h"

static t_vec3	random_on_sphere(t_vec3 c, float r, t_pcg *rng)
{
	t_vec3	dir;

	dir = generate_random_ray(rng);
	return (vec_add(c, vec_scale(dir, r)));
}

t_color	eval_point_light(t_data *d, t_hit *h, t_light *l, t_vec3 view_dir)
{
	float	distance_to_light;
	float	ndotl;
	t_vec3	light_dir;
	t_color	diff_term;
	t_color	spec_term;

	distance_to_light = vec_length(vec_subtract(l->pos, h->location));
	if (distance_to_light <= 0.0f)
		return (new_color(0, 0, 0));
	light_dir = vec_scale(vec_subtract(l->pos, h->location),
			1.0f / distance_to_light);
	ndotl = vec_dot(h->surface_norm, light_dir);
	if (ndotl <= 0.0f)
		return (new_color(0, 0, 0));
	if (is_in_shadow(d, h, light_dir, distance_to_light))
		return (new_color(0, 0, 0));
	diff_term = compute_diffuse(l, h, ndotl);
	spec_term = compute_specular(l, h, view_dir, light_dir);
	return (color_add(diff_term, spec_term));
}

static t_color	eval_area_once(t_dlctx *c, t_light *l)
{
	t_vec3	to_sample;
	t_vec3	light_dir;
	float	distance_to_sample;
	float	ndotl;
	t_color	sum;

	to_sample = vec_subtract(random_on_sphere(l->pos, GLOBE_RADIUS, c->rng),
			c->hit->location);
	distance_to_sample = vec_length(to_sample);
	if (distance_to_sample <= 0.0f)
		return (new_color(0, 0, 0));
	light_dir = vec_scale(to_sample, 1.0f / distance_to_sample);
	ndotl = vec_dot(c->hit->surface_norm, light_dir);
	if (ndotl <= 0.0f)
		return (new_color(0, 0, 0));
	if (is_in_shadow(c->data, c->hit, light_dir, distance_to_sample))
		return (new_color(0, 0, 0));
	sum = compute_diffuse(l, c->hit, ndotl);
	sum = color_add(sum,
			compute_specular(l, c->hit, c->view_dir, light_dir));
	return (sum);
}

t_color	eval_area_light(t_dlctx *c, t_light *l, int m)
{
	t_color	sum;
	int		i;

	sum = new_color(0, 0, 0);
	i = 0;
	while (i++ < m)
		sum = color_add(sum, eval_area_once(c, l));
	if (m > 1)
		sum = color_scale(sum, 1.0f / (float)m);
	return (sum);
}
