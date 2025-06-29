/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:35:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/22 20:19:23 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void loop_hook(void *param)
{
	t_data *d = param;
	double now = mlx_get_time();

	if (d->preview_mode && now - d->last_move_time > 0.05)
	{
		d->preview_mode = false;
		d->max_rays = MAX_RAYS;
		d->max_bounces = MAX_BOUNCES;

		reset_pixel_buffer(d);
		render(d, 0, 0);
	}
}

void reset_pixel_buffer(t_data *d)
{
	for (int y = 0; y < d->scene.height; ++y)
		for (int x = 0; x < d->scene.width; ++x)
		{
			t_pixel *p = &d->pixels[y][x];
			p->colour_sum = new_colour(0,0,0);
			p->final_colour = new_colour(0,0,0);
			p->ambient = new_colour(0,0,0);
		}
}

void	rt_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	exit_success(data);
}

static void recalc_rays_with_orientation(t_data *data)
{
	cast_rays(data);
	t_camera *cam = data->scene.active_cam;
	for (int y = 0; y < data->scene.height; ++y)
	{
		for (int x = 0; x < data->scene.width; ++x)
		{
			t_vec3 v = data->pixels[y][x].ray_direction;
			t_vec3 world =
				vec_add(
					vec_add(
						vec_scale(cam->right, v.x),
						vec_scale(cam->up,	v.y)),
					vec_scale(cam->dir,	 v.z));
			data->pixels[y][x].ray_direction = vec_normalize(world);
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./minirt <scene.rt>", 2);
		return (EXIT_FAILURE);
	}
	ft_memset(&data, 0, sizeof(data));
	if (!parse_scene(argv[1], &data.scene))
	{
		ft_putendl_fd("Error: Failed to parse scene.", 2);
		free_scene(&data.scene);
		return (EXIT_FAILURE);
	}
	data.scene.active_cam = data.scene.cameras;
	data.max_rays = MAX_RAYS;
	data.max_bounces = MAX_BOUNCES;
	data.preview_mode = false;
	data.last_move_time = 0.0;
	debug_print_scene(&data.scene);
	initialise_mlx_window(&data);
	recalc_rays_with_orientation(&data);
	reset_pixel_buffer(&data);
	render(&data, 0, 0);
	mlx_cursor_hook(data.mlx, mouse_move, &data);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_close_hook(data.mlx, rt_close, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}