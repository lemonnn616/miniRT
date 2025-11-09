/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:29:36 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:24:10 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <string.h>
#include "libft.h"

/**
 * @brief Tokenizes a string in-place using
 * a set of delimiter characters (non re-entrant).
 * @param str Input string for first call; NULL for subsequent calls to continue.
 * @param delim Set of delimiter characters.
 * @return Pointer to next token, or NULL if no more tokens.
 * @details Modifies the input buffer by inserting '\0'.
 * Uses a static internal state; not thread-safe.
 */
char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*start;
	char		*p;

	if (str)
		last = str;
	if (!last)
		return (NULL);
	start = last;
	while (*start && ft_strchr(delim, *start))
		start++;
	if (!*start)
		return (last = NULL, NULL);
	p = start;
	while (*p && !ft_strchr(delim, *p))
		p++;
	if (*p)
	{
		*p = '\0';
		last = p + 1;
	}
	else
		last = NULL;
	return (start);
}
