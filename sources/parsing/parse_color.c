/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:32:07 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:40:29 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

/**
 * @brief Validate that 8-bit RGB components are within [0,255].
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 * @return true if all are in range; false otherwise.
 */
static bool	color_range_valid(long r, long g, long b)
{
	if (r < 0 || r > 255)
		return (false);
	if (g < 0 || g > 255)
		return (false);
	if (b < 0 || b > 255)
		return (false);
	return (true);
}

/**
 * @brief Parse three comma-separated integers into r,g,b with strict format.
 * @param copy Modifiable buffer with "R,G,B".
 * @param r Output red.
 * @param g Output green.
 * @param b Output blue.
 * @return true on success; false or prints error on malformed tokens.
 * @details Ensures each token is fully consumed (no trailing chars)
 * and no extra components.
 */
static bool	extract_components(char *copy, long *r, long *g, long *b)
{
	char	*tok;
	char	*end;

	tok = ft_strtok(copy, ",");
	if (!tok)
		return (false);
	*r = ft_strtol(tok, &end, 10);
	if (*end != '\0')
		return (printf("Error\nInvalid R component format\n"), false);
	tok = ft_strtok(NULL, ",");
	if (!tok)
		return (false);
	*g = ft_strtol(tok, &end, 10);
	if (*end != '\0')
		return (printf("Error\nInvalid G component format\n"), false);
	tok = ft_strtok(NULL, ",");
	if (!tok)
		return (false);
	*b = ft_strtol(tok, &end, 10);
	if (*end != '\0')
		return (printf("Error\nInvalid B component format\n"), false);
	if (ft_strtok(NULL, ",") != NULL)
		return (printf("Error\nToo many color components\n"), false);
	return (true);
}

/**
 * @brief Parse a color string "R,G,B" with 0..255 integers
 * into normalized t_color.
 * @param str Input C-string.
 * @param out Output color with channels in [0,1].
 * @return true on success; false on validation/allocation errors.
 */
bool	parse_color(const char *str, t_color *out)
{
	char	*copy;
	long	r;
	long	g;
	long	b;

	copy = ft_strdup(str);
	if (!copy)
		return (false);
	if (!extract_components(copy, &r, &g, &b))
		return (free(copy), false);
	free(copy);
	if (!color_range_valid(r, g, b))
	{
		printf("Error\nColor out of range [0,255]\n");
		return (false);
	}
	out->r = (float)r / 255.0f;
	out->g = (float)g / 255.0f;
	out->b = (float)b / 255.0f;
	return (true);
}
