/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:24:43 by iriadyns          #+#    #+#             */
/*   Updated: 2025/06/29 13:42:40 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdbool.h>
# include "MLX42.h"

# define CAMERA_SPEED 2.5f

typedef struct s_keys
{
	bool w;
	bool a;
	bool s;
	bool d;
}	t_keys;

void	mouse_move(double mx, double my, void *param);
void	key_cb(mlx_key_data_t key, void *param);
void	update_cb(void *param);

#endif