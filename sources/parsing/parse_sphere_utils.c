/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:24:17 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 15:24:45 by iriadyns         ###   ########.fr       */
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
bool	validate_sphere_tokens(char **tokens)
{
	int	n;

	n = count_tokens(tokens);
	if (n < 4 || n > 6)
		return (printf("Error\nInvalid sphere format\n"), false);
	return (true);
}
