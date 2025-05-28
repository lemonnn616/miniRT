/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_surface_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:50:21 by natallia          #+#    #+#             */
/*   Updated: 2025/05/16 09:48:00 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	compute_surface_interaction(t_hit *hit, t_vec3 ray_direction)
{
	if (hit->hit_occurred == false)
	{
		hit->colour = new_colour(0.5f, 0.7f, 1.0f);
		return ;
	}
	if (hit->type == OBJ_SPHERE)
		handle_sphere_surface_interaction(hit);
	else if (hit->type == OBJ_PLANE)
		handle_plane_surface_interaction(hit);
	else if (hit->type == OBJ_CYLINDER)
		handle_cylinder_surface_interaction(hit);
	else if (hit->type == OBJ_CONE)
		handle_cone_surface_interaction(hit);
	else if (hit->type == OBJ_LIGHT)
		handle_light_globe_interaction(hit, ray_direction);
	hit->location = vec_add(hit->location, vec_scale(hit->surface_norm, OFFSET));
}
