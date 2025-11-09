/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conjugate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:04:20 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:17:43 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

/**
 * @brief Returns the conjugate of a quaternion.
 * @param q Input quaternion.
 * @return Conjugate qc = [w, -v].
 * @details For unit quaternions, conjugate equals inverse.
 */
t_quat	quat_conj(t_quat q)
{
	t_quat	qc;

	qc.w = q.w;
	qc.v = vec_scale(q.v, -1.0f);
	return (qc);
}
