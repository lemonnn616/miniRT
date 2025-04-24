/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_vactor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:02 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 13:39:10 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

bool parse_vector(const char *str, t_vec3 *out)
{
	char *copy;
	char *tok;

	copy = strdup(str); // libft
	if (!copy)
		return false;
	tok = ft_strtok(copy, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	out->x = ft_strtof(tok, NULL);
	tok = ft_strtok(NULL, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	out->y = ft_strtof(tok, NULL);
	tok = ft_strtok(NULL, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	out->z = ft_strtof(tok, NULL);
	free(copy);
	return true;
}