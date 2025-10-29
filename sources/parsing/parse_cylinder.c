/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/29 18:00:33 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static bool	validate_cy_tokens(char **tokens)
{
	int	n;

	n = count_tokens(tokens);
	if (n < 6 || n > 8)
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
	char	*end = NULL;
	char	*end2 = NULL;

	if (!parse_vector(tokens[1], &base) || !parse_vector(tokens[2], &axis))
		return (false);
	if (axis.x < -1.0f || axis.x > 1.0f
			|| axis.y < -1.0f || axis.y > 1.0f
			|| axis.z < -1.0f || axis.z > 1.0f)
		return (printf("Error\nCylinder axis components must be in [-1,1]\n"), false);
	if (vec_length(axis) < 1e-6f)
		return (printf("Error\nCylinder axis vector is zero\n"), false);
	dia = ft_strtof(tokens[3], &end);
	h = ft_strtof(tokens[4], &end2);
	if (*tokens[3] == '\0' || *end != '\0')
		return (printf("Error\nInvalid cylinder diameter format\n"), false);
	if (*tokens[4] == '\0' || *end2 != '\0')
		return (printf("Error\nInvalid cylinder height format\n"), false);
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

static void	set_cylinder_material(t_cylinder *cy, t_color col,
	float shininess, float reflectivity)
{
	cy->mat.color = col;
	cy->mat.diffuse = 1.0f;
	cy->mat.specular = 0.0f;
	cy->mat.shininess = shininess;
	cy->mat.reflectivity = reflectivity;
}

bool	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cy;
	t_object	*obj;
	t_color		col;
	float		shininess;
	float		reflectivity;
	int			n;

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
	reflectivity = 0.0f;
	n = count_tokens(tokens);
	if (n > 6 && !parse_shininess(tokens[6], &shininess))
		return (free(cy), false);
	if (n > 7 && !parse_reflectivity(tokens[7], &reflectivity))
		return (free(cy), false);
	set_cylinder_material(cy, col, shininess, reflectivity);
	obj = malloc(sizeof(*obj));
	if (!obj)
		return (perror("malloc"), free(cy), false);
	obj->type = OBJ_CYLINDER;
	obj->obj = cy;
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}