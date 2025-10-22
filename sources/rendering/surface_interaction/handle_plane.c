/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:48:51 by natallia          #+#    #+#             */
/*   Updated: 2025/10/22 17:45:10 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_plane_surface_interaction(t_hit *hit)
{
	t_plane *p = (t_plane *)hit->obj_ptr;

	hit->surface_norm = vec_normalize(p->normal);
	if (hit->inside_obj)
		hit->surface_norm = vec_scale(hit->surface_norm, -1.0f);
	if (p->use_checker)
	{
		t_vec3 rel = vec_subtract(hit->location, p->point);
		float u = vec_dot(rel, p->u_axis);
		float v = vec_dot(rel, p->v_axis);
		int iu = (int)floorf(u / p->checker_size);
		int iv = (int)floorf(v / p->checker_size);
		bool odd = ((iu + iv) & 1);
		t_color base = p->mat.color;
		t_color alt  = p->checker_alt;
		hit->obj_colour = odd ? alt : base;
	}
	else
		hit->obj_colour = p->mat.color;
}
