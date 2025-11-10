/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:05:44 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 12:28:02 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	apply_plane_material(t_hit *hit, t_plane *p)
{
	hit->obj_color = p->mat.color;
	hit->reflectivity = fminf(1.0f, fmaxf(0.0f, p->mat.reflectivity));
	hit->shininess = fminf(1.0f, fmaxf(0.0f, p->mat.shininess));
	if (p->mat.specular > 0.0f)
		hit->specular = fminf(1.0f, p->mat.specular);
	else
		hit->specular = hit->reflectivity;
}

void	intersect_plane(t_hit *hit, t_ray *ray, t_object *obj)
{
	t_plane	*p;
	t_vec3	op;
	float	denominator;
	float	distance;

	p = (t_plane *)obj->obj;
	denominator = vec_dot(ray->direction, p->normal);
	if (fabsf(denominator) < EPSILON)
		return ;
	op = vec_subtract(ray->origin, p->point);
	distance = -vec_dot(op, p->normal) / denominator;
	if (distance > 0.0f && distance < hit->distance)
	{
		update_hit(ray, distance, obj);
		apply_plane_material(hit, p);
		if (denominator > 0.0f)
			hit->surface_norm = vec_scale(p->normal, -1.0f);
		else
			hit->surface_norm = p->normal;
	}
}
