/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:32:03 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 13:55:59 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

bool	parse_camera(char **tokens, t_scene *scene)
{
	t_camera	*cam;
	t_vec3		pos;
	t_vec3		dir;
	float		fov;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (printf("Error\nInvalid camera format\n"), false);
	if (!parse_vector(tokens[1], &pos) || !parse_vector(tokens[2], &dir))
		return (false);
	dir = vec_normalize(dir);
	fov = ft_strtof(tokens[3], NULL);
	if (fov <= 0.0f || fov >= 180.0f)
		return (printf("Error\nFOV out of range (0,180)\n"), false);
	cam = malloc(sizeof(*cam));
	if (!cam)
		return (perror("malloc"), false);
	cam->pos = pos;
	cam->dir = dir;
	cam->orient = (t_quat){.w = 1.0f, .v = {0, 0, 0}};
	cam->fov = fov;
	cam->next = scene->cameras;
	scene->cameras = cam;
	return (true);
}
