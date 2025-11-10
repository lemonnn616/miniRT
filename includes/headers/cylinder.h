/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:21:59 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 11:20:49 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "rt_math.h"
# include "material.h"
# include "quaternion.h"

typedef struct s_cylinder
{
	t_vec3		base;
	t_vec3		axis;
	float		radius;
	float		height;
	t_quat		orient;
	t_vec3		axis0;
	t_material	mat;
}	t_cylinder;

#endif
