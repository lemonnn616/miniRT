/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:44:46 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 14:36:05 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

bool parse_cone(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5] || tokens[6])
	{
		fprintf(stderr, "Error\nInvalid cone format\n");
		return false;
	}
	t_cone *co = malloc(sizeof(*co));
	if (!co)
	{
		perror("malloc");
		return false;
	}
	if (!parse_vector(tokens[1], &co->apex) ||
		!parse_vector(tokens[2], &co->axis))
	{
		free(co);
		return false;
	}
	co->axis = vec_normalize(co->axis);
	co->angle  = ft_strtof(tokens[3], NULL);
	co->height = ft_strtof(tokens[4], NULL);
	if (co->angle <= 0.0f || co->angle >= 180.0f || co->height <= 0.0f)
	{
		fprintf(stderr, "Error\nCone parameters out of range\n");
		free(co);
		return false;
	}
	t_color col;
	if (!parse_color(tokens[5], &col))
	{
		free(co);
		return false;
	}
	co->mat.color = col;
	co->mat.diffuse = 1.0f;
	co->mat.specular = 0.0f;
	co->mat.shininess = 0.0f;
	co->mat.reflectivity = 0.0f;
	t_object *obj = malloc(sizeof(*obj));
	if (!obj)
	{
		perror("malloc");
		free(co);
		return false;
	}
	obj->type = OBJ_CONE;
	obj->obj = co;
	obj->next = scene->objects;
	scene->objects = obj;
	return true;
}
