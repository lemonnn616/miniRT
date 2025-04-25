/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:28:38 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 12:51:32 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static const char	*parse_sign(const char *s, long *sign)
{
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			*sign = -1;
		s++;
	}
	return (s);
}

static const char	*parse_integer(const char *s, float *result)
{
	while (*s >= '0' && *s <= '9')
	{
		*result = *result * 10.0f + (*s - '0');
		s++;
	}
	return (s);
}

static const char	*parse_fraction(const char *s, float *result)
{
	float	frac;
	float	base;

	frac = 0.0f;
	base = 0.1f;
	while (*s >= '0' && *s <= '9')
	{
		frac += (*s - '0') * base;
		base *= 0.1f;
		s++;
	}
	*result += frac;
	return (s);
}

float	ft_strtof(const char *nptr, char **endptr)
{
	const char	*s;
	long		sign;
	float		result;

	s = nptr;
	sign = 1;
	result = 0.0f;
	s = parse_sign(s, &sign);
	s = parse_integer(s, &result);
	if (*s == '.')
	{
		s++;
		s = parse_fraction(s, &result);
	}
	if (endptr)
		*endptr = (char *)s;
	return (result * sign);
}
