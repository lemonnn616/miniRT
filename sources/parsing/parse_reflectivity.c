/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_reflectivity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:10:24 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:30:38 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdio.h>

/**
 * @brief Parse a normalized reflectivity scalar in [0,1].
 * @param str Input C-string.
 * @param out Output float.
 * @return true on success; false on format/range error.
 */
bool	parse_reflectivity(const char *str, float *out)
{
	char	*end;
	float	value;

	if (!str || !out)
		return (false);
	value = ft_strtof(str, &end);
	if (*end != '\0')
	{
		printf("Error\nInvalid reflectivity format\n");
		return (false);
	}
	if (value < 0.0f || value > 1.0f)
	{
		printf("Error\nReflectivity out of range [0,1]\n");
		return (false);
	}
	*out = value;
	return (true);
}
