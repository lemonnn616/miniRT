/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:25:09 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 12:35:46 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vec3.h"
# include "color.h"

typedef struct s_light
{
	t_vec3			pos;
	float			intensity;
	t_color			color;
	struct s_light	*next;
}	t_light;

#endif
