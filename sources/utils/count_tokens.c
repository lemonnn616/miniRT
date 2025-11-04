/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:02:40 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:18:04 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Counts the number of C-strings in a NULL-terminated array.
 * @param t Array of char* terminated by NULL.
 * @return Number of tokens (>= 0).
 */
int	count_tokens(char **t)
{
	int	n;

	n = 0;
	while (t && t[n])
		n++;
	return (n);
}
