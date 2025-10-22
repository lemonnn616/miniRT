/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:26 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/22 18:51:07 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static bool	validate_sphere_tokens(char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		printf("Error\nInvalid sphere format\n");
		return (false);
	}
	if (tokens[6])
	{
		printf("Error\nInvalid sphere format\n");
		return (false);
	}
	return (true);
}


static bool	fill_sphere_data(t_sphere *sp, char **tokens)
{
	t_vec3	center;
	float	dia;
	char	*end = NULL;

	if (!parse_vector(tokens[1], &center))
		return (false);
	dia = ft_strtof(tokens[2], &end);
	if (*tokens[2] == '\0' || *end != '\0')
		return (printf("Error\nInvalid sphere diameter format\n"), false);
	if (dia <= 0.0f)
	{
		printf("Error\nSphere diameter <= 0\n");
		return (false);
	}
	sp->center = center;
	sp->radius = dia * 0.5f;
	return (true);
}

static void	set_sphere_material(t_sphere *sp, t_color col,
	float shininess, float reflectivity)
{
	sp->mat.color = col;
	sp->mat.diffuse = 0.8f;
	sp->mat.specular = 0.2f;
	sp->mat.shininess = shininess;
	sp->mat.reflectivity = reflectivity;
}

bool	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sp;
	t_object	*obj;
	t_color		col;
	float		shininess;
	float		reflectivity;

	if (!validate_sphere_tokens(tokens))
		return (false);
	sp = malloc(sizeof(*sp));
	if (!sp)
		return (perror("malloc"), false);
	if (!fill_sphere_data(sp, tokens))
		return (free(sp), false);
	if (!parse_color(tokens[3], &col))
		return (free(sp), false);
	shininess = 0.5f;
	reflectivity = 0.1f;
	if (tokens[4] && !parse_shininess(tokens[4], &shininess))
		return (free(sp), false);
	if (tokens[5] && !parse_reflectivity(tokens[5], &reflectivity))
		return (free(sp), false);
	set_sphere_material(sp, col, shininess, reflectivity);
	obj = malloc(sizeof(*obj));
	if (!obj)
		return (perror("malloc"), free(sp), false);
	obj->type = OBJ_SPHERE;
	obj->obj = sp;
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
