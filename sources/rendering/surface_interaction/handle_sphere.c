/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:48:32 by natallia          #+#    #+#             */
/*   Updated: 2025/05/15 18:23:34 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_sphere_surface_interaction(t_hit *hit)
{
	t_sphere	*s;

	s = (t_sphere *)hit->obj_ptr;
	hit->surface_norm = vec_normalize(vec_subtract(hit->location, s->center));
	if (hit->inside_obj == true)
		hit->surface_norm = vec_scale(hit->surface_norm, -1.0f);
	if (hit->reflection_ray == false)
		hit->colour = tint_reflected_light(hit->obj_colour, hit->colour);
}
