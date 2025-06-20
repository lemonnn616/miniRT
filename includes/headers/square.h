/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:23:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/20 15:17:47 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "vec3.h"
# include "material.h"
# include "quaternion.h"

typedef struct s_square
{
	t_vec3		center;
	t_vec3		normal;
	float		side;
	t_quat		orient;
	t_vec3		normal0;
	t_material	mat;
}	t_square;

#endif
