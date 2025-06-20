/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:21:59 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/20 15:17:29 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "vec3.h"
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
