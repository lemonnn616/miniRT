/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:06:21 by natallia          #+#    #+#             */
/*   Updated: 2025/05/15 15:02:45 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	is_within_cone_height(t_ray *ray, t_cone *c, float root)
{
	t_vec3	hit_point;
	t_vec3	apex_to_point;
	float	height_projection;

	hit_point = vec_add(ray->origin, vec_scale(ray->direction, root));
	apex_to_point = vec_subtract(hit_point, c->apex);
	height_projection = vec_dot(apex_to_point, c->axis);
	if (height_projection >= 0 && height_projection <= c->height)
		return (true);
	return (false);
}

static	t_vec3	get_cone_coefficients(t_ray *ray, t_cone *c)
{
	t_vec3	d;
	t_vec3	v;
	t_vec3	quad_coeff;
	t_vec3	origin_to_apex;
	float	cos_theta_squared;

	d = ray->direction;
	v = c->axis;
	origin_to_apex = vec_subtract(ray->origin, c->apex);
	cos_theta_squared = cosf(c->angle / 2) * cosf(c->angle / 2);
	quad_coeff.x = vec_dot(d, v) * vec_dot(d, v)
		- vec_dot(d, d) * cos_theta_squared;
	quad_coeff.y = 2 * (vec_dot(origin_to_apex, v) * vec_dot(d, v)
		- vec_dot(origin_to_apex, d) * cos_theta_squared);
	quad_coeff.z = vec_dot(origin_to_apex, v) * vec_dot(origin_to_apex, v)
		- vec_dot(origin_to_apex, origin_to_apex) * cos_theta_squared;
	return (quad_coeff);
}

static void	intersect_body(t_hit *hit, t_ray *ray, t_object *obj, float *roots)
{
	t_cone	*c;
	t_vec3	quad_coeff;

	c = obj->obj;
	quad_coeff = get_cone_coefficients(ray, c);
	if (quadratic_equation(quad_coeff, roots) == true
		&& valid_intersection(&roots[0], &roots[1]) == true
		&& roots[0] < hit->distance
		&& is_within_cone_height(ray, c, roots[0]))
	{
		update_hit(ray, roots[0], obj);
		hit->caps = false;
	}
}

static void	intersect_base(t_hit *hit, t_ray *ray,
	t_object *obj, float *base_hit)
{
	t_cone	*c;
	t_vec3	base_center;
	t_vec3	origin_to_base;
	float	denominator;
	float	distance;

	c = obj->obj;
	base_center = vec_add(c->apex,
			vec_scale(vec_scale(c->axis, -1), c->height));
	denominator = vec_dot(ray->direction, c->axis);
	if (fabs(denominator) < EPSILON)
		return ;
	origin_to_base = vec_subtract(ray->origin, base_center);
	distance = - vec_dot(origin_to_base, c->axis) / denominator;
	if (is_within_circular_area(ray,
		c->height * tan(c->angle / 2), c->axis, distance))
	{
		*base_hit = distance;
		if (distance > 0 && distance < hit->distance)
		{
			update_hit(ray, distance, obj);
			update_orientation(hit, c->axis, denominator);
			hit->caps = true;
		}
	}
}

void	intersect_cone(t_hit *hit, t_ray *ray, t_object *obj)
{
	t_cone	*c;
	float	base_hit;
	float	body_hits[2];

	c = obj->obj;
	base_hit = 0.0f;
	ft_memset(body_hits, 0, 2 * sizeof(float));
	intersect_base(hit, ray, obj, &base_hit);
	intersect_body(hit, ray, obj, body_hits);
	if ((t_cone *)ray->hit_data->obj_ptr == c)
	{
		hit->specular = c->mat.specular;
		hit->shininess = c->mat.shininess;
		hit->obj_colour = c->mat.color;
		if (base_hit < 0 || body_hits[0] < 0 || body_hits[1] < 0)
			hit->inside_obj = true;
		else
			hit->inside_obj = false;
	}
}
