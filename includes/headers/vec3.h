/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:18:27 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 13:33:58 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
#define VEC3_H

#ifndef EPSILON
# define EPSILON 1e-6f
#endif

#include <math.h>

typedef struct s_vec3
{
	float x;
	float y;
	float z;
}	t_vec3;

t_vec3	vec_normalize(t_vec3 v);

#endif
