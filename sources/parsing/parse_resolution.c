/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:43:59 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 13:46:24 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

bool	parse_resolution(char **tokens, t_scene *scene)
{
	int	w;
	int	h;

	if (!tokens[1] || !tokens[2] || tokens[3])
	{
		printf("Error\nInvalid resolution format\n");
		return (false);
	}
	w = ft_strtol(tokens[1], NULL, 10);
	h = ft_strtol(tokens[2], NULL, 10);
	if (w <= 0 || h <= 0)
	{
		printf("Error\nResolution must be >0\n");
		return (false);
	}
	scene->width = w;
	scene->height = h;
	scene->resolution_set = true;
	return (true);
}
