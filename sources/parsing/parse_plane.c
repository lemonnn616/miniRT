/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:16 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 13:41:56 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

bool parse_plane(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		fprintf(stderr, "Error\nInvalid plane format\n");
		return false;
	}
	t_vec3 point, normal;
	if (!parse_vector(tokens[1], &point) || !parse_vector(tokens[2], &normal))
		return false;
	normal = vec_normalize(normal);
	t_color col;
	if (!parse_color(tokens[3], &col))
		return false;
	t_material mat = { .color = col, .diffuse = 1.0f,
						.specular = 0.0f, .shininess = 0.0f,
						.reflectivity = 0.0f };
	t_plane *pl = malloc(sizeof(*pl));
	if (!pl)
	{
		perror("malloc");
		return false;
	}
	pl->point = point;
	pl->normal = normal;
	pl->mat = mat;
	t_object *obj = malloc(sizeof(*obj));
	if (!obj)
	{
		perror("malloc");
		free(pl);
		return false;
	}
	obj->type = OBJ_PLANE;
	obj->obj = pl;
	obj->next = scene->objects;
	scene->objects = obj;
	return true;
}