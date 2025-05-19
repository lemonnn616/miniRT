/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_light_globe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:45:02 by natallia          #+#    #+#             */
/*   Updated: 2025/05/16 09:46:19 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_light_globe_interaction(t_hit *hit, t_vec3 ray_direction)
{
	t_light	*l;
	t_color	c;
	float	brightness;

	l = (t_light *)hit->obj_ptr;
	c = l->color;
	hit->surface_norm = vec_normalize(vec_subtract(hit->location, l->pos));
	if (hit->inside_obj == true)
		hit->surface_norm = vec_scale(hit->surface_norm, -1.0f);
	brightness = vec_dot(ray_direction, vec_scale(hit->surface_norm, -1.0f));
	if (brightness < 0.1f)
		brightness = 0.1f;
	hit->colour = colour_scale(c, brightness);
}
