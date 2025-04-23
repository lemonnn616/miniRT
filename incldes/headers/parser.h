/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:55 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/23 12:32:07 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "scene.h"
#include <stdbool.h>

bool parse_scene(const char *filename, t_scene *scene);
bool parse_line(const char *line, t_scene *scene);
bool parse_ambient(char **tokens, t_scene *scene);
bool parse_camera(char **tokens, t_scene *scene);
bool parse_light(char **tokens, t_scene *scene);
bool parse_sphere(char **tokens, t_scene *scene);
bool parse_plane(char **tokens, t_scene *scene);
bool parse_cylinder(char **tokens, t_scene *scene);
bool parse_vector(const char *str, t_vec3 *out);
bool parse_color(const char *str, t_color *out);

#endif
