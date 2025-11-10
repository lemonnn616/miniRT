/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:48:17 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 12:34:18 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static t_vec3	get_cylinder_normal(t_hit *hit, t_cylinder *c)
{
	t_vec3	center_to_point;
	t_vec3	axis_projection;
	t_vec3	surface_normal;

	center_to_point = vec_subtract(hit->location, c->base);
	axis_projection = vec_add(c->base, vec_scale(c->axis,
				vec_dot(center_to_point, c->axis)));
	surface_normal = vec_subtract(hit->location, axis_projection);
	return (vec_normalize(surface_normal));
}

void	handle_cylinder_surface_interaction(t_hit *hit)
{
	t_cylinder	*c;

	c = (t_cylinder *)hit->obj_ptr;
	if (hit->caps == false)
	{
		hit->surface_norm = get_cylinder_normal(hit, c);
		if (hit->inside_obj == true)
			hit->surface_norm = vec_scale(hit->surface_norm, -1.0f);
	}
}
