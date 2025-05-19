/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:05:20 by natallia          #+#    #+#             */
/*   Updated: 2025/05/02 12:09:38 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_sphere(t_hit *hit, t_ray *ray, t_object *obj)
{
	t_sphere	*s;
	t_vec3		oc;
	t_vec3		quad_coeff;
	float		roots[2];

	s = obj->obj;
	oc = vec_subtract(ray->origin, s->center);
	quad_coeff.x = vec_dot(ray->direction, ray->direction);
	quad_coeff.y = 2.0f * vec_dot(oc, ray->direction);
	quad_coeff.z = vec_dot(oc, oc) - s->radius * s->radius;
	if (quadratic_equation(quad_coeff, roots) == true
		&& valid_intersection(&roots[0], &roots[1]) == true
		&& roots[0] < hit->distance)
	{
		update_hit(ray, roots[0], obj);
		hit->specular = s->mat.specular;
		hit->shininess = s->mat.shininess;
		hit->obj_colour = s->mat.color;
		if (roots[1] <= 0.0f)
			hit->inside_obj = true;
	}
}
