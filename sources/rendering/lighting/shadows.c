/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:39:04 by natallia          #+#    #+#             */
/*   Updated: 2025/11/09 22:39:21 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_in_shadow(t_data *d, t_hit *hit, t_vec3 light_dir, float dist)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;

	shadow_ray.direction = light_dir;
	shadow_ray.hit_data = &shadow_hit;
	ft_memset(&shadow_hit, 0, sizeof(t_hit));
	offset_ray_origin(hit->location, hit->surface_norm, &shadow_ray.origin);
	find_closest_object(d, &shadow_ray, &shadow_hit);
	if (shadow_hit.hit_occurred
		&& shadow_hit.type != OBJ_LIGHT
		&& shadow_hit.distance > 1e-3f
		&& shadow_hit.distance < dist)
		return (true);
	return (false);
}
