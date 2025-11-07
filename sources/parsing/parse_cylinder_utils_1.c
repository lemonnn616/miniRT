/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:51:51 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 15:55:37 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * @brief Validate token count for a cylinder line.
 * @param tokens Token array.
 * @return true if count in [6,8]; false otherwise with error message.
 * @details Expected: "cy <base> <axis> <diameter> <height> <R,G,B>
 * [shininess] [reflectivity]".
 */
bool	validate_cy_tokens(char **tokens)
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

/**
 * @brief Parse cylinder base position.
 * @param tok Token string for base.
 * @param cy Output cylinder.
 * @return 1 on success; 0 with error message otherwise.
 */
static int	parse_cy_base(const char *tok, t_cylinder *cy)
{
	if (!parse_vector(tok, &cy->base))
		return (printf("Error\nInvalid cylinder base\n"), 0);
	return (1);
}

/**
 * @brief Parse & validate cylinder axis; normalize and cache axis/axis0.
 * @param tok Token string for axis.
 * @param cy Output cylinder.
 * @return 1 on success; 0 with error message otherwise.
 * @details Enforces components in [-1,1] and non-zero length.
 */
static int	parse_cy_axis(const char *tok, t_cylinder *cy)
{
	t_vec3	v;

	if (!parse_vector(tok, &v))
		return (printf("Error\nInvalid cylinder axis\n"), 0);
	if (v.x < -1.0f || v.x > 1.0f
		|| v.y < -1.0f || v.y > 1.0f
		|| v.z < -1.0f || v.z > 1.0f)
		return (printf("Error\nCylinder axis components must be in [-1,1]\n"),
			0);
	if (vec_length(v) < 1e-6f)
		return (printf("Error\nCylinder axis vector is zero\n"), 0);
	cy->axis0 = vec_normalize(v);
	cy->axis = cy->axis0;
	return (1);
}

/**
 * @brief Parse cylinder diameter and height; return radius and height.
 * @param tok_dia Token string for diameter.
 * @param tok_h Token string for height.
 * @param radius_out Output radius (dia/2).
 * @param h_out Output height.
 * @return 1 on success; 0 with error message otherwise.
 * @details Requires full-string floats; dia>0, h>0.
 */
static int	parse_cy_sizes(const char *tok_dia, const char *tok_h,
		float *radius_out, float *h_out)
{
	char	*end1;
	char	*end2;
	float	dia;
	float	h;

	end1 = NULL;
	end2 = NULL;
	dia = 0.0f;
	h = 0.0f;
	dia = ft_strtof(tok_dia, &end1);
	h = ft_strtof(tok_h, &end2);
	if (tok_dia[0] == '\0' || end1 == NULL || *end1 != '\0')
		return (printf("Error\nInvalid cylinder diameter format\n"), 0);
	if (tok_h[0] == '\0' || end2 == NULL || *end2 != '\0')
		return (printf("Error\nInvalid cylinder height format\n"), 0);
	if (dia <= 0.0f || h <= 0.0f)
		return (printf("Error\nCylinder size must be > 0\n"), 0);
	*radius_out = dia * 0.5f;
	*h_out = h;
	return (1);
}

/**
 * @brief Parse required cylinder data and set derived fields.
 * @param cy Output cylinder.
 * @param tokens Token array.
 * @return true on success; false on any validation failure.
 * @details Validates axis in [-1,1] and non-zero; normalizes axis.
 * radius = diameter/2; sets orient to identity and caches axis0.
 */
bool	fill_cylinder_data(t_cylinder *cy, char **tokens)
{
	float	radius;
	float	height;

	if (!parse_cy_base(tokens[1], cy))
		return (false);
	if (!parse_cy_axis(tokens[2], cy))
		return (false);
	if (!parse_cy_sizes(tokens[3], tokens[4], &radius, &height))
		return (false);
	cy->radius = radius;
	cy->height = height;
	cy->orient.w = 1.0f;
	cy->orient.v.x = 0.0f;
	cy->orient.v.y = 0.0f;
	cy->orient.v.z = 0.0f;
	return (true);
}
