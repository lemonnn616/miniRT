/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:20:05 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 17:24:52 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include "libft.h"

static size_t	count_words(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace((unsigned char)s[i]))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !ft_isspace((unsigned char)s[i]))
				i++;
		}
	}
	return (count);
}

static void	free_words(char **res, size_t last)
{
	size_t	i;

	i = 0;
	while (i < last)
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static char	*alloc_word(const char *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static int	fill_words(char **res, const char *s)
{
	size_t	i;
	size_t	idx;
	size_t	start;

	i = 0;
	idx = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace((unsigned char)s[i]))
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && !ft_isspace((unsigned char)s[i]))
				i++;
			res[idx] = alloc_word(s, start, i);
			if (!res[idx])
				return (free_words(res, idx), 0);
			idx++;
		}
	}
	res[idx] = NULL;
	return (1);
}

/**
 * @brief Splits a string into tokens separated by ASCII whitespace.
 * @param s Input C-string to split.
 * @return NULL-terminated array of newly allocated C-strings,
 * or NULL on allocation failure.
 * @details Caller must free with free_tokens().
 * Uses count_words() and fill_words() internally.
 */
char	**split_whitespace(const char *s)
{
	char	**res;
	size_t	count;

	count = count_words(s);
	res = (char **)malloc((count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	if (!fill_words(res, s))
		return (NULL);
	return (res);
}
