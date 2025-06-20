/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:16 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/20 15:27:04 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static bool	validate_plane_tokens(char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		printf("Error\nInvalid plane format\n");
		return (false);
	}
	return (true);
}

static bool	fill_plane_data(t_plane *pl, char **tokens)
{
	t_vec3		point;
	t_vec3		normal;

	if (!parse_vector(tokens[1], &point))
		return (false);
	if (!parse_vector(tokens[2], &normal))
		return (false);
	pl->point = point;
	pl->normal0 = vec_normalize(normal);
	pl->normal = pl->normal0;
	pl->orient = (t_quat){ 1.0f, {0,0,0} }; 
	return (true);
}

static void	set_plane_material(t_plane *pl, t_color col)
{
	pl->mat.color = col;
	pl->mat.diffuse = 1.0f;
	pl->mat.specular = 0.0f;
	pl->mat.shininess = 0.0f;
	pl->mat.reflectivity = 0.0f;
}

bool	parse_plane(char **tokens, t_scene *scene)
{
	t_plane		*pl;
	t_object	*obj;
	t_color		col;

	if (!validate_plane_tokens(tokens))
		return (false);
	pl = malloc(sizeof(*pl));
	if (!pl)
		return (perror("malloc"), false);
	if (!fill_plane_data(pl, tokens))
		return (free(pl), false);
	if (!parse_color(tokens[3], &col))
		return (free(pl), false);
	set_plane_material(pl, col);
	obj = malloc(sizeof(*obj));
	if (!obj)
		return (perror("malloc"), free(pl), false);
	obj->type = OBJ_PLANE;
	obj->obj = pl;
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
