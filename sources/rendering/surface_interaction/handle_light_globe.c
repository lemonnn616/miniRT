/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_light_globe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:45:02 by natallia          #+#    #+#             */
/*   Updated: 2025/11/03 15:32:28 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_light_globe_interaction(t_hit *hit, t_vec3 ray_direction)
{
	t_light	*l;
	t_color	emission;
	float	ndotv;
	float	brightness;

	l = (t_light *)hit->obj_ptr;
	hit->surface_norm = vec_normalize(vec_subtract(hit->location, l->pos));
	if (hit->inside_obj == true)
		hit->surface_norm = vec_scale(hit->surface_norm, -1.0f);
	ndotv = vec_dot(ray_direction, vec_scale(hit->surface_norm, -1.0f));
	if (ndotv < 0.0f)
		ndotv = 0.0f;
	brightness = 0.1f + 0.9f * ndotv;
	emission = colour_scale(l->color, l->intensity * brightness);
	hit->colour = emission;
	hit->obj_colour = emission;
}
