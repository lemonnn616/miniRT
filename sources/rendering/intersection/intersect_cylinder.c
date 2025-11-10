/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:06:03 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 12:26:45 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	intersect_top_cap(t_hit *hit, t_ray *ray,
	t_object *obj, float *top_hit)
{
	t_cylinder	*c;
	t_vec3		top_center;
	t_vec3		origin_to_top;
	float		denominator;
	float		distance;

	c = (t_cylinder *)obj->obj;
	top_center = vec_add(c->base, vec_scale(c->axis, c->height / 2.0f));
	denominator = vec_dot(ray->direction, c->axis);
	if (fabs(denominator) < EPSILON)
		return ;
	origin_to_top = vec_subtract(ray->origin, top_center);
	distance = -vec_dot(origin_to_top, c->axis) / denominator;
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

	c = (t_cylinder *)obj->obj;
	bottom_center = vec_subtract(c->base,
			vec_scale(c->axis, c->height / 2.0f));
	denominator = vec_dot(ray->direction, c->axis);
	if (fabs(denominator) < EPSILON)
		return ;
	origin_to_bottom = vec_subtract(ray->origin, bottom_center);
	distance = -vec_dot(origin_to_bottom, c->axis) / denominator;
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

	c = (t_cylinder *)obj->obj;
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
	float		top;
	float		bottom;
	float		body[2];

	c = (t_cylinder *)obj->obj;
	top = 0.0f;
	bottom = 0.0f;
	ft_memset(body, 0, sizeof(body));
	intersect_body(hit, ray, obj, body);
	intersect_top_cap(hit, ray, obj, &top);
	intersect_bottom_cap(hit, ray, obj, &bottom);
	if ((t_cylinder *)ray->hit_data->obj_ptr != c)
		return ;
	hit->obj_color = c->mat.color;
	hit->reflectivity = fminf(1.0f, fmaxf(0.0f, c->mat.reflectivity));
	hit->shininess = fminf(1.0f, fmaxf(0.0f, c->mat.shininess));
	if (c->mat.specular <= 0.0f)
		hit->specular = hit->reflectivity;
	else
		hit->specular = fminf(1.0f, c->mat.specular);
	if (top < 0.0f || bottom < 0.0f || body[0] < 0.0f || body[1] < 0.0f)
		hit->inside_obj = true;
	else
		hit->inside_obj = false;
}
