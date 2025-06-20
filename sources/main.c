/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:44:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/20 13:46:50 by iriadyns         ###   ########.fr       */
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

static bool   first_mouse = true;
static double last_x, last_y;

static void mouse_move(double mx, double my, void *param)
{
	t_data   *data = param;
	t_camera *cam  = data->scene.active_cam;

	const double sens = 0.002;
	double dx = mx - last_x;
	double dy = my - last_y;

	if (first_mouse)
	{
		first_mouse = false;
		last_x = mx;
		last_y = my;
		return;
	}
	last_x = mx;
	last_y = my;
	t_quat q_yaw   = quat_from_axis_angle((t_vec3){0,1,0}, (float)(dx * sens));
	t_quat q_pitch = quat_from_axis_angle(cam->right, (float)(dy * sens));
	cam->orient = quat_normalize(quat_mul(q_pitch, quat_mul(q_yaw, cam->orient)));
	camera_compute_basis(cam);
	data->preview_mode = true;
	data->max_rays = 1;
	data->max_bounces = 0;
	data->last_move_time = mlx_get_time();
	recalc_rays_with_orientation(data);
	reset_pixel_buffer(data);
	render(data, 0, 0);
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