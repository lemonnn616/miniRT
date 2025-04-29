/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:00:53 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/29 22:23:51 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

}
