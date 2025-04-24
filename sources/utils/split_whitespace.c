/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:20:05 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 14:16:37 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include "libft.h"

char **split_whitespace(const char *s)
{
	size_t i = 0, count = 0;
	char **res;

	while (s[i]) {
		while (s[i] && ft_isspace((unsigned char)s[i]))
			i++;
		if (s[i]) {
			count++;
			while (s[i] && !ft_isspace((unsigned char)s[i]))
				i++;
		}
	}
	res = malloc((count + 1) * sizeof(*res));
	if (!res)
		return NULL;
	i = 0;
	size_t idx = 0;
	while (s[i]) {
		while (s[i] && ft_isspace((unsigned char)s[i]))
			i++;
		if (s[i]) {
			size_t start = i;
			while (s[i] && !ft_isspace((unsigned char)s[i]))
				i++;
			size_t len = i - start;
			res[idx] = malloc(len + 1);
			if (!res[idx]) {
				for (size_t j = 0; j < idx; j++)
					free(res[j]);
				free(res);
				return NULL;
			}
			ft_memcpy(res[idx], s + start, len);
			res[idx][len] = '\0';
			idx++;
		}
	}
	res[idx] = NULL;
	return res;
}
