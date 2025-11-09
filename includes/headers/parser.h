/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:55 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/07 16:47:11 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include <stdbool.h>

# define DEFAULT_WIDTH 800
# define DEFAULT_HEIGHT 600

bool	parse_scene(const char *filename, t_scene *scene);
bool	parse_line(const char *line, t_scene *scene);
bool	parse_ambient(char **tokens, t_scene *scene);
bool	parse_camera(char **tokens, t_scene *scene);
bool	parse_light(char **tokens, t_scene *scene);
bool	parse_sphere(char **tokens, t_scene *scene);
bool	parse_plane(char **tokens, t_scene *scene);
bool	parse_cylinder(char **tokens, t_scene *scene);
bool	parse_vector(const char *str, t_vec3 *out);
bool	parse_color(const char *str, t_color *out);
bool	parse_cone(char **tokens, t_scene *scene);
bool	parse_resolution(char **tokens, t_scene *scene);
bool	parse_shininess(const char *str, float *out);
bool	parse_reflectivity(const char *str, float *out);
bool	validate_sphere_tokens(char **tokens);
void	setup_camera_basis(t_camera *cam);
int		parse_and_set_plane_material(t_plane *pl, const char *color_tok,
			float sh, float re);
bool	fill_plane_data(t_plane *pl, char **tokens);
bool	validate_plane_tokens(char **tokens);
bool	fill_cylinder_data(t_cylinder *cy, char **tokens);
bool	validate_cy_tokens(char **tokens);
int		parse_cylinder_optional(char **tokens, float *sh, float *re);
bool	parse_cone_data(t_cone *co, char **tokens);
bool	validate_cone_tokens(char **tokens);

#endif
