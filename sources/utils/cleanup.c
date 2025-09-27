/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:40:57 by natallia          #+#    #+#             */
/*   Updated: 2025/09/26 21:14:52 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cleanup_threads(t_data *data)
{
	int	i;

	if (!data || data->nthreads_success == 0)
		return ;
	pthread_mutex_lock(&data->render_lock);
	data->should_stop = true;
	data->rendering_on = false;
	data->frame_id++;
	pthread_cond_broadcast(&data->render_cond);
	pthread_mutex_unlock(&data->render_lock);
	i = 0;
	while (i < data->nthreads_success)
		pthread_join(data->threads[i++], NULL);
	pthread_mutex_destroy(&data->render_lock);
	pthread_cond_destroy(&data->render_cond);
	free(data->threads);
	free(data->thread_ctx);
	data->threads = NULL;
	data->thread_ctx = NULL;
	data->nthreads_success = 0;
	data->pool_started = false;
}

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
	if (!data)
		return ;
	if (data->pool_started)
		cleanup_threads(data);
	if (data->mlx && data->image_buffer)
		mlx_delete_image(data->mlx, data->image_buffer);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data->pixels)
		free_pixels(&data->pixels, data->scene.height);
	free_scene(&data->scene);
}
