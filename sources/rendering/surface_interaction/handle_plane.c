/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:48:51 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 12:34:40 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	handle_plane_surface_interaction(t_hit *hit)
{
	t_plane	*p;
	int		sum;

	p = (t_plane *)hit->obj_ptr;
	hit->surface_norm = vec_normalize(p->normal);
	if (hit->inside_obj)
		hit->surface_norm = vec_scale(hit->surface_norm, -1.0f);
	if (!p->use_checker)
	{
		hit->obj_color = p->mat.color;
		return ;
	}
	sum = (int)floorf(vec_dot(vec_subtract(hit->location, p->point), p->u_axis)
			/ p->checker_size)
		+ (int)floorf(vec_dot(vec_subtract(hit->location, p->point), p->v_axis)
			/ p->checker_size);
	if ((sum & 1) != 0)
		hit->obj_color = p->checker_alt;
	else
		hit->obj_color = p->mat.color;
}
