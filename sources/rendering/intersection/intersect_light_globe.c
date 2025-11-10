/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light_globe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:32:27 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 12:28:41 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "light.h"

void	intersect_light_globe(t_hit *hit, t_ray *ray, t_object *obj)
{
	t_light		*l;
	t_vec3		oc;
	t_vec3		quad_coeff;
	float		roots[2];

	l = (t_light *)obj->obj;
	oc = vec_subtract(ray->origin, l->pos);
	quad_coeff.x = vec_dot(ray->direction, ray->direction);
	quad_coeff.y = 2.0f * vec_dot(oc, ray->direction);
	quad_coeff.z = vec_dot(oc, oc) - GLOBE_RADIUS * GLOBE_RADIUS;
	if (quadratic_equation(quad_coeff, roots) == true
		&& valid_intersection(&roots[0], &roots[1]) == true
		&& roots[0] < hit->distance)
	{
		update_hit(ray, roots[0], obj);
		hit->obj_color = l->color;
		if (roots[1] <= 0.0f)
			hit->inside_obj = true;
	}
}
