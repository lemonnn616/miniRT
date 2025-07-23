/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:48:51 by natallia          #+#    #+#             */
/*   Updated: 2025/07/23 13:24:29 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_plane_surface_interaction(t_hit *hit)
{
	t_plane *p = (t_plane *)hit->obj_ptr;

	hit->surface_norm = vec_normalize(p->normal);
	if (hit->inside_obj)
		hit->surface_norm = vec_scale(hit->surface_norm, -1.0f);
}
