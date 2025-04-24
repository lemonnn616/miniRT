/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:28:38 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/24 13:42:22 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

float ft_strtof(const char *nptr, char **endptr)
{
	const char *s = nptr;
	long sign = 1;
	float result = 0.0f;

	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10.0f + (*s - '0');
		s++;
	}
	if (*s == '.')
	{
		s++;
		float frac = 0.0f;
		float base = 0.1f;
		while (*s >= '0' && *s <= '9')
		{
			frac += (*s - '0') * base;
			base *= 0.1f;
			s++;
		}
		result += frac;
	}
	if (endptr)
		*endptr = (char *)s;
	return result * sign;
}
