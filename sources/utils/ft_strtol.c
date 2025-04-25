/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:24:42 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 12:47:03 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	const char	*s;
	long		sign;
	long		result;

	s = nptr;
	sign = 1;
	result = 0;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s == ' ' || *s == '\t' || *s == '\n'
		|| *s == '\r' || *s == '\f' || *s == '\v')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		result = result * base + (*s - '0');
		s++;
	}
	if (endptr)
		*endptr = (char *)s;
	return (sign * result);
}
