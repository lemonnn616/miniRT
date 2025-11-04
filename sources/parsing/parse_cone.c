/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:44:46 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:57:57 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * @brief Validate token count for a cone line.
 * @param tokens Token array.
 * @return true if count in [6,8]; false otherwise with error.
 * @details Expected: "co <apex> <axis> <angle_deg> <height> <R,G,B>
 * [shininess] [reflectivity]".
 */
static bool	validate_cone_tokens(char **tokens)
{
	int	n;

	n = count_tokens(tokens);
	if (n < 6 || n > 8)
	{
		printf("Error\nInvalid cone format\n");
		return (false);
	}
	return (true);
}

/**
 * @brief Parse cone apex position.
 * @param tok Token string for apex.
 * @param co Output cone.
 * @return 1 on success; 0 on error with message.
 */
static int	parse_cone_apex(const char *tok, t_cone *co)
{
	if (!parse_vector(tok, &co->apex))
		return (printf("Error\nInvalid cone apex\n"), 0);
	return (1);
}

/**
 * @brief Parse and validate cone axis; normalize and store axis/axis0.
 * @param tok Token string for axis.
 * @param co Output cone.
 * @return 1 on success; 0 on error with message.
 * @details Enforces components in [-1,1] and non-zero length.
 */
static int	parse_cone_axis(const char *tok, t_cone *co)
{
	int		ok;
	t_vec3	v;

	ok = parse_vector(tok, &v);
	if (!ok)
		return (printf("Error\nInvalid cone axis\n"), 0);
	if (v.x < -1.0f || v.x > 1.0f
		|| v.y < -1.0f || v.y > 1.0f
		|| v.z < -1.0f || v.z > 1.0f)
		return (printf("Error\nCone axis components must be in [-1,1]\n"), 0);
	if (vec_length(v) < 1e-6f)
		return (printf("Error\nCone axis vector is zero\n"), 0);
	co->axis0 = vec_normalize(v);
	co->axis = co->axis0;
	return (1);
}

/**
 * @brief Parse cone angle and height.
 * @param tok_angle Token string for angle (deg).
 * @param tok_height Token string for height.
 * @param co Output cone.
 * @return 1 on success; 0 on error with message.
 * @details Requires full-string floats; angle in (0,180), height > 0.
 */
static int	parse_cone_angle_height(const char *tok_angle,
		const char *tok_height, t_cone *co)
{
	char	*end1;
	char	*end2;
	float	a;
	float	h;

	end1 = NULL;
	end2 = NULL;
	a = 0.0f;
	h = 0.0f;
	a = ft_strtof(tok_angle, &end1);
	h = ft_strtof(tok_height, &end2);
	if (tok_angle[0] == '\0' || end1 == NULL || *end1 != '\0')
		return (printf("Error\nInvalid cone angle format\n"), 0);
	if (tok_height[0] == '\0' || end2 == NULL || *end2 != '\0')
		return (printf("Error\nInvalid cone height format\n"), 0);
	if (a <= 0.0f || a >= 180.0f || h <= 0.0f)
		return (printf("Error\nCone parameters out of range\n"), 0);
	co->angle = a;
	co->height = h;
	return (1);
}

/**
 * @brief Set identity orientation for the cone.
 * @param co Output cone.
 */
static void	init_cone_orientation(t_cone *co)
{
	co->orient.w = 1.0f;
	co->orient.v.x = 0.0f;
	co->orient.v.y = 0.0f;
	co->orient.v.z = 0.0f;
}

/**
 * @brief Parse required cone data (apex, axis, angle, height)
 * and set derived fields.
 * @param co Output cone.
 * @param tokens Token array.
 * @return true on success; false on validation errors.
 * @details Validates axis in [-1,1] and non-zero; angle in (0,180); height > 0.
 * Stores axis0 normalized; orient identity.
 */
static bool	parse_cone_data(t_cone *co, char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4])
		return (printf("Error\nInvalid cone format\n"), false);
	if (!parse_cone_apex(tokens[1], co))
		return (false);
	if (!parse_cone_axis(tokens[2], co))
		return (false);
	if (!parse_cone_angle_height(tokens[3], tokens[4], co))
		return (false);
	init_cone_orientation(co);
	return (true);
}

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
