/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:00:53 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/19 18:57:51 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	exit_success(data);
}

static void recalc_rays_with_orientation(t_data *data)
{
	/* 1) генерируем «камерные» лучи старой функцией */
	cast_rays(data);   /* если pixels ещё нет – она же их и выделит */

	/* 2) превращаем их в мировые через basis активной камеры */
	t_camera *cam = data->scene.active_cam;
	for (int y = 0; y < data->scene.height; ++y)
	{
		for (int x = 0; x < data->scene.width; ++x)
		{
			t_vec3 v = data->pixels[y][x].ray_direction;   /* локальный (x,y,z) */
			t_vec3 world =
				vec_add(
					vec_add(
						vec_scale(cam->right, v.x),
						vec_scale(cam->up,    v.y)),
					vec_scale(cam->dir,     v.z));
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

	/* кватернионное вращение камеры */
	t_quat q_yaw   = quat_from_axis_angle((t_vec3){0,1,0}, (float)(dx * sens));
	t_quat q_pitch = quat_from_axis_angle(cam->right,      (float)(dy * sens));
	cam->orient = quat_normalize(quat_mul(q_pitch, quat_mul(q_yaw, cam->orient)));
	camera_compute_basis(cam);

	/* 1) пересчитываем направления лучей под новый basis */
	recalc_rays_with_orientation(data);
	/* 2) обычный рендер целиком */
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
	debug_print_scene(&data.scene);
	initialise_mlx_window(&data);
	recalc_rays_with_orientation(&data);
	render(&data, 0, 0);
	mlx_cursor_hook(data.mlx, mouse_move, &data);
	mlx_close_hook(data.mlx, &rt_close, &data);
	// mlx_key_hook(data.mlx, &rt_keys, &data);
	// mlx_scroll_hook(data.mlx, &rt_scroll, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
