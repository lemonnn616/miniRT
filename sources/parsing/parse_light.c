/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:11 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/23 13:44:46 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

bool parse_light(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		fprintf(stderr, "Error\nInvalid light format\n");
		return false;
	}
	t_vec3 pos;
	if (!parse_vector(tokens[1], &pos))
		return false;
	float intensity = strtof(tokens[2], NULL); // todo
	if (intensity < 0.0f || intensity > 1.0f)
	{
		fprintf(stderr, "Error\nLight intensity out of range [0,1]\n");
		return false;
	}
	t_color col;
	if (!parse_color(tokens[3], &col))
		return false;
	t_light *l = malloc(sizeof(*l));
	if (!l)
	{
		perror("malloc");
		return false;
	}
	l->pos = pos;
	l->intensity = intensity;
	l->color = col;
	l->next = scene->lights;
	scene->lights = l;
	return true;
}
