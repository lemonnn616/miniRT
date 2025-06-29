/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 13:53:00 by iriadyns         ###   ########.fr       */
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
		|| !tokens[4] || !tokens[5] || tokens[6])
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
	dia = ft_strtof(tokens[3], NULL);
	h = ft_strtof(tokens[4], NULL);
	if (dia <= 0.0f || h <= 0.0f)
	{
		printf("Error\nCylinder size <= 0\n");
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

static void	set_cylinder_material(t_cylinder *cy, t_color col)
{
	cy->mat.color = col;
	cy->mat.diffuse = 1.0f;
	cy->mat.specular = 0.0f;
	cy->mat.shininess = 0.0f;
	cy->mat.reflectivity = 0.0f;
}

bool	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cy;
	t_object	*obj;
	t_color		col;

	if (!validate_cy_tokens(tokens))
		return (false);
	cy = malloc(sizeof(*cy));
	if (!cy)
		return (perror("malloc"), false);
	if (!fill_cylinder_data(cy, tokens))
		return (free(cy), false);
	if (!parse_color(tokens[5], &col))
		return (free(cy), false);
	set_cylinder_material(cy, col);
	obj = malloc(sizeof(*obj));
	if (!obj)
		return (perror("malloc"), free(cy), false);
	obj->type = OBJ_CYLINDER;
	obj->obj = cy;
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
