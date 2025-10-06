/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/06 15:05:44 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static bool	validate_cy_tokens(char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3]
		|| !tokens[4] || !tokens[5])
	{
		printf("Error\nInvalid cylinder format\n");
		return (false);
	}
	if (tokens[6] && tokens[7])
	{
		printf("Error\nInvalid cylinder format\n");
		return (false);
	}
	return (true);
}

static bool	fill_cylinder_data(t_cylinder *cy, char **tokens)
{
	t_vec3	base;
	t_vec3	axis;
	float	dia;
	float	h;

	if (!parse_vector(tokens[1], &base) || !parse_vector(tokens[2], &axis))
		return (false);
	if (axis.x < -1.0f || axis.x > 1.0f
			|| axis.y < -1.0f || axis.y > 1.0f
			|| axis.z < -1.0f || axis.z > 1.0f)
		return (printf("Error\nCylinder axis components must be in [-1,1]\n"), false);
	if (vec_length(axis) < 1e-6f)
		return (printf("Error\nCylinder axis vector is zero\n"), false);
	dia = ft_strtof(tokens[3], NULL);
	h = ft_strtof(tokens[4], NULL);
	if (dia <= 0.0f || h <= 0.0f)
	{
		printf("Error\nCylinder size must be > 0\n");
		return (false);
	}
	cy->base = base;
	cy->axis0 = vec_normalize(axis);
	cy->axis = cy->axis0;
	cy->orient = (t_quat){1.0f, {0, 0, 0}};
	cy->radius = dia * 0.5f;
	cy->height = h;
	return (true);
}

static void	set_cylinder_material(t_cylinder *cy, t_color col, float shininess)
{
	cy->mat.color = col;
	cy->mat.diffuse = 1.0f;
	cy->mat.specular = 0.0f;
	cy->mat.shininess = shininess;
	cy->mat.reflectivity = 0.0f;
}

bool	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cy;
	t_object	*obj;
	t_color		col;
	float		shininess;

	if (!validate_cy_tokens(tokens))
		return (false);
	cy = malloc(sizeof(*cy));
	if (!cy)
		return (perror("malloc"), false);
	if (!fill_cylinder_data(cy, tokens))
		return (free(cy), false);
	if (!parse_color(tokens[5], &col))
		return (free(cy), false);
	shininess = 0.0f;
	if (tokens[6])
	{
		if (!parse_shininess(tokens[6], &shininess))
			return (free(cy), false);
	}
	set_cylinder_material(cy, col, shininess);
	obj = malloc(sizeof(*obj));
	if (!obj)
		return (perror("malloc"), free(cy), false);
	obj->type = OBJ_CYLINDER;
	obj->obj = cy;
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
