/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 15:55:18 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * @brief Assign cylinder material.
 * @param cy Cylinder to modify.
 * @param col Base color.
 * @param shininess Specular control [0..1].
 * @param reflectivity Reflectivity [0..1].
 * @return None.
 */
static void	set_cylinder_material(t_cylinder *cy, t_color col,
	float shininess, float reflectivity)
{
	cy->mat.color = col;
	cy->mat.diffuse = 1.0f;
	cy->mat.specular = 0.0f;
	cy->mat.shininess = shininess;
	cy->mat.reflectivity = reflectivity;
}

/**
 * @brief Free cylinder and return false.
 * @param cy Cylinder to free.
 * @return false (convenience).
 */
static bool	free_cylinder_fail(t_cylinder *cy)
{
	free(cy);
	return (false);
}

/**
 * @brief Parse color and apply material to cylinder.
 * @param cy Cylinder.
 * @param color_tok Token with color.
 * @param sh Shininess.
 * @param re Reflectivity.
 * @return 1 on success; 0 on error with message.
 */
static int	parse_and_set_cy_material(t_cylinder *cy, const char *color_tok,
		float sh, float re)
{
	t_color	col;

	if (!parse_color(color_tok, &col))
		return (printf("Error\nInvalid cylinder color\n"), 0);
	set_cylinder_material(cy, col, sh, re);
	return (1);
}

/**
 * @brief Make an object node for cylinder.
 * @param cy Cylinder pointer (owned by object).
 * @return Allocated object or NULL (perror on failure).
 */
static t_object	*make_cylinder_object(t_cylinder *cy)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(*obj));
	if (!obj)
	{
		perror("malloc");
		return (NULL);
	}
	obj->type = OBJ_CYLINDER;
	obj->obj = cy;
	obj->next = NULL;
	return (obj);
}

/**
 * @brief Parse a cylinder line and append to the scene object list.
 * @param tokens Token array.
 * @param scene Target scene.
 * @return true on success; false otherwise.
 */
bool	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cy;
	t_object	*obj;
	float		sh;
	float		re;

	if (!validate_cy_tokens(tokens))
		return (false);
	cy = (t_cylinder *)malloc(sizeof(*cy));
	if (!cy)
	{
		perror("malloc");
		return (false);
	}
	if (!fill_cylinder_data(cy, tokens))
		return (free_cylinder_fail(cy));
	if (!parse_cylinder_optional(tokens, &sh, &re))
		return (free_cylinder_fail(cy));
	if (!parse_and_set_cy_material(cy, tokens[5], sh, re))
		return (free_cylinder_fail(cy));
	obj = make_cylinder_object(cy);
	if (!obj)
		return (free_cylinder_fail(cy));
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
