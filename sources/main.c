/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:35:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/06 15:42:07 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->exiting)
		return ;
	data->exiting = true;
}

static void	setup_data(t_data *data, char **argv)
{
	ft_memset(data, 0, sizeof(t_data));
	if (!parse_scene(argv[1], &data->scene))
	{
		ft_putendl_fd("Error: Failed to parse scene.", 2);
		free_scene(&data->scene);
		exit(EXIT_FAILURE);
	}
	data->scene.active_cam = data->scene.cameras;
	data->max_rays = MAX_RAYS;
	data->max_bounces = MAX_BOUNCES;
	data->preview_mode = false;
	data->first_mouse = true;
	debug_print_scene(&data->scene);
	initialise_mlx_window(data);
	{
		double now = mlx_get_time();
		data->last_move_time  = now;
		data->last_frame_time = now;
	}
}

static void	setup_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, key_cb, data);
	mlx_loop_hook(data->mlx, update_cb, data);
	mlx_cursor_hook(data->mlx, mouse_move, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_close_hook(data->mlx, rt_close, data);
}

static void	start_rendering(t_data *data)
{
	recalc_rays_with_orientation(data);
	reset_pixel_buffer(data);
	start_progressive_render(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./minirt <scene.rt>", 2);
		return (EXIT_FAILURE);
	}
	setup_data(&data, argv);
	setup_hooks(&data);
	start_rendering(&data);
	mlx_loop(data.mlx);
	exit_success(&data);
	return (EXIT_SUCCESS);
}
