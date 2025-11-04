/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:11 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/29 13:04:28 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static bool	validate_light_tokens(char **tokens)
{
	int	n;

	n = count_tokens(tokens);
	if (n < 3 || n > 4)
		return (printf("Error\nInvalid light format\n"), false);
	return (true);
}


static bool	fill_light_data(t_light *l, char **tokens)
{
	if (!parse_vector(tokens[1], &l->pos))
		return (false);
	char *end = NULL;
	l->intensity = ft_strtof(tokens[2], &end);
	if (*tokens[2] == '\0' || *end != '\0')
		return (printf("Error\nInvalid light intensity format\n"), false);
	if (l->intensity < 0.0f || l->intensity > 1.0f)
		return (printf("Error\nLight intensity out of range [0,1]\n"), false);
	if (tokens[3])
	{
		if (!parse_color(tokens[3], &l->color))
			return (false);
	}
	else
	{
		l->color = (t_color){1.0f, 1.0f, 1.0f};
	}
	return (true);
}

bool	parse_light(char **tokens, t_scene *scene)
{
	t_light		*l;
	t_object	*obj;

	if (!validate_light_tokens(tokens))
		return (false);
	l = malloc(sizeof(*l));
	if (!l)
		return (perror("malloc"), false);
	if (!fill_light_data(l, tokens))
		return (free(l), false);
	l->next = scene->lights;
	scene->lights = l;
	obj = malloc(sizeof(*obj));
	if (!obj)
		return (perror("malloc"), free(l), false);
	obj->type = OBJ_LIGHT;
	obj->obj = l;
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
