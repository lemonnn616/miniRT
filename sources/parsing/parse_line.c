/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:13 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 13:41:44 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"

bool parse_line(const char *line, t_scene *scene)
{
	char	**tokens;
	bool	ok;

	tokens = split_whitespace(line);
	if (!tokens || !tokens[0])
	{
		free_tokens(tokens);
		return false;
	}
	ok = false;
	if (strcmp(tokens[0], "R") == 0)
		ok = parse_resolution(tokens, scene);
	else if (strcmp(tokens[0], "A") == 0)
		ok = parse_ambient(tokens, scene);
	else if (strcmp(tokens[0], "C") == 0)
		ok = parse_camera(tokens, scene);
	else if (strcmp(tokens[0], "L") == 0)
		ok = parse_light(tokens, scene);
	else if (strcmp(tokens[0], "sp") == 0)
		ok = parse_sphere(tokens, scene);
	else if (strcmp(tokens[0], "pl") == 0)
		ok = parse_plane(tokens, scene);
	else if (strcmp(tokens[0], "cy") == 0)
		ok = parse_cylinder(tokens, scene);
	else if (strcmp(tokens[0], "co") == 0)
		ok = parse_cone(tokens, scene);
	else
		fprintf(stderr, "Error\nUnknown identifier: %s\n", tokens[0]);
	free_tokens(tokens);
	return ok;
}