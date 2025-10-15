/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:32:12 by iriadyns          #+#    #+#             */
/*   Updated: 2025/10/06 15:03:16 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

bool	parse_vector(const char *str, t_vec3 *out)
{
	char	*copy;
	char	*tok;
	char	*end;

	copy = ft_strdup(str);
	if (!copy)
		return (false);
	tok = ft_strtok(copy, ",");
	if (!tok)
		return (free(copy), false);
	out->x = ft_strtof(tok, &end);
	if (*end != '\0')
		return (free(copy), printf("Error\nInvalid X component format\n"), false);
	tok = ft_strtok(NULL, ",");
	if (!tok)
		return (free(copy), false);
	out->y = ft_strtof(tok, &end);
	if (*end != '\0')
		return (free(copy), printf("Error\nInvalid Y component format\n"), false);
	tok = ft_strtok(NULL, ",");
	if (!tok)
	{
		free(copy);
		return (false);
	}
	out->z = ft_strtof(tok, &end);
	if (*end != '\0')
		return (free(copy), printf("Error\nInvalid Z component format\n"), false);
	if (ft_strtok(NULL, ",") != NULL)
		return (free(copy), printf("Error\nToo many vector components\n"), false);
	free(copy);
	return (true);
}
