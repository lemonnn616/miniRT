/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:20:52 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 11:20:49 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "rt_math.h"
# include "material.h"
# include "quaternion.h"

typedef struct s_sphere
{
	t_vec3		center;
	float		radius;
	t_material	mat;
}	t_sphere;

#endif
