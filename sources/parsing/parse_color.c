/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:32:07 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 14:32:08 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

bool parse_color(const char *str, t_color *out)
{
	char *copy;
	char *tok;
	long r, g, b;

	copy = ft_strdup(str);
	if (!copy)
		return false;
	tok = ft_strtok(copy, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	r = ft_strtol(tok, NULL, 10);
	tok = ft_strtok(NULL, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	g = ft_strtol(tok, NULL, 10);
	tok = ft_strtok(NULL, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	b = ft_strtol(tok, NULL, 10);
	free(copy);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		fprintf(stderr, "Error\nColor out of range [0,255]\n");
		return false;
	}
	out->r = (uint8_t)r;
	out->g = (uint8_t)g;
	out->b = (uint8_t)b;
	return true;
}