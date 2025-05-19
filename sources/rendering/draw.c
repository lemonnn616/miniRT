/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:07:27 by natallia          #+#    #+#             */
/*   Updated: 2025/05/19 13:11:04 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <float.h>

uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// uint32_t percentage_to_rgba(const t_color f)
// {
// 	return (ft_pixel(f.r * 255, f.g * 255, f.b * 255, 0xff));
// }

uint32_t t_color_to_rgba(const t_color f)
{
	return (ft_pixel(f.r, f.g, f.b, 0xff));
}

void	update_ray(t_data *data, t_ray *ray, int32_t y, int32_t x)
{
	ft_memset(ray->hit_data, 0, sizeof(t_hit));
	ray->origin = data->scene.cameras[0].pos;
	ray->direction = data->pixels[y][x].ray_direction;
	ray->hit_data->colour = new_colour(1.0f, 1.0f, 1.0f);
}

void find_closest_object(t_data *data, t_ray *ray, t_hit *hit)
{
	t_object *obj;

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
	if (ray->hit_data->type == OBJ_LIGHT)
	{
		data->pixels[y][x].final_colour = ray->hit_data->colour;
		gamma_adjust(&data->pixels[y][x].final_colour);
	}
	else if (ray->hit_data->hit_occurred)
	{
		data->pixels[y][x].obj_colour = ray->hit_data->obj_colour;
		data->pixels[y][x].specular = ray->hit_data->specular;
		data->pixels[y][x].shininess = ray->hit_data->shininess;
		data->pixels[y][x].location = ray->hit_data->location;
		data->pixels[y][x].ray_direction = ray->direction;
		data->pixels[y][x].surface_norm = ray->hit_data->surface_norm;
		data->pixels[y][x].ambient = blend_ambient_light(ray->hit_data->colour,
			data->scene.ambient, ray->hit_data->shininess);
		data->pixels[y][x].final_colour = combine_colours(
			data->pixels[y][x].obj_colour, data->pixels[y][x].ambient);
	}
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
			// if (hit.hit_occurred && hit.type != OBJ_LIGHT)
			// 	trace_paths(data, &ray, y, x);
			mlx_put_pixel(data->image_buffer, x, y,
				t_color_to_rgba(data->pixels[y][x].final_colour));
			x++;
		}
		y++;
	}
}
