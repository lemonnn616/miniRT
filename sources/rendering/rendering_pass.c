/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_pass.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:07:27 by natallia          #+#    #+#             */
/*   Updated: 2025/11/07 17:41:26 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <float.h>

void	offset_ray_origin(const t_vec3 p, const t_vec3 n, t_vec3 *origin_out)
{
	float	eps_n;
	float	eps_p;
	float	m;

	eps_n = 1e-3f;
	eps_p = 1e-4f;
	m = vec_length(p);
	*origin_out = vec_add(p, vec_scale(n, eps_n + eps_p * m));
}

void	update_ray(t_data *data, t_ray *ray, int32_t y, int32_t x)
{
	t_camera	*cam;
	t_vec3		vlocal;
	t_vec3		world;
	float		half_w;
	float		half_h;

	ft_memset(ray->hit_data, 0, sizeof(t_hit));
	cam = data->scene.active_cam;
	if (cam == NULL)
		cam = data->scene.cameras;
	ray->origin = cam->pos;
	half_w = tanf(degree_to_radian(cam->fov) * 0.5f);
	half_h = half_w * ((float)data->scene.height / (float)data->scene.width);
	vlocal.x = ((2.0f * (x + 0.5f)
				/ (float)data->scene.width) - 1.0f) * half_w;
	vlocal.y = (1.0f - (2.0f * (y + 0.5f)
				/ (float)data->scene.height)) * half_h;
	vlocal.z = 1.0f;
	world = vec_add(vec_add(vec_scale(cam->right, vlocal.x),
				vec_scale(cam->up, vlocal.y)), vec_scale(cam->dir, vlocal.z));
	ray->direction = vec_normalize(world);
	data->pixels[y][x].ray_direction = ray->direction;
	ray->hit_data->colour = new_colour(1.0f, 1.0f, 1.0f);
}

void	find_closest_object(t_data *data, t_ray *ray, t_hit *hit)
{
	t_object	*obj;

	obj = data->scene.objects;
	hit->hit_occurred = false;
	hit->type = OBJ_NONE;
	hit->distance = FLT_MAX;
	while (obj)
	{
		if (obj->type == OBJ_SPHERE)
			intersect_sphere(hit, ray, obj);
		else if (obj->type == OBJ_PLANE)
			intersect_plane(hit, ray, obj);
		else if (obj->type == OBJ_CYLINDER)
			intersect_cylinder(hit, ray, obj);
		else if (obj->type == OBJ_CONE)
			intersect_cone(hit, ray, obj);
		else if (obj->type == OBJ_LIGHT)
			intersect_light_globe(hit, ray, obj);
		obj = obj->next;
	}
}

void	get_first_hit(t_data *data, t_ray *ray, int32_t y, int32_t x)
{
	find_closest_object(data, ray, ray->hit_data);
	compute_surface_interaction(ray->hit_data, ray->direction);
	if (!ray->hit_data->hit_occurred)
		return ;
	if (ray->hit_data->type == OBJ_LIGHT)
	{
		data->pixels[y][x].final_colour = ray->hit_data->colour;
		gamma_adjust(&data->pixels[y][x].final_colour);
		return ;
	}
	data->pixels[y][x].obj_colour = ray->hit_data->obj_colour;
	data->pixels[y][x].specular = ray->hit_data->specular;
	data->pixels[y][x].shininess = ray->hit_data->shininess;
	data->pixels[y][x].location = ray->hit_data->location;
	data->pixels[y][x].ray_direction = ray->direction;
	data->pixels[y][x].surface_norm = ray->hit_data->surface_norm;
	data->pixels[y][x].ambient = blend_ambient_light(
			ray->hit_data->colour, data->scene.ambient,
			ray->hit_data->reflectivity);
}

void	render_pass(t_data *data, uint32_t y_start,
	uint32_t y_stride, t_pcg *rng)
{
	t_ray	ray;
	t_hit	hit;
	int		x;

	ray.hit_data = &hit;
	ray.rng = rng;
	while ((int)y_start < data->scene.height)
	{
		x = -1;
		while (++x < data->scene.width)
		{
			update_ray(data, &ray, (int32_t)y_start, (int32_t)x);
			get_first_hit(data, &ray, (int32_t)y_start, (int32_t)x);
			if (hit.hit_occurred && hit.type != OBJ_LIGHT)
			{
				if (data->preview_mode)
					prepare_preview(data, &ray, y_start, x);
				else
					trace_paths(data, &ray, y_start, x);
			}
			mlx_put_pixel(data->image_buffer, x, y_start,
				percentage_to_rgba(data->pixels[y_start][x].final_colour));
		}
		y_start += y_stride;
	}
}
