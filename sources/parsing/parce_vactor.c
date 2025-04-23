/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_vactor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:34:02 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/23 13:50:09 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool parse_vector(const char *str, t_vec3 *out)
{
	char *copy;
	char *tok;

	copy = strdup(str); // libft
	if (!copy)
		return false;
	tok = strtok(copy, ","); // libft
	if (!tok)
	{
		free(copy);
		return false;
	}
	out->x = strtof(tok, NULL);
	tok = strtok(NULL, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	out->y = strtof(tok, NULL);
	tok = strtok(NULL, ",");
	if (!tok)
	{
		free(copy);
		return false;
	}
	out->z = strtof(tok, NULL);
	free(copy);
	return true;
}