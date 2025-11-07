/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:37:17 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 16:39:02 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

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
bool	parse_cone_data(t_cone *co, char **tokens)
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
