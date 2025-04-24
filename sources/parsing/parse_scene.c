/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:22 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 14:26:05 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

bool	parse_scene(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;
	char	*trimmed;

	scene->width = DEFAULT_WIDTH;
	scene->height = DEFAULT_HEIGHT;
	scene->resolution_set = false;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return false;
	}
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		trimmed = ft_strtrim(line, " \t\n\r\v\f");
		free(line);
		if (trimmed[0] == '\0' || trimmed[0] == '#')
		{
			free(trimmed);
			continue;
		}
		if (!parse_line(trimmed, scene))
		{
			free(trimmed);
			close(fd);
			return false;
		}
		free(trimmed);
	}
	close(fd);
	if (!scene->ambient.is_set || !scene->cameras || !scene->lights)
	{
		fprintf(stderr, "Error\nMissing ambient, camera or light\n");
		return false;
	}
	{
		t_camera *cam = scene->cameras;
		while (cam)
		{
			// TODO: camera_compute_basis(cam); // count basis for camera
			cam = cam->next;
		}
	}
	return true;
}