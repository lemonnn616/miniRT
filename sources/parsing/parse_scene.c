/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:22 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 18:37:48 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

/**
 * @brief Initializes the orientation and orthonormal basis for every camera.
 * @param cam Head of the camera linked list.
 * @return None.
 * @details Computes quaternion mapping (0,0,-1) to cam->dir, then derives
 * (dir, up, right) orthonormal basis via camera_compute_basis().
 */
static void	setup_camera_basis(t_camera *cam)
{
	while (cam)
	{
		cam->orient = quat_from_two_vecs((t_vec3){0, 0, -1}, cam->dir);
		camera_compute_basis(cam);
		cam = cam->next;
	}
}

/**
 * @brief Preprocess a raw line: trim,
 * strip trailing comment '#', re-trim, then parse.
 * @param line Heap-allocated line from get_next_line(); will be freed.
 * @param scene Scene to fill.
 * @return true if the (possibly empty) line was handled successfully;
 * false on parse error.
 */
static bool	process_line(char *line, t_scene *scene)
{
	char	*trimmed;
	char	*hash;
	char	*retrim;
	bool	ok;

	if (!line)
		return (true);
	trimmed = ft_strtrim(line, " \t\n\r\v\f");
	free(line);
	if (!trimmed)
		return (perror("ft_strtrim"), false);
	hash = ft_strchr(trimmed, '#');
	if (hash)
		*hash = '\0';
	retrim = ft_strtrim(trimmed, " \t\n\r\v\f");
	free(trimmed);
	if (!retrim)
		return (perror("ft_strtrim"), false);
	trimmed = retrim;
	if (trimmed[0] == '\0')
		return (free(trimmed), true);
	ok = parse_line(trimmed, scene);
	free(trimmed);
	return (ok);
}

/**
 * @brief Initialize scene with defaults and empty lists.
 * @param s Scene to init.
 */
static void	scene_init_defaults(t_scene *s)
{
	s->width = DEFAULT_WIDTH;
	s->height = DEFAULT_HEIGHT;
	s->resolution_set = false;
	s->cameras = NULL;
	s->active_cam = NULL;
	s->lights = NULL;
	s->objects = NULL;
	s->ambient.is_set = false;
	s->ambient.intensity = 0.0f;
	s->ambient.color.r = 1.0f;
	s->ambient.color.g = 1.0f;
	s->ambient.color.b = 1.0f;
}

/**
 * @brief Read all lines from fd and process them.
 * @param fd Open file descriptor.
 * @param scene Target scene.
 * @return true on success; false on error (fd remains open).
 */
static bool	scene_read_loop(int fd, t_scene *scene)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!process_line(line, scene))
			return (false);
	}
	return (true);
}

/**
 * @brief Validate required entities and finalize scene.
 * @param scene Scene.
 * @return true if valid; false otherwise.
 */
static bool	scene_finalize(t_scene *scene)
{
	if (!scene->ambient.is_set || !scene->cameras || !scene->lights)
	{
		printf("Error\nMissing ambient, camera or light\n");
		return (false);
	}
	setup_camera_basis(scene->cameras);
	if (!scene->active_cam)
		scene->active_cam = scene->cameras;
	return (true);
}

/**
 * @brief Parse a .rt scene file and populate the scene structure.
 * @param filename Path to the .rt file.
 * @param scene Output scene; will be initialized inside.
 * @return true on success; false on I/O or semantic/validation errors.
 * @details Requires at least one ambient, camera and light. Builds camera bases,
 * sets active_cam if missing. Leaves scene lists on success.
 */
bool	parse_scene(const char *filename, t_scene *scene)
{
	int	fd;

	scene_init_defaults(scene);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("open"), false);
	if (!scene_read_loop(fd, scene))
		return (close(fd), false);
	close(fd);
	if (!scene_finalize(scene))
		return (false);
	return (true);
}
