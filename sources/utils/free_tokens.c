/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:21:21 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 13:42:21 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

void free_tokens(char **tokens)
{
	char **ptr = tokens;

	if (!tokens)
		return;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(tokens);
}
