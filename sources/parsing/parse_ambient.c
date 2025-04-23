/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:05 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/23 13:42:29 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

bool	parse_ambient(char **tokens, t_scene *scene)
{
	if (scene->ambient.is_set)
	{
		fprintf(stderr, "Error\nAmbient already defined\n");
		return false;
	}
	if (!tokens[1] || !tokens[2] || tokens[3])
	{
		fprintf(stderr, "Error\nInvalid ambient format\n");
		return false;
	}
	float ratio = strtof(tokens[1], NULL); // todo
	if (ratio < 0.0f || ratio > 1.0f) {
		fprintf(stderr, "Error\nAmbient ratio out of range [0,1]\n");
		return false;
	}
	t_color col;
	if (!parse_color(tokens[2], &col))
		return false;

	scene->ambient.intensity = ratio;
	scene->ambient.color = col;
	scene->ambient.is_set = true;
	return true;
}