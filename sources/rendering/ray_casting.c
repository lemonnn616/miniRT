/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:20:17 by natallia          #+#    #+#             */
/*   Updated: 2025/06/19 18:39:06 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_ray_direction(t_data *data, float y, float x)
{
	float	w;
	float	h;
	float	aspect_ratio;
	float	fov_correction;
	t_vec3	ray;

	w = (float)data->scene.width;
	h = (float)data->scene.height;
	aspect_ratio = w / h;
	fov_correction = tan(degree_to_radian(data->scene.cameras[0].fov) / 2.0f);
	ray.x = (2.0f * (x + 0.5f) / w - 1.0f) * fov_correction;
	ray.y = (1.0f - 2.0f * (y + 0.5f) / h) * fov_correction / aspect_ratio;
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
