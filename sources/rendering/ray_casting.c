/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:20:17 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 12:37:07 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"

static t_vec3	get_ray_direction(t_data *data, float y, float x)
{
	t_vec3	ray;
	float	fov;
	float	half_w;
	float	half_h;

	if (data->scene.active_cam)
		fov = data->scene.active_cam->fov;
	else
		fov = data->scene.cameras[0].fov;
	half_w = tanf(degree_to_radian(fov) * 0.5f);
	half_h = half_w * ((float)data->scene.height / (float)data->scene.width);
	ray.x = ((2.0f * (x + 0.5f) / (float)data->scene.width) - 1.0f) * half_w;
	ray.y = (1.0f - (2.0f * (y + 0.5f) / (float)data->scene.height)) * half_h;
	ray.z = 1.0f;
	return (vec_normalize(ray));
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
