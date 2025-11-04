/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:22 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/29 18:01:35 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

static void	setup_camera_basis(t_camera *cam)
{
	while (cam)
	{
		cam->orient = quat_from_two_vecs((t_vec3){0, 0, -1}, cam->dir);
		camera_compute_basis(cam);
		cam = cam->next;
	}
}

static bool	process_line(char *line, t_scene *scene)
{
	char	*trimmed;
	bool	ok;

	trimmed = ft_strtrim(line, " \t\n\r\v\f");
	free(line);
	char *hash = ft_strchr(trimmed, '#');
	if (hash)
		*hash = '\0';
	char *retrim = ft_strtrim(trimmed, " \t\n\r\v\f");
	free(trimmed);
	trimmed = retrim;
	if (trimmed[0] == '\0')
		return (free(trimmed), true);
	ok = parse_line(trimmed, scene);
	return (free(trimmed), ok);
}

bool	parse_scene(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	scene->width = DEFAULT_WIDTH;
	scene->height = DEFAULT_HEIGHT;
	scene->resolution_set = false;
	scene->cameras = NULL;
	scene->active_cam = NULL;
	scene->lights = NULL;
	scene->objects = NULL;
	scene->ambient.is_set = false;
	scene->ambient.intensity = 0.0f;
	scene->ambient.color = (t_color){1.0f, 1.0f, 1.0f};
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("open"), false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!process_line(line, scene))
			return (close(fd), false);
	}
	close(fd);
	if (!scene->ambient.is_set || !scene->cameras || !scene->lights)
		return (printf("Error\nMissing ambient, camera or light\n"), false);
	setup_camera_basis(scene->cameras);
	if (!scene->active_cam)
		scene->active_cam = scene->cameras;
	return (true);
}
