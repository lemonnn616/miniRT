/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:05:44 by natallia          #+#    #+#             */
/*   Updated: 2025/11/04 17:27:08 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_plane(t_hit *hit, t_ray *ray, t_object *obj)
{
	t_plane	*p;
	t_vec3	op;
	float	denominator;
	float	distance;

	p = obj->obj;
	denominator = vec_dot(ray->direction, p->normal);
	if (fabs(denominator) < EPSILON)
		return ;
	op = vec_subtract(ray->origin, p->point);
	distance = -vec_dot(op, p->normal) / denominator;
	if (distance > 0.0f && distance < hit->distance)
	{
		update_hit(ray, distance, obj);
		hit->specular = p->mat.specular;
		hit->shininess = p->mat.shininess;
		hit->reflectivity = p->mat.reflectivity;
		hit->obj_colour = p->mat.color;
		if (denominator > 0)
			hit->surface_norm = vec_scale(p->normal, -1);
		else
			hit->surface_norm = p->normal;
	}
}
