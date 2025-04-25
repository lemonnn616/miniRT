/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:23:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 12:33:05 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "vec3.h"
# include "material.h"

typedef struct s_square
{
	t_vec3		center;
	t_vec3		normal;
	float		side;
	t_material	mat;
}	t_square;

#endif
