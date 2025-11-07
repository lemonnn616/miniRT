/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:16 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 15:32:33 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Parse optional checkerboard suffix: "cb <size> <R,G,B>".
 * @param tokens Token array.
 * @param i Index where "cb" may appear.
 * @param pl Plane to annotate with checkerboard params.
 * @return true if OK or not present; false on malformed suffix.
 */
static bool	parse_checkerboard(char **tokens, int i, t_plane *pl)
{
	char	*end;
	float	size;
	t_color	alt;

	if (!tokens[i])
		return (true);
	if (ft_strcmp(tokens[i], "cb") != 0)
		return (printf("Error\nInvalid plane format\n"), false);
	if (!tokens[i + 1] || !tokens[i + 2])
	{
		printf("Error\nInvalid checkerboard format.\n");
		return (printf("Use: cb <size> <R,G,B>\n"), false);
	}
	end = NULL;
	size = ft_strtof(tokens[i + 1], &end);
	if (tokens[i + 1][0] == '\0' || end == NULL || *end != '\0' || size <= 0.0f)
		return (printf("Error\nInvalid checkerboard size\n"), false);
	if (!parse_color(tokens[i + 2], &alt))
		return (false);
	pl->use_checker = true;
	pl->checker_size = size;
	pl->checker_alt = alt;
	if (tokens[i + 3])
		return (printf("Error\nInvalid plane format (extra tokens)\n"), false);
	return (true);
}

/**
 * @brief Parse optional shininess/reflectivity starting at index i.
 * @param tokens Token array.
 * @param i Start index (after color).
 * @param sh Out shininess (default 0).
 * @param re Out reflectivity (default 0).
 * @return Next index on success (>= i); -1 on error.
 */
static int	parse_plane_optional(char **tokens, int i, float *sh, float *re)
{
	int	idx;

	*sh = 0.0f;
	*re = 0.0f;
	idx = i;
	if (tokens[idx] && ft_strcmp(tokens[idx], "cb") != 0)
	{
		if (!parse_shininess(tokens[idx], sh))
			return (-1);
		idx++;
	}
	if (tokens[idx] && ft_strcmp(tokens[idx], "cb") != 0)
	{
		if (!parse_reflectivity(tokens[idx], re))
			return (-1);
		idx++;
	}
	return (idx);
}

/**
 * @brief Make an object node for plane.
 * @param pl Plane pointer (owned by object).
 * @return Allocated object or NULL (perror on failure).
 */
static t_object	*make_plane_object(t_plane *pl)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(*obj));
	if (!obj)
	{
		perror("malloc");
		return (NULL);
	}
	obj->type = OBJ_PLANE;
	obj->obj = pl;
	obj->next = NULL;
	return (obj);
}

/**
 * @brief Parse optional params, set material & checkerboard for plane.
 * @param pl Plane.
 * @param tokens Token array.
 * @param i In/out index (starts at 4).
 * @return 1 on success; 0 on error.
 */
static int	set_plane_props(t_plane *pl, char **tokens, int *i)
{
	int		idx;
	float	sh;
	float	re;

	idx = *i;
	sh = 0.0f;
	re = 0.0f;
	idx = parse_plane_optional(tokens, idx, &sh, &re);
	if (idx < 0)
		return (0);
	if (!parse_and_set_plane_material(pl, tokens[3], sh, re))
		return (0);
	if (!parse_checkerboard(tokens, idx, pl))
		return (0);
	*i = idx;
	return (1);
}

/**
 * @brief Parse a plane object line with optional material and checkerboard.
 * @param tokens Token array.
 * @param scene Target scene.
 * @return true on success; false otherwise with diagnostics.
 * @details Syntax: "pl <point> <normal> <R,G,B>
 * [shininess] [reflectivity] [cb <size> <R,G,B>]".
 */
bool	parse_plane(char **tokens, t_scene *scene)
{
	t_plane		*pl;
	t_object	*obj;
	int			i;

	if (!validate_plane_tokens(tokens))
		return (false);
	pl = (t_plane *)malloc(sizeof(*pl));
	if (!pl)
		return (perror("malloc"), false);
	if (!fill_plane_data(pl, tokens))
		return (free(pl), false);
	i = 4;
	if (!set_plane_props(pl, tokens, &i))
		return (free(pl), false);
	obj = make_plane_object(pl);
	if (!obj)
		return (free(pl), false);
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
