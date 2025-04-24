/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 13:41:21 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

bool parse_cylinder(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] ||
		!tokens[4] || !tokens[5] || tokens[6])
	{
		fprintf(stderr, "Error\nInvalid cylinder format\n");
		return false;
	}
	t_vec3 base, axis;
	if (!parse_vector(tokens[1], &base) || !parse_vector(tokens[2], &axis))
		return false;
	axis = vec_normalize(axis);
	float dia = ft_strtof(tokens[3], NULL);
	float h = ft_strtof(tokens[4], NULL);
	if (dia <= 0.0f || h <= 0.0f)
	{
		fprintf(stderr, "Error\nCylinder size <= 0\n");
		return false;
	}
	t_color col;
	if (!parse_color(tokens[5], &col))
		return false;
	t_material mat = { .color = col, .diffuse = 1.0f,
						.specular = 0.0f, .shininess = 0.0f,
						.reflectivity = 0.0f };
	t_cylinder *cy = malloc(sizeof(*cy));
	if (!cy)
	{
		perror("malloc");
		return false;
	}
	cy->base = base;
	cy->axis = axis;
	cy->radius = dia * 0.5f;
	cy->height = h;
	cy->mat = mat;
	t_object *obj = malloc(sizeof(*obj));
	if (!obj)
	{
		perror("malloc");
		free(cy);
		return false;
	}
	obj->type = OBJ_CYLINDER;
	obj->obj = cy;
	obj->next = scene->objects;
	scene->objects = obj;
	return true;
}