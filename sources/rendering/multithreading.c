/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:29:37 by natallia          #+#    #+#             */
/*   Updated: 2025/09/26 21:35:27 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static bool	wait_for_work(t_data *data, uint32_t *frame)
{
	pthread_mutex_lock(&data->render_lock);
	while (!data->rendering_on && !data->should_stop)
		pthread_cond_wait(&data->render_cond, &data->render_lock);
	if (data->should_stop)
	{
		pthread_mutex_unlock(&data->render_lock);
		return (false);
	}
	*frame = data->frame_id;
	pthread_mutex_unlock(&data->render_lock);
	return (true);
}

static void	*thread_worker(void *arg)
{
	t_thread_ctx	*ctx;
	t_data			*d;
	uint32_t		frame;

	ctx = (t_thread_ctx *)arg;
	d = ctx->data;
	while (ETERNITY)
	{
		if (!wait_for_work(d, &frame))
			break ;
		while (ETERNITY)
		{
			render_pass(d, ctx->y_start, ctx->y_stride, &ctx->rng);
			pthread_mutex_lock(&d->render_lock);
			if (d->should_stop || d->frame_id != frame || !d->rendering_on)
			{
				pthread_mutex_unlock(&d->render_lock);
				break ;
			}
			pthread_mutex_unlock(&d->render_lock);
		}
	}
	return (NULL);
}

static void	init_thread_context(t_data *data, t_thread_ctx *ctx, int id)
{
	uint64_t	initstate;
	uint64_t	initseq;

	ctx->data = data;
	ctx->y_start = id;
	ctx->y_stride = data->nthreads;
	initstate = ((uint64_t)time(NULL) ^ ((uint64_t)id * SEED_BASE));
	initseq = (uint64_t)id;
	pcg_seed(&ctx->rng, initstate, initseq);
}

static void	initialise_render_threads(t_data *data)
{
	int	i;

	if (data->pool_started)
		return ;
	data->threads = ft_calloc(data->nthreads, sizeof(*data->threads));
	if (!data->threads)
		exit_error(data, ERR_MEM);
	data->thread_ctx = ft_calloc(data->nthreads, sizeof(*data->thread_ctx));
	if (!data->thread_ctx)
		exit_error(data, ERR_MEM);
	if (pthread_mutex_init(&data->render_lock, NULL) != 0)
		exit_error(data, ERR_MUTEX);
	if (pthread_cond_init(&data->render_cond, NULL) != 0)
		exit_error(data, ERR_MUTEX);
	i = 0;
	while (i < data->nthreads)
	{
		init_thread_context(data, &data->thread_ctx[i], i);
		if (pthread_create(&data->threads[i], NULL,
				thread_worker, &data->thread_ctx[i]) != 0)
			exit_error(data, ERR_THREAD);
		data->nthreads_success++;
		i++;
	}
	data->pool_started = true;
}

void	start_progressive_render(t_data *data)
{
	long	nprocessors;

	if (!data->pool_started)
	{
		nprocessors = sysconf(_SC_NPROCESSORS_ONLN);
		if (nprocessors < 1)
			nprocessors = 1;
		data->nthreads = (int)nprocessors;
		data->nthreads_success = 0;
		data->frame_id = 0;
		data->should_stop = false;
		data->rendering_on = false;
		initialise_render_threads(data);
	}
	pthread_mutex_lock(&data->render_lock);
	data->frame_id++;
	data->rendering_on = true;
	pthread_cond_broadcast(&data->render_cond);
	pthread_mutex_unlock(&data->render_lock);
}
