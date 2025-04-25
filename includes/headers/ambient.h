/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:25:51 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 12:37:38 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_H
# define AMBIENT_H

# include "color.h"
# include <stdbool.h>

typedef struct s_ambient
{
	float	intensity;
	t_color	color;
	bool	is_set;
}	t_ambient;

#endif
