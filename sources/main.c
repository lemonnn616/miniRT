/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:35:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 19:00:58 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief MLX window close hook: marks the app as exiting.
 * @param param Opaque pointer to t_data.
 * @return None.
 */
void	rt_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->exiting)
		return ;
	data->exiting = true;
}

/**
 * @brief Initialize runtime, parse scene, create window and set timing baselines.
 * @param data Out runtime structure to fill.
 * @param argv Command-line arguments (expects argv[1] to hold scene path).
 * @return None (terminates on failure).
 * @details On parse failure prints message, frees the partial scene and exits.
 * Sets active_cam, quality parameters, and initial timestamps.
 */
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
	data->mouse_block_until = 0.0;
	data->suppress_next_mouse = false;
	debug_print_scene(&data->scene);
	initialise_mlx_window(data);
	{
		double now = mlx_get_time();
		data->last_move_time  = now;
		data->last_frame_time = now;
	}
}

/**
 * @brief Register all MLX callbacks (keys, loop, cursor, close).
 * @param data Runtime data (holds MLX handle).
 * @return None.
 */
static void	setup_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, key_cb, data);
	mlx_loop_hook(data->mlx, update_cb, data);
	mlx_cursor_hook(data->mlx, mouse_move, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_close_hook(data->mlx, rt_close, data);
}

/**
 * @brief Rebuild rays for current camera, clear buffers and kick off rendering.
 * @param data Runtime data.
 * @return None.
 */
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
