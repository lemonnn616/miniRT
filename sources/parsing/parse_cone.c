/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:44:46 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/20 15:11:31 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static bool	validate_cone_tokens(char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3]
		|| !tokens[4] || !tokens[5] || tokens[6])
	{
		printf("Error\nInvalid cone format\n");
		return (false);
	}
	return (true);
}

static bool	parse_cone_data(t_cone *co, char **tokens)
{
	if (!parse_vector(tokens[1], &co->apex))
		return (false);
	if (!parse_vector(tokens[2], &co->axis))
		return (false);
	co->axis0 = vec_normalize(co->axis);
	co->axis = co->axis0;
	co->orient = (t_quat){ 1.0f, {0,0,0} };
	co->angle = ft_strtof(tokens[3], NULL);
	co->height = ft_strtof(tokens[4], NULL);
	if (co->angle <= 0.0f || co->angle >= 180.0f || co->height <= 0.0f)
	{
		printf("Error\nCone parameters out of range\n");
		return (false);
	}
	return (true);
}

static bool	parse_cone_color(t_cone *co, const char *str)
{
	t_color	col;

	if (!parse_color(str, &col))
		return (false);
	co->mat.color = col;
	co->mat.diffuse = 1.0f;
	co->mat.specular = 0.0f;
	co->mat.shininess = 0.0f;
	co->mat.reflectivity = 0.0f;
	return (true);
}

bool	parse_cone(char **tokens, t_scene *scene)
{
	t_cone		*co;
	t_object	*obj;

	if (!validate_cone_tokens(tokens))
		return (false);
	co = malloc(sizeof(*co));
	if (!co)
		return (perror("malloc"), false);
	if (!parse_cone_data(co, tokens))
		return (free(co), false);
	if (!parse_cone_color(co, tokens[5]))
		return (free(co), false);
	obj = malloc(sizeof(*obj));
	if (!obj)
		return (perror("malloc"), free(co), false);
	obj->type = OBJ_CONE;
	obj->obj = co;
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
