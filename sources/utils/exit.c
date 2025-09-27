/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:26:24 by natallia          #+#    #+#             */
/*   Updated: 2025/09/26 19:28:36 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_error(t_data *data, char *msg)
{
	free_data(data);
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	exit_error_errno(t_data *data, char *msg, int errcode)
{
	free_data(data);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errcode), 2);
	exit(EXIT_FAILURE);
}

void	exit_success(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}
