/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:16 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 18:12:03 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Validate minimal tokens for a plane line.
 * @param tokens Token array.
 * @return true if tokens[1..3] exist; false with error otherwise.
 * @details Expected at least: "pl <point> <normal> <R,G,B> ..."
 */
static bool	validate_plane_tokens(char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		printf("Error\nInvalid plane format\n");
		return (false);
	}
	return (true);
}

/**
 * @brief Build an orthonormal (u_axis, v_axis) basis on the plane.
 * @param pl Plane with a valid normalized normal vector.
 * @return None.
 * @details Math: choose an @p up not parallel to normal; u = normalize(n × up),
 * v = n × u. Robust near Y-up using a threshold on |ny|.
 */
static void	build_plane_axes(t_plane *pl)
{
	float	ay;
	t_vec3	up;
	t_vec3	cu;

	ay = pl->normal.y;
	if (ay < 0.0f)
		ay = -ay;
	if (ay < 0.999f)
	{
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;
	}
	else
	{
		up.x = 1.0f;
		up.y = 0.0f;
		up.z = 0.0f;
	}
	cu = vec_cross(pl->normal, up);
	pl->u_axis = vec_normalize(cu);
	pl->v_axis = vec_cross(pl->normal, pl->u_axis);
}

/**
 * @brief Parse required data for a plane: point and normal; initialize defaults.
 * @param pl Plane to fill.
 * @param tokens Token array.
 * @return true on success; false if vector formats invalid or normal degenerate.
 * @details Validates normal components in [-1,1] and non-zero length;
 * normalizes.
 * Initializes orientation, checker flags and local axes.
 */
static bool	fill_plane_data(t_plane *pl, char **tokens)
{
	t_vec3	point;
	t_vec3	normal;

	if (!parse_vector(tokens[1], &point))
		return (false);
	if (!parse_vector(tokens[2], &normal))
		return (false);
	if (normal.x < -1.0f || normal.x > 1.0f
		|| normal.y < -1.0f || normal.y > 1.0f
		|| normal.z < -1.0f || normal.z > 1.0f)
		return (printf("Error\nPlane normal components"
				"must be in [-1,1]\n"), false);
	if (vec_length(normal) < 1e-6f)
		return (printf("Error\nPlane normal vector is zero\n"), false);
	pl->point = point;
	pl->normal0 = vec_normalize(normal);
	pl->normal = pl->normal0;
	pl->orient = (t_quat){1.0f, {0, 0, 0}};
	pl->use_checker = false;
	pl->checker_size = 1.0f;
	pl->checker_alt = (t_color){0.0f, 0.0f, 0.0f};
	build_plane_axes(pl);
	return (true);
}

/**
 * @brief Assigns material properties to a plane.
 * @param pl Plane to modify.
 * @param col Base color.
 * @param shininess Specular probability/control [0..1].
 * @param reflectivity Reflectivity [0..1].
 * @return None.
 */
static void	set_plane_material(t_plane *pl, t_color col,
	float shininess, float reflectivity)
{
	pl->mat.color = col;
	pl->mat.diffuse = 1.0f;
	pl->mat.specular = 0.0f;
	pl->mat.shininess = shininess;
	pl->mat.reflectivity = reflectivity;
}

/**
 * @brief Parse optional checkerboard suffix: "cb <size> <R,G,B>".
 * @param tokens Token array.
 * @param i Index where "cb" may appear.
 * @param pl Plane to annotate with checkerboard params.
 * @return true if OK or not present; false on malformed suffix.
 */
static bool	parse_checkerboard(char **tokens, int i, t_plane *pl)
{
	char	*end;
	float	size;
	t_color	alt;

	if (!tokens[i])
		return (true);
	if (ft_strcmp(tokens[i], "cb") != 0)
		return (printf("Error\nInvalid plane format\n"), false);
	if (!tokens[i + 1] || !tokens[i + 2])
	{
		printf("Error\nInvalid checkerboard format.\n");
		return (printf("Use: cb <size> <R,G,B>\n"), false);
	}
	end = NULL;
	size = ft_strtof(tokens[i + 1], &end);
	if (tokens[i + 1][0] == '\0' || end == NULL || *end != '\0' || size <= 0.0f)
		return (printf("Error\nInvalid checkerboard size\n"), false);
	if (!parse_color(tokens[i + 2], &alt))
		return (false);
	pl->use_checker = true;
	pl->checker_size = size;
	pl->checker_alt = alt;
	if (tokens[i + 3])
		return (printf("Error\nInvalid plane format (extra tokens)\n"), false);
	return (true);
}

/**
 * @brief Parse optional shininess/reflectivity starting at index i.
 * @param tokens Token array.
 * @param i Start index (after color).
 * @param sh Out shininess (default 0).
 * @param re Out reflectivity (default 0).
 * @return Next index on success (>= i); -1 on error.
 */
static int	parse_plane_optional(char **tokens, int i, float *sh, float *re)
{
	int	idx;

	*sh = 0.0f;
	*re = 0.0f;
	idx = i;
	if (tokens[idx] && ft_strcmp(tokens[idx], "cb") != 0)
	{
		if (!parse_shininess(tokens[idx], sh))
			return (-1);
		idx++;
	}
	if (tokens[idx] && ft_strcmp(tokens[idx], "cb") != 0)
	{
		if (!parse_reflectivity(tokens[idx], re))
			return (-1);
		idx++;
	}
	return (idx);
}

/**
 * @brief Parse color and apply material to plane.
 * @param pl Plane.
 * @param color_tok Token with color.
 * @param sh Shininess.
 * @param re Reflectivity.
 * @return 1 on success; 0 on error.
 */
static int	parse_and_set_plane_material(t_plane *pl, const char *color_tok,
		float sh, float re)
{
	t_color	col;

	if (!parse_color(color_tok, &col))
		return (printf("Error\nInvalid plane color\n"), 0);
	set_plane_material(pl, col, sh, re);
	return (1);
}

/**
 * @brief Make an object node for plane.
 * @param pl Plane pointer (owned by object).
 * @return Allocated object or NULL (perror on failure).
 */
static t_object	*make_plane_object(t_plane *pl)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(*obj));
	if (!obj)
	{
		perror("malloc");
		return (NULL);
	}
	obj->type = OBJ_PLANE;
	obj->obj = pl;
	obj->next = NULL;
	return (obj);
}

/**
 * @brief Parse optional params, set material & checkerboard for plane.
 * @param pl Plane.
 * @param tokens Token array.
 * @param i In/out index (starts at 4).
 * @return 1 on success; 0 on error.
 */
static int	set_plane_props(t_plane *pl, char **tokens, int *i)
{
	int		idx;
	float	sh;
	float	re;

	idx = *i;
	sh = 0.0f;
	re = 0.0f;
	idx = parse_plane_optional(tokens, idx, &sh, &re);
	if (idx < 0)
		return (0);
	if (!parse_and_set_plane_material(pl, tokens[3], sh, re))
		return (0);
	if (!parse_checkerboard(tokens, idx, pl))
		return (0);
	*i = idx;
	return (1);
}

/**
 * @brief Parse a plane object line with optional material and checkerboard.
 * @param tokens Token array.
 * @param scene Target scene.
 * @return true on success; false otherwise with diagnostics.
 * @details Syntax: "pl <point> <normal> <R,G,B>
 * [shininess] [reflectivity] [cb <size> <R,G,B>]".
 */
bool	parse_plane(char **tokens, t_scene *scene)
{
	t_plane		*pl;
	t_object	*obj;
	int			i;

	if (!validate_plane_tokens(tokens))
		return (false);
	pl = (t_plane *)malloc(sizeof(*pl));
	if (!pl)
		return (perror("malloc"), false);
	if (!fill_plane_data(pl, tokens))
		return (free(pl), false);
	i = 4;
	if (!set_plane_props(pl, tokens, &i))
		return (free(pl), false);
	obj = make_plane_object(pl);
	if (!obj)
		return (free(pl), false);
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
