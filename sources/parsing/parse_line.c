/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:13 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:54:57 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"

/**
 * @brief Dispatch parser by identifier token
 * ("R","A","C","L","sp","pl","cy","co").
 * @param tokens Token array for a single line.
 * @param scene Scene to fill.
 * @param ok Out flag: set to true if the specific parser succeeded.
 * @return true if identifier recognized (even if parse failed);
 * false if unknown id.
 */
static bool	handle_identifier(char **tokens, t_scene *scene, bool *ok)
{
	if (ft_strcmp(tokens[0], "R") == 0)
		*ok = parse_resolution(tokens, scene);
	else if (ft_strcmp(tokens[0], "A") == 0)
		*ok = parse_ambient(tokens, scene);
	else if (ft_strcmp(tokens[0], "C") == 0)
		*ok = parse_camera(tokens, scene);
	else if (ft_strcmp(tokens[0], "L") == 0)
		*ok = parse_light(tokens, scene);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		*ok = parse_sphere(tokens, scene);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		*ok = parse_plane(tokens, scene);
	else if (ft_strcmp(tokens[0], "cy") == 0)
		*ok = parse_cylinder(tokens, scene);
	else if (ft_strcmp(tokens[0], "co") == 0)
		*ok = parse_cone(tokens, scene);
	else
	{
		printf("Error\nUnknown identifier: %s\n", tokens[0]);
		return (false);
	}
	return (true);
}

/**
 * @brief Tokenize a trimmed scene line and pass to a specific parser.
 * @param line Single scene line (not NULL, already trimmed).
 * @param scene Scene to fill.
 * @return true if a known identifier was parsed successfully; false otherwise.
 * @details Empty input (tokens==NULL or tokens[0]==NULL)
 * is treated as error here;
 * comment/blank lines should be filtered earlier.
 */
bool	parse_line(const char *line, t_scene *scene)
{
	char	**tokens;
	bool	ok;

	tokens = split_whitespace(line);
	if (!tokens || !tokens[0])
		return (free_tokens(tokens), false);
	ok = false;
	handle_identifier(tokens, scene, &ok);
	free_tokens(tokens);
	return (ok);
}
