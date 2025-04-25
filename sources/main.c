/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:00:53 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 12:40:13 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>

#include "debug.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
	{
		printf("Usage: ./minirt <scene.rt>\n");
		return (1);
	}
	ft_memset(&scene, 0, sizeof(scene));
	if (!parse_scene(argv[1], &scene))
	{
		printf("Error\nFailed to parse scene.\n");
		free_scene(&scene);
		return (1);
	}
	debug_print_scene(&scene);
	free_scene(&scene);
	return (0);
}
