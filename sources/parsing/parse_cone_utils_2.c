/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:37:20 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 16:39:18 by iriadyns         ###   ########.fr       */
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
bool	validate_cone_tokens(char **tokens)
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
