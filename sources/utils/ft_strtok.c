/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:29:36 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 14:16:53 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <string.h>
#include "libft.h"

char *ft_strtok(char *str, const char *delim)
{
	static char *last;
	char *start;

	if (str)
		last = str;
	if (!last)
		return NULL;
	start = last;
	while (*start && ft_strchr(delim, *start))
		start++;
	if (!*start)
	{
		last = NULL;
		return NULL;
	}
	char *p = start;
	while (*p && !ft_strchr(delim, *p))
		p++;
	if (*p)
	{
		*p = '\0';
		last = p + 1;
	}
	else
	{
		last = NULL;
	}
	return start;
}
