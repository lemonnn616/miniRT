/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:16 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/29 13:05:13 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static bool	validate_plane_tokens(char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		printf("Error\nInvalid plane format\n");
		return (false);
	}
	return (true);
}

static void	build_plane_axes(t_plane *pl)
{
	float ay = pl->normal.y;
	if (ay < 0.0f)
		ay = -ay;
	t_vec3 up = (ay < 0.999f) ? (t_vec3){0, 1, 0} : (t_vec3){1, 0, 0};
	pl->u_axis = vec_normalize(vec_cross(pl->normal, up));
	pl->v_axis = vec_cross(pl->normal, pl->u_axis);
}

static bool	fill_plane_data(t_plane *pl, char **tokens)
{
	t_vec3	point;
	t_vec3	normal;

	if (!parse_vector(tokens[1], &point))
		return (false);
	if (!parse_vector(tokens[2], &normal))
		return (false);
	if (normal.x < -1.0f || normal.x > 1.0f
			|| normal.y < -1.0f || normal.y > 1.0f
			|| normal.z < -1.0f || normal.z > 1.0f)
		return (printf("Error\nPlane normal components must be in [-1,1]\n"), false);
	if (vec_length(normal) < 1e-6f)
		return (printf("Error\nPlane normal vector is zero\n"), false);
	pl->point = point;
	pl->normal0 = vec_normalize(normal);
	pl->normal = pl->normal0;
	pl->orient = (t_quat){1.0f, {0, 0, 0}};
	pl->use_checker = false;
	pl->checker_size = 1.0f;
	pl->checker_alt = (t_color){0.0f, 0.0f, 0.0f};
	build_plane_axes(pl);
	return (true);
}

static void	set_plane_material(t_plane *pl, t_color col,
	float shininess, float reflectivity)
{
	pl->mat.color = col;
	pl->mat.diffuse = 1.0f;
	pl->mat.specular = 0.0f;
	pl->mat.shininess = shininess;
	pl->mat.reflectivity = reflectivity;
}

static bool	parse_checkerboard(char **tokens, int i, t_plane *pl)
{
	if (!tokens[i])
		return (true);
	if (ft_strcmp(tokens[i], "cb") != 0)
	{
		printf("Error\nInvalid plane format (unexpected token: %s)\n", tokens[i]);
		return (false);
	}
	if (!tokens[i + 1] || !tokens[i + 2])
		return (printf("Error\nInvalid checkerboard format. Use: cb <size> <R,G,B>\n"), false);
	char *end = NULL;
	float size = ft_strtof(tokens[i + 1], &end);
	if (*end != '\0' || size <= 0.0f)
		return (printf("Error\nInvalid checkerboard size\n"), false);
	t_color alt;
	if (!parse_color(tokens[i + 2], &alt))
		return (false);
	pl->use_checker = true;
	pl->checker_size = size;
	pl->checker_alt = alt;
	if (tokens[i + 3])
		return (printf("Error\nInvalid plane format (extra tokens)\n"), false);
	return (true);
}

bool	parse_plane(char **tokens, t_scene *scene)
{
	t_plane		*pl;
	t_object	*obj;
	t_color		col;
	float		shininess = 0.0f;
	float		reflectivity = 0.0f;

	if (!validate_plane_tokens(tokens))
		return (false);
	pl = malloc(sizeof(*pl));
	if (!pl)
		return (perror("malloc"), false);
	if (!fill_plane_data(pl, tokens))
		return (free(pl), false);
	if (!parse_color(tokens[3], &col))
		return (free(pl), false);
	int i = 4;
	if (tokens[i] && ft_strcmp(tokens[i], "cb") != 0)
	{
		if (!parse_shininess(tokens[i], &shininess))
			return (free(pl), false);
		i++;
	}
	if (tokens[i] && ft_strcmp(tokens[i], "cb") != 0)
	{
		if (!parse_reflectivity(tokens[i], &reflectivity))
			return (free(pl), false);
		i++;
	}
	set_plane_material(pl, col, shininess, reflectivity);
	if (!parse_checkerboard(tokens, i, pl))
		return (free(pl), false);
	obj = malloc(sizeof(*obj));
	if (!obj)
		return (perror("malloc"), free(pl), false);
	obj->type = OBJ_PLANE;
	obj->obj = pl;
	obj->next = scene->objects;
	scene->objects = obj;
	return (true);
}
