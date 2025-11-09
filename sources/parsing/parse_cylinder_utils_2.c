/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:53:47 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 15:55:14 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * @brief Parse optional cylinder surface params (shininess, reflectivity).
 * @param tokens Token array.
 * @param sh Out shininess (default 0).
 * @param re Out reflectivity (default 0).
 * @return 1 on success; 0 on error with message.
 */
int	parse_cylinder_optional(char **tokens, float *sh, float *re)
{
	int	n;

	*sh = 0.0f;
	*re = 0.0f;
	n = count_tokens(tokens);
	if (n > 6 && !parse_shininess(tokens[6], sh))
		return (printf("Error\nInvalid cylinder shininess\n"), 0);
	if (n > 7 && !parse_reflectivity(tokens[7], re))
		return (printf("Error\nInvalid cylinder reflectivity\n"), 0);
	return (1);
}
