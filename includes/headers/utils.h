/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:01:20 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/25 12:30:31 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char	**split_whitespace(const char *s);
void	free_tokens(char **tokens);
long	ft_strtol(const char *nptr, char **endptr, int base);
float	ft_strtof(const char *nptr, char **endptr);
char	*ft_strtok(char *str, const char *delim);

#endif
