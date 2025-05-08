/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:06:03 by natallia          #+#    #+#             */
/*   Updated: 2025/05/08 11:29:35 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	intersect_top_cap(t_hit *hit, t_ray *ray,
	t_object *obj, float *top_hit)
{
	t_cylinder	*c;
	t_vec3		top_center;
	t_vec3		origin_to_top;
	float		denominator;
	float		distance;

	c = obj->obj;
	top_center = vec_add(c->base, vec_scale(c->axis, c->height / 2.0f));
	denominator = vec_dot(ray->direction, c->axis);
	if (fabs(denominator) < EPSILON)
		return ;
	origin_to_top = vec_subtract(ray->origin, top_center);
	distance = - vec_dot(origin_to_top, c->axis) / denominator;
	if (is_within_circular_area(ray, c->radius, top_center, distance))
	{
		*top_hit = distance;
		if (distance > 0 && distance < hit->distance)
		{
			update_hit(ray, distance, obj);
			update_orientation(hit, c->axis, denominator);
			hit->caps = true;
		}
	}
}

static void	intersect_bottom_cap(t_hit *hit, t_ray *ray,
	t_object *obj, float *bottom_hit)
{
	t_cylinder	*c;
	t_vec3		bottom_center;
	t_vec3		origin_to_bottom;
	float		denominator;
	float		distance;

	c = obj->obj;
	bottom_center = vec_subtract(c->base,
		vec_scale(c->axis, c->height / 2.0f));
	denominator = vec_dot(ray->direction, c->axis);
	if (fabs(denominator) < EPSILON)
		return ;
	origin_to_bottom = vec_subtract(ray->origin, bottom_center);
	distance = - vec_dot(origin_to_bottom, c->axis) / denominator;
	if (is_within_circular_area(ray, c->radius, bottom_center, distance))
	{
		*bottom_hit = distance;
		if (distance > 0 && distance < hit->distance)
		{
			update_hit(ray, distance, obj);
			update_orientation(hit, c->axis, denominator);
			hit->caps = true;
		}
	}
}

static void	intersect_body(t_hit *hit, t_ray *ray, t_object *obj, float *roots)
{
	t_cylinder	*c;
	t_vec3		origin_to_center;
	t_vec3		ray_axis_skew;
	t_vec3		origin_axis_offset;
	t_vec3		quad_coeff;

	c = obj->obj;
	origin_to_center = vec_subtract(ray->origin, c->base);
	ray_axis_skew = vec_cross(c->axis, ray->direction);
	origin_axis_offset = vec_cross(c->axis, origin_to_center);
	quad_coeff.x = vec_dot(ray_axis_skew, ray_axis_skew);
	quad_coeff.y = 2.0f * vec_dot(ray_axis_skew, origin_axis_offset);
	quad_coeff.z = vec_dot(origin_axis_offset, origin_axis_offset)
		- c->radius * c->radius;
	if (quadratic_equation(quad_coeff, roots) == true
		&& valid_intersection(&roots[0], &roots[1]) == true
		&& roots[0] < hit->distance
		&& is_within_cylinder_height(ray, c, roots[0]))
	{
		update_hit(ray, roots[0], obj);
		hit->caps = false;
	}
}

void	intersect_cylinder(t_hit *hit, t_ray *ray, t_object *obj)
{
	t_cylinder	*c;
	float		top_hit;
	float		bottom_hit;
	float		body_hits[2];

	c = obj->obj;
	top_hit = 0;
	bottom_hit = 0;
	ft_memset(body_hits, 0, 2 * sizeof(float));
	intersect_body(hit, ray, obj, body_hits);
	intersect_top_cap(hit, ray, obj, &top_hit);
	intersect_bottom_cap(hit, ray, obj, &bottom_hit);
	if ((t_cylinder *)ray->hit_data->obj_ptr == c)
	{
		hit->specular = c->mat.specular;
		hit->shininess = c->mat.shininess;
		hit->obj_colour = c->mat.color;
		if (top_hit < 0 || bottom_hit < 0
			|| body_hits[0] < 0 || body_hits[1] < 0)
				hit->inside_obj = true;
		else
			hit->inside_obj = false;
	}

}
