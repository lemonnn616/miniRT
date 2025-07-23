/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:29:37 by natallia          #+#    #+#             */
/*   Updated: 2025/07/23 13:10:11 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	*thread_worker(void *arg)
{
	t_thread_ctx	*ctx;

	ctx = arg;
	while (ctx->data->keep_rendering)
		render_pass(ctx->data, ctx->y_start, ctx->y_stride, &ctx->rng);
	return (NULL);
}

static void	init_thread_context(t_data *data, t_thread_ctx *ctx, int id)
{
	uint64_t	initstate;
	uint64_t	initseq;

	ctx->data = data;
	ctx->y_start = id;
	ctx->y_stride = data->nthreads;
	initstate = (uint64_t)time(NULL) ^ (uint64_t)id * SEED_BASE;
	initseq = (uint64_t)id;
	pcg_seed(&ctx->rng, initstate, initseq);
}

static int	set_thread_count(void)
{
	long	nprocessors;

	nprocessors = sysconf(_SC_NPROCESSORS_ONLN);
	if (nprocessors < 1)
		nprocessors = 1;
	return ((int)nprocessors);
}

void	start_progressive_render(t_data *data)
{
	int	i;
	int	ret;

	data->nthreads = set_thread_count();
	data->threads = ft_calloc(data->nthreads, sizeof(*data->threads));
	if (data->threads == NULL)
		exit_error(data, ERR_MEM);
	data->thread_ctx = ft_calloc(data->nthreads, sizeof(*data->thread_ctx));
	if (data->thread_ctx == NULL)
		exit_error(data, ERR_MEM);
	data->keep_rendering = true;
	i = 0;
	while (i < data->nthreads)
	{
		init_thread_context(data, &data->thread_ctx[i], i);
		ret = pthread_create(&data->threads[i], NULL,
				thread_worker, &data->thread_ctx[i]);
		if (ret != 0)
			exit_error_errno(data, ERR_THREAD, ret);
		ret = pthread_detach(data->threads[i]);
		if (ret != 0)
			exit_error_errno(data, ERR_DETACH, ret);
		i++;
	}
}
