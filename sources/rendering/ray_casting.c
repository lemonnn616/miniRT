/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:20:17 by natallia          #+#    #+#             */
/*   Updated: 2025/10/06 16:11:32 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_ray_direction(t_data *data, float y, float x)
{
	float	w = (float)data->scene.width;
	float	h = (float)data->scene.height;
	float	aspect = w / h;
	float	fov;
	if (data->scene.active_cam)
	{
		fov = data->scene.active_cam->fov;
	}
	else
	{
		fov = data->scene.cameras[0].fov;
	}
	float	half_w = tanf(degree_to_radian(fov) * 0.5f);
	float	half_h = half_w / aspect;
	float	nx = (2.0f * (x + 0.5f) / w) - 1.0f;
	float	ny = 1.0f - (2.0f * (y + 0.5f) / h);
	t_vec3	ray;
	ray.x = nx * half_w;
	ray.y = ny * half_h;
	ray.z = 1.0f;
	return vec_normalize(ray);
}

static void	allocate_pixels(t_data *data)
{
	t_pixel	**pixels;
	int		y;

	pixels = malloc(data->scene.height * sizeof(t_pixel *));
	if (pixels == NULL)
		exit_error(data, ERR_MEM);
	ft_memset(pixels, 0, data->scene.height * sizeof(t_pixel *));
	y = 0;
	while (y < data->scene.height)
	{
		pixels[y] = malloc(data->scene.width * sizeof(t_pixel));
		if (pixels[y] == NULL)
		{
			free_pixels(&pixels, y);
			exit_error(data, ERR_MEM);
		}
		ft_memset(pixels[y], 0, data->scene.width * sizeof(t_pixel));
		y++;
	}
	data->pixels = pixels;
}

void	cast_rays(t_data *data)
{
	int	x;
	int	y;

	if (data->pixels == NULL)
		allocate_pixels(data);
	y = 0;
	while (y < data->scene.height)
	{
		x = 0;
		while (x < data->scene.width)
		{
			data->pixels[y][x].ray_direction = get_ray_direction(data, y, x);
			x++;
		}
		y++;
	}
}
