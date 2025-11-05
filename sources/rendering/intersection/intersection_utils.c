/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:02:26 by natallia          #+#    #+#             */
/*   Updated: 2025/11/04 17:27:24 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	valid_intersection(float *low, float *high)
{
	float	temp;

	if (*high <= EPSILON)
		return (false);
	else if (*low <= 0 && *high > 0)
	{
		temp = *low;
		*low = *high;
		*high = temp;
	}
	return (true);
}

void	update_hit(t_ray *ray, float distance, t_object *obj)
{
	ft_memset(ray->hit_data, 0, sizeof(t_hit));
	ray->hit_data->hit_occurred = true;
	ray->hit_data->distance = distance;
	ray->hit_data->type = obj->type;
	ray->hit_data->obj_ptr = obj->obj;
	ray->hit_data->location = vec_add(ray->origin,
			vec_scale(ray->direction, distance));
}

void	update_orientation(t_hit *hit, t_vec3 normal, float denominator)
{
	if (denominator > 0)
		hit->surface_norm = vec_scale(normal, -1);
	else
		hit->surface_norm = normal;
}
