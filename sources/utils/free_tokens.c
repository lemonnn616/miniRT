/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:21:21 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:24:41 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

/**
 * @brief Frees a NULL-terminated array of
 * C-strings created by split_whitespace().
 * @param tokens Array to free (can be NULL).
 * @return None.
 * @details Frees each token and the array itself;
 * sets no external pointer to NULL.
 */
void	free_tokens(char **tokens)
{
	char	**ptr;

	ptr = tokens;
	if (!tokens)
		return ;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(tokens);
}
