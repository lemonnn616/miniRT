/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:32:07 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 13:44:29 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

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

static bool	extract_components(char *copy, long *r, long *g, long *b)
{
	char	*tok;

	tok = ft_strtok(copy, ",");
	if (!tok)
		return (false);
	*r = ft_strtol(tok, NULL, 10);
	tok = ft_strtok(NULL, ",");
	if (!tok)
		return (false);
	*g = ft_strtol(tok, NULL, 10);
	tok = ft_strtok(NULL, ",");
	if (!tok)
		return (false);
	*b = ft_strtol(tok, NULL, 10);
	return (true);
}

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
	out->r = (uint8_t)r;
	out->g = (uint8_t)g;
	out->b = (uint8_t)b;
	return (true);
}
