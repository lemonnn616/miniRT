/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:00:53 by iriadyns          #+#    #+#             */
/*   Updated: 2025/05/02 11:59:58 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	debug_print_scene(&data.scene);
	initialise_mlx_window(&data);
	cast_rays(&data);
	render(&data, 0, 0);
	mlx_close_hook(data.mlx, &rt_close, &data);
	// mlx_key_hook(data.mlx, &rt_keys, &data);
	// mlx_scroll_hook(data.mlx, &rt_scroll, &data);
	mlx_loop(data.mlx);
}
