/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cosine_hemisphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:57:23 by natallia          #+#    #+#             */
/*   Updated: 2025/10/03 11:15:02 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	orthonormal_basis(const t_vec3 normal,
	t_vec3 *tangent, t_vec3 *bitangent)
{
	t_vec3	helper;

	if (fabsf(normal.x) < 0.5f)
		helper = (t_vec3){1.0f, 0.0f, 0.0f};
	else
		helper = (t_vec3){0.0f, 1.0f, 0.0f};
	helper = vec_normalize(helper);
	*tangent = vec_normalize(vec_cross(helper, normal));
	*bitangent = vec_cross(normal, *tangent);
}

static void	sample_concentric_disk(float u1, float u2,
	float *disk_x, float *disk_y)
{
	float	sx;
	float	sy;
	float	radius;
	float	angle;

	sx = 2.0f * u1 - 1.0f;
	sy = 2.0f * u2 - 1.0f;
	if (sx == 0.0f && sy == 0.0f)
	{
		*disk_x = 0.0f;
		*disk_y = 0.0f;
		return ;
	}
	if (fabsf(sx) > fabsf(sy))
	{
		radius = sx;
		angle = (float)M_PI_4 * (sy / sx);
	}
	else
	{
		radius = sy;
		angle = (float)M_PI_2 - (float)M_PI_4 * (sx / sy);
	}
	*disk_x = radius * cosf(angle);
	*disk_y = radius * sinf(angle);
}

static t_vec3	local_cosine_direction(float disk_x, float disk_y)
{
	t_vec3	dir;
	float	z_sq;

	z_sq = 1.0f - (disk_x * disk_x + disk_y * disk_y);
	if (z_sq < 0.0f)
		z_sq = 0.0f;
	dir.x = disk_x;
	dir.y = disk_y;
	dir.z = sqrtf(z_sq);
	return (dir);
}

static t_vec3	local_to_world(const t_vec3 local_dir, const t_vec3 normal)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	world;

	orthonormal_basis(normal, &tangent, &bitangent);
	world.x = tangent.x * local_dir.x + bitangent.x * local_dir.y
		+ normal.x * local_dir.z;
	world.y = tangent.y * local_dir.x + bitangent.y * local_dir.y
		+ normal.y * local_dir.z;
	world.z = tangent.z * local_dir.x + bitangent.z * local_dir.y
		+ normal.z * local_dir.z;
	return (vec_normalize(world));
}

t_vec3	cosine_weighted_hemisphere(t_pcg *rng, const t_vec3 normal)
{
	float	u1;
	float	u2;
	float	dx;
	float	dy;
	t_vec3	local_dir;

	u1 = pcg_random_float(rng);
	u2 = pcg_random_float(rng);
	sample_concentric_disk(u1, u2, &dx, &dy);
	local_dir = local_cosine_direction(dx, dy);
	return (local_to_world(local_dir, normal));
}
