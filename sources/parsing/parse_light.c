/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:11 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 13:42:46 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

bool	parse_light(char **tokens, t_scene *scene)
{
	t_vec3	pos;
	float	intensity;
	t_color	col;
	t_light	*l;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (printf("Error\nInvalid light format\n"), false);
	if (!parse_vector(tokens[1], &pos))
		return (false);
	intensity = ft_strtof(tokens[2], NULL);
	if (intensity < 0.0f || intensity > 1.0f)
		return (printf("Error\nLight intensity out of range [0,1]\n"), false);
	if (!parse_color(tokens[3], &col))
		return (false);
	l = malloc(sizeof(*l));
	if (!l)
		return (perror("malloc"), false);
	l->pos = pos;
	l->intensity = intensity;
	l->color = col;
	l->next = scene->lights;
	scene->lights = l;
	return (true);
}
