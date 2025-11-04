/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:32:03 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:39:58 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * @brief Parse a vector token into pos.
 * @param tok Token string.
 * @param pos Output position.
 * @return 1 on success; 0 with error printed otherwise.
 */
static int	parse_pos(const char *tok, t_vec3 *pos)
{
	if (!parse_vector(tok, pos))
		return (printf("Error\nInvalid camera position\n"), 0);
	return (1);
}

/**
 * @brief Parse and validate camera forward direction.
 * @param tok Token string.
 * @param out_dir Output normalized direction.
 * @return 1 on success; 0 with error printed otherwise.
 * @details Enforces components in [-1,1] and non-zero length.
 */
static int	parse_dir(const char *tok, t_vec3 *out_dir)
{
	t_vec3	dir;

	if (!parse_vector(tok, &dir))
		return (printf("Error\nInvalid camera direction\n"), 0);
	if (dir.x < -1.0f || dir.x > 1.0f
		|| dir.y < -1.0f || dir.y > 1.0f
		|| dir.z < -1.0f || dir.z > 1.0f)
		return (printf("Error\nCamera direction"
				"components must be in [-1,1]\n"),
			0);
	if (vec_length(dir) < 1e-6f)
		return (printf("Error\nCamera direction vector is zero\n"), 0);
	*out_dir = vec_normalize(dir);
	return (1);
}

/**
 * @brief Parse FOV in degrees.
 * @param tok Token string.
 * @param out_fov Output FOV.
 * @return 1 on success; 0 with error printed otherwise.
 * @details Accepts only full-string float and enforces (0,180).
 */
static int	parse_fov(const char *tok, float *out_fov)
{
	char	*end;
	float	val;

	end = NULL;
	val = ft_strtof(tok, &end);
	if (tok[0] == '\0' || end == NULL || *end != '\0')
		return (printf("Error\nInvalid FOV format\n"), 0);
	if (val <= 0.0f || val >= 180.0f)
		return (printf("Error\nFOV out of range (0,180)\n"), 0);
	*out_fov = val;
	return (1);
}

/**
 * @brief Parse and push a camera definition.
 * @param tokens Token array.
 * @param scene Target scene.
 * @return true on success; false with error message otherwise.
 * @details Enforces direction components in [-1,1],
 * non-zero length (then normalized),
 * and FOV in (0,180). Orientation is set to identity;
 * basis computed later.
 */
bool	parse_camera(char **tokens, t_scene *scene)
{
	t_camera	*cam;
	t_vec3		pos;
	t_vec3		dir;
	float		fov;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (printf("Error\nInvalid camera format\n"), false);
	if (!parse_pos(tokens[1], &pos) || !parse_dir(tokens[2], &dir)
		|| !parse_fov(tokens[3], &fov))
		return (false);
	cam = (t_camera *)malloc(sizeof(*cam));
	if (!cam)
		return (perror("malloc"), false);
	cam->pos = pos;
	cam->dir = dir;
	cam->orient.w = 1.0f;
	cam->orient.v.x = 0.0f;
	cam->orient.v.y = 0.0f;
	cam->orient.v.z = 0.0f;
	cam->fov = fov;
	cam->next = scene->cameras;
	scene->cameras = cam;
	return (true);
}
