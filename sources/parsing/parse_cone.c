/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:44:46 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 16:39:35 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * @brief Assign cone material using a color string.
 * @param co Cone to modify.
 * @param str Color string "R,G,B".
 * @param shininess Specular control [0..1].
 * @param reflectivity Reflectivity [0..1].
 * @return true on success; false if color parse failed.
 */
static bool	set_cone_material(t_cone *co, const char *str,
	float shininess, float reflectivity)
{
	t_color	col;

	if (!parse_color(str, &col))
		return (false);
	co->mat.color = col;
	co->mat.diffuse = 1.0f;
	co->mat.specular = 0.0f;
	co->mat.shininess = shininess;
	co->mat.reflectivity = reflectivity;
	return (true);
}

/**
 * @brief Free cone and return false.
 * @param co Cone to free.
 * @return false (convenience helper).
 */
static bool	free_cone_fail(t_cone *co)
{
	free(co);
	return (false);
}

/**
 * @brief Parse optional cone surface params.
 * @param tokens Token array.
 * @param sh Out shininess (default 0).
 * @param re Out reflectivity (default 0).
 * @return 1 on success; 0 on error.
 */
static int	parse_cone_optional(char **tokens, float *sh, float *re)
{
	int	n;

	*sh = 0.0f;
	*re = 0.0f;
	n = count_tokens(tokens);
	if (n > 6 && !parse_shininess(tokens[6], sh))
		return (printf("Error\nInvalid cone shininess\n"), 0);
	if (n > 7 && !parse_reflectivity(tokens[7], re))
		return (printf("Error\nInvalid cone reflectivity\n"), 0);
	return (1);
}

/**
 * @brief Make an object node for a cone.
 * @param co Cone pointer (owned by object).
 * @return Allocated object or NULL (perror on failure).
 */
static t_object	*make_cone_object(t_cone *co)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(*obj));
	if (!obj)
		return (perror("malloc"), NULL);
	obj->type = OBJ_CONE;
	obj->obj = co;
	obj->next = NULL;
	return (obj);
}

/**
 * @brief Parse a cone line and append it to the scene object list.
 * @param tokens Token array.
 * @param scene Target scene.
 * @return true on success; false otherwise.
 */
bool	parse_cone(char **tokens, t_scene *scene)
{
	t_cone		*co;
	t_object	*obj;
	float		sh;
	float		re;

	if (!validate_cone_tokens(tokens))
		return (false);
	co = (t_cone *)malloc(sizeof(*co));
	if (!co)
		return (perror("malloc"), false);
	if (!parse_cone_data(co, tokens))
		return (free_cone_fail(co));
	if (!parse_cone_optional(tokens, &sh, &re))
		return (free_cone_fail(co));
	if (!set_cone_material(co, tokens[5], sh, re))
		return (free_cone_fail(co));
	obj = make_cone_object(co);
	if (!obj)
		return (free_cone_fail(co));
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
