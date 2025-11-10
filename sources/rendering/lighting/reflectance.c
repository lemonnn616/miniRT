/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflectance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:25:26 by natallia          #+#    #+#             */
/*   Updated: 2025/11/09 22:35:40 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	random_is_specular(t_pcg *rng, float reflectivity)
{
	float	p;

	p = pcg_random_float(rng);
	if (p <= reflectivity)
		return (true);
	return (false);
}

t_color	compute_specular(t_light *l, t_hit *h, t_vec3 view_dir, t_vec3 l_dir)
{
	t_vec3	half_vector;
	float	spec_angle;
	float	spec_power;
	float	spec_strength;
	t_color	specular;

	view_dir = vec_normalize(view_dir);
	half_vector = vec_normalize(vec_add(view_dir, l_dir));
	spec_angle = vec_dot(h->surface_norm, half_vector);
	if (spec_angle < 0.0f)
		spec_angle = 0.0f;
	spec_power = 8.0f + h->shininess * h->shininess * 1016.0f;
	spec_strength = fmaxf(h->reflectivity, 0.04f);
	specular = colour_scale(l->color,
			l->intensity * spec_strength * powf(spec_angle, spec_power));
	return (specular);
}

t_color	compute_diffuse(t_light *l, t_hit *h, float n_dot_l)
{
	t_color	diffuse;
	float	ks;
	float	kd;

	ks = fminf(1.0f, fmaxf(0.0f, h->reflectivity));
	kd = 1.0f - ks;
	diffuse = multiply_colours(l->color, h->obj_colour);
	diffuse = colour_scale(diffuse, l->intensity * n_dot_l * kd);
	return (diffuse);
}
