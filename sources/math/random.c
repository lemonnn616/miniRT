/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:14:04 by natallia          #+#    #+#             */
/*   Updated: 2025/11/10 11:20:49 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

static float	norm_dist(t_pcg *rng)
{
	float	u1;
	float	u2;
	float	rho;
	float	theta;

	u1 = pcg_random_float(rng);
	u2 = pcg_random_float(rng);
	rho = sqrtf(-2.0f * log(u1));
	theta = 2.0f * PI * u2;
	return (rho * cosf(theta));
}

t_vec3	generate_random_ray(t_pcg *rng)
{
	t_vec3	random;

	random.x = norm_dist(rng);
	random.y = norm_dist(rng);
	random.z = norm_dist(rng);
	random = vec_normalize(random);
	return (random);
}

static uint32_t	pcg_random(t_pcg *rng)
{
	uint64_t	oldstate;
	uint32_t	xorshifted;
	uint32_t	rotate;

	oldstate = rng->state;
	rng->state = oldstate * 6364136223846793005ull + rng->inc;
	xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
	rotate = oldstate >> 59u;
	return ((xorshifted >> rotate) | (xorshifted << ((-rotate) & 31)));
}

float	pcg_random_float(t_pcg *rng)
{
	return ((float)pcg_random(rng) / (float)UINT32_MAX);
}

void	pcg_seed(t_pcg *rng, uint64_t initstate, uint64_t initseq)
{
	rng->state = 0u;
	rng->inc = (initseq << 1u) | 1u;
	pcg_random(rng);
	rng->state += initstate;
	pcg_random(rng);
}
