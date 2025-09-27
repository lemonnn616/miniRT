/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:01:20 by natallia          #+#    #+#             */
/*   Updated: 2025/07/23 13:25:52 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_within_cylinder_height(t_ray *ray, t_cylinder *c, float root)
{
	t_vec3	hit_point;
	t_vec3	point_to_center;
	float	height_projection;

	hit_point = vec_add(ray->origin, vec_scale(ray->direction, root));
	point_to_center = vec_subtract(hit_point, c->base);
	height_projection = vec_dot(point_to_center, c->axis);
	if (fabs(height_projection) <= c->height / 2)
		return (true);
	return (false);
}

bool	is_within_circular_area(t_ray *ray, float radius,
	t_vec3 top_center, float distance)
{
	t_vec3	hit_point;
	float	length;

	hit_point = vec_add(ray->origin, vec_scale(ray->direction, distance));
	length = vec_distance(hit_point, top_center);
	if (length <= radius)
		return (true);
	return (false);
}
