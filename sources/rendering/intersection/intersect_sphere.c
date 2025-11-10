/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:05:20 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 12:28:14 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	intersect_sphere(t_hit *hit, t_ray *ray, t_object *obj)
{
	t_sphere	*s;
	t_vec3		oc;
	t_vec3		quad_coeff;
	float		roots[2];

	s = (t_sphere *)obj->obj;
	oc = vec_subtract(ray->origin, s->center);
	quad_coeff.x = vec_dot(ray->direction, ray->direction);
	quad_coeff.y = 2.0f * vec_dot(oc, ray->direction);
	quad_coeff.z = vec_dot(oc, oc) - s->radius * s->radius;
	if (quadratic_equation(quad_coeff, roots) == true
		&& valid_intersection(&roots[0], &roots[1]) == true
		&& roots[0] < hit->distance)
	{
		update_hit(ray, roots[0], obj);
		hit->obj_color = s->mat.color;
		hit->reflectivity = fminf(1.0f, fmaxf(0.0f, s->mat.reflectivity));
		hit->shininess = fminf(1.0f, fmaxf(0.0f, s->mat.shininess));
		if (s->mat.specular > 0.0f)
			hit->specular = fminf(1.0f, s->mat.specular);
		else
			hit->specular = hit->reflectivity;
		if (roots[1] <= 0.0f)
			hit->inside_obj = true;
	}
}
