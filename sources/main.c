/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:35:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 13:42:58 by iriadyns         ###   ########.fr       */
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

void	rt_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	exit_success(data);
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
	mlx_key_hook(data.mlx, key_cb, &data);
	mlx_loop_hook(data.mlx, update_cb, &data);
	recalc_rays_with_orientation(&data);
	reset_pixel_buffer(&data);
	render(&data, 0, 0);
	mlx_cursor_hook(data.mlx, mouse_move, &data);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_close_hook(data.mlx, rt_close, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}