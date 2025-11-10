/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:21:23 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 11:20:49 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "rt_math.h"
# include "material.h"
# include "quaternion.h"

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_quat		orient;
	t_vec3		normal0;
	t_material	mat;
	bool		use_checker;
	float		checker_size;
	t_color		checker_alt;
	t_vec3		u_axis;
	t_vec3		v_axis;
}	t_plane;

#endif
