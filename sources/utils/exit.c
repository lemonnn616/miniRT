/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:26:24 by natallia          #+#    #+#             */
/*   Updated: 2025/07/23 12:41:07 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_pixels(t_pixel ***pixels, uint32_t y)
{
	uint32_t	i;

	i = 0;
	while (i < y)
	{
		free((*pixels)[i]);
		(*pixels)[i] = NULL;
		i++;
	}
	free(*pixels);
	(*pixels) = NULL;
}

void	free_data(t_data *data)
{
	free_scene(&data->scene);
	if (data->image_buffer)
		mlx_delete_image(data->mlx, data->image_buffer);
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	if (data->pixels)
		free_pixels(&data->pixels, data->scene.height);
}

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
