/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:29:50 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 15:32:54 by iriadyns         ###   ########.fr       */
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
bool	validate_plane_tokens(char **tokens)
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
bool	fill_plane_data(t_plane *pl, char **tokens)
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
 * @brief Parse color and apply material to plane.
 * @param pl Plane.
 * @param color_tok Token with color.
 * @param sh Shininess.
 * @param re Reflectivity.
 * @return 1 on success; 0 on error.
 */
int	parse_and_set_plane_material(t_plane *pl, const char *color_tok,
		float sh, float re)
{
	t_color	col;

	if (!parse_color(color_tok, &col))
		return (printf("Error\nInvalid plane color\n"), 0);
	set_plane_material(pl, col, sh, re);
	return (1);
}
