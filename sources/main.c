/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:21:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/23 11:33:01 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	t_scene scene;

	if (argc != 2)
	{
		fprintf("Usage: ./minirt <scene.rt>\n");
		return 1;
	}
	memset(&scene, 0, sizeof(scene));
	if (!parse_scene(argv[1], &scene))
	{
		fprintf(stderr, "Error\nFailed to parse scene.\n");
		return 1;
	}
	printf("OK\n");
	// TODO:render_scene(&scene);
	// TODO:free_scene(&scene);
	return 0;
}