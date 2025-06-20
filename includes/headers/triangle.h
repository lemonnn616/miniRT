/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:39 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/20 15:17:51 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "vec3.h"
# include "material.h"
# include "quaternion.h"

typedef struct s_triangle
{
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
	t_vec3		normal0;
	t_material	mat;
}	t_triangle;

#endif
