/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:47:49 by natallia          #+#    #+#             */
/*   Updated: 2025/11/09 20:00:40 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_cone_normal(t_hit *hit, t_cone *c)
{
	t_vec3	apex_to_point;
	t_vec3	axis_projection;
	t_vec3	radius_projection;
	t_vec3	surface_normal;
	float	half;

	apex_to_point = vec_subtract(hit->location, c->apex);
	axis_projection = vec_scale(c->axis, vec_dot(apex_to_point, c->axis));
	radius_projection = vec_subtract(apex_to_point, axis_projection);
	if (vec_dot(radius_projection, radius_projection) < 1e-8f)
		surface_normal = c->axis;
	else
	{
		half = degree_to_radian(c->angle) * 0.5f;
		surface_normal = vec_add(vec_scale(radius_projection, cosf(half)),
				vec_scale(c->axis, sinf(half)));
	}
	surface_normal = vec_normalize(surface_normal);
	if (hit->inside_obj)
		surface_normal = vec_scale(surface_normal, -1.0f);
	return (surface_normal);
}

void	handle_cone_surface_interaction(t_hit *hit)
{
	t_cone	*c;

	c = (t_cone *)hit->obj_ptr;
	if (hit->caps == false)
	{
		hit->surface_norm = get_cone_normal(hit, c);
		if (hit->inside_obj == true)
			hit->surface_norm = vec_scale(hit->surface_norm, -1.0f);
	}
}
