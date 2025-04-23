/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:26 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/23 13:46:59 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

bool parse_sphere(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		fprintf(stderr, "Error\nInvalid sphere format\n");
		return false;
	}
	t_vec3 center;
	if (!parse_vector(tokens[1], &center))
		return false;
	float dia = strtof(tokens[2], NULL); // todo
	if (dia <= 0.0f)
	{
		fprintf(stderr, "Error\nSphere diameter <= 0\n");
		return false;
	}
	t_color col;
	if (!parse_color(tokens[3], &col))
		return false;
	t_material mat = { .color = col, .diffuse = 1.0f, // todo
						.specular = 0.0f, .shininess = 0.0f,
						.reflectivity = 0.0f };
	t_sphere *sp = malloc(sizeof(*sp));
	if (!sp)
	{
		perror("malloc");
		return false;
	}
	sp->center = center;
	sp->radius = dia * 0.5f;
	sp->mat = mat;
	t_object *obj = malloc(sizeof(*obj));
	if (!obj)
	{
		perror("malloc");
		free(sp);
		return false;
	}
	obj->type = OBJ_SPHERE;
	obj->obj  = sp;
	obj->next = scene->objects;
	scene->objects = obj;
	return true;
}