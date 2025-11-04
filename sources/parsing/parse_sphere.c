/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:26 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 18:25:15 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Validate token count for a sphere line.
 * @param tokens NULL-terminated token array.
 * @return true if token count is in [4,6]; false and prints error otherwise.
 * @details Expected: "sp <center> <diameter> <R,G,B>
 * [shininess] [reflectivity]".
 */
static bool	validate_sphere_tokens(char **tokens)
{
	int	n;

	n = count_tokens(tokens);
	if (n < 4 || n > 6)
		return (printf("Error\nInvalid sphere format\n"), false);
	return (true);
}

/**
 * @brief Parse required data for a sphere: center and diameter.
 * @param sp Output sphere pointer (already allocated).
 * @param tokens Token array for the sphere line.
 * @return true on success; false on any validation error.
 * @details Validates diameter format and positivity; radius = diameter/2.
 */
static bool	fill_sphere_data(t_sphere *sp, char **tokens)
{
	t_vec3	center;
	float	dia;
	char	*end;

	end = NULL;
	if (!parse_vector(tokens[1], &center))
		return (false);
	dia = ft_strtof(tokens[2], &end);
	if (*tokens[2] == '\0' || *end != '\0')
		return (printf("Error\nInvalid sphere diameter format\n"), false);
	if (dia <= 0.0f)
	{
		printf("Error\nSphere diameter <= 0\n");
		return (false);
	}
	sp->center = center;
	sp->radius = dia * 0.5f;
	return (true);
}

/**
 * @brief Assigns material properties to a sphere.
 * @param sp Sphere to modify.
 * @param col Base albedo color (0..1 per channel).
 * @param shininess [0..1] controls specular probability in your integrator.
 * @param reflectivity [0..1] reflectivity coefficient (used if supported).
 * @return None.
 */
static void	set_sphere_material(t_sphere *sp, t_color col,
	float shininess, float reflectivity)
{
	sp->mat.color = col;
	sp->mat.diffuse = 0.8f;
	sp->mat.specular = 0.2f;
	sp->mat.shininess = shininess;
	sp->mat.reflectivity = reflectivity;
}

/**
 * @brief Parse optional sphere surface params (shininess, reflectivity).
 * @param tokens Token array.
 * @param i Start index (after color).
 * @param sh Out shininess (default 0.5).
 * @param re Out reflectivity (default 0.1).
 * @return Next index on success (>= i); -1 on error.
 */
static int	parse_sphere_optional(char **tokens, int i, float *sh, float *re)
{
	int	idx;

	*sh = 0.5f;
	*re = 0.1f;
	idx = i;
	if (tokens[idx])
	{
		if (!parse_shininess(tokens[idx], sh))
			return (-1);
		idx++;
	}
	if (tokens[idx])
	{
		if (!parse_reflectivity(tokens[idx], re))
			return (-1);
		idx++;
	}
	return (idx);
}

/**
 * @brief Make an object node for a sphere (owns sp).
 * @param sp Sphere pointer.
 * @return Allocated object or NULL (perror on failure).
 */
static t_object	*make_sphere_object(t_sphere *sp)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(*obj));
	if (!obj)
		return (perror("malloc"), NULL);
	obj->type = OBJ_SPHERE;
	obj->obj = sp;
	obj->next = NULL;
	return (obj);
}

/**
 * @brief Parse a sphere object line and append it to the scene object list.
 * @param tokens Token array (must be validated).
 * @param scene Target scene to mutate.
 * @return true on success; false on allocation/parse error (prints diagnostics).
 * @details Optional fields: shininess, reflectivity. Color is required.
 * On success links a new t_object{OBJ_SPHERE} at scene->objects head.
 */
bool	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sp;
	t_object	*obj;
	t_color		col;
	float		sh;
	float		re;

	if (!validate_sphere_tokens(tokens))
		return (false);
	sp = (t_sphere *)malloc(sizeof(*sp));
	if (!sp)
		return (perror("malloc"), false);
	if (!fill_sphere_data(sp, tokens))
		return (free(sp), false);
	if (!parse_color(tokens[3], &col))
		return (free(sp), false);
	if (parse_sphere_optional(tokens, 4, &sh, &re) < 0)
		return (free(sp), false);
	set_sphere_material(sp, col, sh, re);
	obj = make_sphere_object(sp);
	if (!obj)
		return (free(sp), false);
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
