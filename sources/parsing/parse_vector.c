/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:32:12 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 18:31:32 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

/**
 * @brief Parse a single float component.
 * @param tok Token string for the component.
 * @param dst Output float.
 * @param label Component name ("X", "Y", "Z") for diagnostics.
 * @return 1 on success; 0 on error (prints message).
 */
static int	parse_vec_comp(const char *tok, float *dst, const char *label)
{
	char	*end;
	float	v;

	end = NULL;
	v = ft_strtof(tok, &end);
	if (tok[0] == '\0' || end == NULL || *end != '\0')
	{
		printf("Error\nInvalid %s component format\n", label);
		return (0);
	}
	*dst = v;
	return (1);
}

/**
 * @brief Parse a 3D vector from the string "x,y,z".
 * @param str Input C-string with comma-separated components.
 * @param out Output pointer for the parsed vector.
 * @return true on success; false on malformed input or allocation failure.
 * @details Expects exactly three components; rejects trailing/extra tokens.
 * Uses ft_strtof for each component and validates that the entire
 * token was consumed (no leftover characters).
 * @note This function allocates a temporary copy of @p str and frees it.
 */
bool	parse_vector(const char *str, t_vec3 *out)
{
	char	*copy;
	char	*tok;

	copy = ft_strdup(str);
	if (!copy)
		return (false);
	tok = ft_strtok(copy, ",");
	if (!tok)
		return (free(copy), false);
	if (!parse_vec_comp(tok, &out->x, "X"))
		return (free(copy), false);
	tok = ft_strtok(NULL, ",");
	if (!tok)
		return (free(copy), false);
	if (!parse_vec_comp(tok, &out->y, "Y"))
		return (free(copy), false);
	tok = ft_strtok(NULL, ",");
	if (!tok)
		return (free(copy), false);
	if (!parse_vec_comp(tok, &out->z, "Z"))
		return (free(copy), false);
	if (ft_strtok(NULL, ",") != NULL)
		return (printf("Error\nToo many vector components\n"),
			free(copy), false);
	return (free(copy), true);
}
