/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:07:27 by natallia          #+#    #+#             */
/*   Updated: 2025/05/08 14:41:19 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_ray(t_data *data, t_ray *ray, int32_t y, int32_t x)
{
	ft_memset(ray->hit_data, 0, sizeof(t_hit));
	ray->origin = data->scene.cameras[0].pos;
	ray->direction = data->pixels[y][x].ray_direction;
	ray->hit_data->colour.r = 1;
	ray->hit_data->colour.g = 1;
	ray->hit_data->colour.b = 1;
}

void find_closest_object(t_data *data, t_ray *ray, t_hit *hit)
{
	t_object *obj;

	obj = data->scene.objects;
	hit->hit_occurred = false;
	hit->type = OBJ_NONE;
	hit->distance = MAXFLOAT;
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
		obj = obj->next;
	}
}



t_color	blend_ambient_light(t_color base, t_ambient amb, float shininess)
{
	float	amb_total;
	t_color	result;

	if (!amb.is_set)
		return (base);
	amb_total = amb.intensity * (1.0f - shininess);

	// lerp
	// result.r = base.r * (1.0f - amb_total) + amb.color.r * amb_total;
	// result.g = base.g * (1.0f - amb_total) + amb.color.g * amb_total;
	// result.b = base.b * (1.0f - amb_total) + amb.color.b * amb_total;

	result.r = base.r * amb.color.r * amb_total;
	result.g = base.g * amb.color.g * amb_total;
	result.b = base.b * amb.color.b * amb_total;

	// compromise ?
	// result.r = base.r * (amb.color.r * amb_total + (1 - amb_total));
	// result.g = base.g * (amb.color.g * amb_total + (1 - amb_total));
	// result.b = base.b * (amb.color.b * amb_total + (1 - amb_total));
	return (result);
}

void	get_first_hit(t_data *data, t_ray *ray, int32_t y, int32_t x)
{
	find_closest_object(data, ray, ray->hit_data);
	if (ray->hit_data->hit_occurred)
	{
		data->pixels[y][x].obj_colour = ray->hit_data->obj_colour;
		data->pixels[y][x].specular = ray->hit_data->specular;
		data->pixels[y][x].shininess = ray->hit_data->shininess;
		data->pixels[y][x].location = ray->hit_data->location;
		data->pixels[y][x].ray_direction = ray->direction;
		data->pixels[y][x].surface_norm = ray->hit_data->surface_norm;
		data->pixels[y][x].ambient = blend_ambient_light(ray->hit_data->colour,
			data->scene.ambient, ray->hit_data->shininess);
		data->pixels[y][x].final_colour = blend_ambient_light(ray->hit_data->obj_colour,
			data->scene.ambient, ray->hit_data->shininess);
	}
	else
		data->pixels[y][x].final_colour = data->scene.ambient.color;
}

uint32_t ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t percentage_to_rgba(const t_color f)
{
	return (ft_pixel(f.r * 255, f.g * 255, f.b * 255, 0xff));
}

void	render(t_data *data, uint32_t y, uint32_t x)
{
	t_ray		ray;
	t_hit		hit;

	ray.hit_data = &hit;
	while (y < (uint32_t)data->scene.height)
	{
		x = 0;
		while (x < (uint32_t)data->scene.width)
		{
			update_ray(data, &ray, y, x);
			get_first_hit(data, &ray, y, x);
			// continue tracing with light as object
			mlx_put_pixel(data->image_buffer, x, y,
				percentage_to_rgba(data->pixels[y][x].final_colour));
			x++;
		}
		y++;
	}
}
