/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:07 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 13:40:33 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

bool	parse_camera(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		fprintf(stderr, "Error\nInvalid camera format\n");
		return false;
	}
	t_vec3 pos, dir;
	if (!parse_vector(tokens[1], &pos) || !parse_vector(tokens[2], &dir))
		return false;
	dir = vec_normalize(dir);
	float fov = ft_strtof(tokens[3], NULL);
	if (fov <= 0.0f || fov >= 180.0f)
	{
		fprintf(stderr, "Error\nFOV out of range (0,180)\n");
		return false;
	}
	t_camera *cam = malloc(sizeof(*cam));
	if (!cam)
	{
		perror("malloc");
		return false;
	}
	cam->pos  = pos;
	cam->dir  = dir;
	cam->fov  = fov;
	cam->next = scene->cameras;
	scene->cameras = cam;
	return true;
}
