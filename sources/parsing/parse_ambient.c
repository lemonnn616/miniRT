/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:05 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 13:00:54 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

bool	parse_ambient(char **tokens, t_scene *scene)
{
	t_color	col;
	float	ratio;

	if (scene->ambient.is_set)
	{
		printf("Error\nAmbient already defined\n");
		return (false);
	}
	if (!tokens[1] || !tokens[2] || tokens[3])
	{
		printf("Error\nInvalid ambient format\n");
		return (false);
	}
	ratio = ft_strtof(tokens[1], NULL);
	if (ratio < 0.0f || ratio > 1.0f)
	{
		printf("Error\nAmbient ratio out of range [0,1]\n");
		return (false);
	}
	if (!parse_color(tokens[2], &col))
		return (false);
	scene->ambient.intensity = ratio;
	scene->ambient.color = col;
	scene->ambient.is_set = true;
	return (true);
}
