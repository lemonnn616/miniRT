/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:00 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/23 13:51:19 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool parse_color(const char *str, t_color *out)
{
	char *copy;
	char *tok;
	long r, g, b;

	copy = strdup(str);
	if (!copy)
		return false;
	tok = strtok(copy, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	r = strtol(tok, NULL, 10);
	tok = strtok(NULL, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	g = strtol(tok, NULL, 10);
	tok = strtok(NULL, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	b = strtol(tok, NULL, 10);
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