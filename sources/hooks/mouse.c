/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:15:28 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 12:51:43 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"

/**
 * @brief Clamp x to [a,b].
 * @param x Value.
 * @param a Min bound.
 * @param b Max bound.
 * @return Clamped value.
 */
static float	clampf(float x, float a, float b)
{
	if (x < a)
		return (a);
	if (x > b)
		return (b);
	return (x);
}

/**
 * @brief Switch to preview render (1 spp, 0 bounces) and restart.
 * @param d Runtime data.
 * @return None.
 */
static void	rt_preview_restart(t_data *d)
{
	d->preview_mode = true;
	d->max_rays = 1;
	d->max_bounces = 0;
	d->last_move_time = mlx_get_time();
	reset_pixel_buffer(d);
	start_progressive_render(d);
}

/**
 * @brief Recompute orientation and basis from yaw/pitch.
 * @param cam Camera to update.
 * @return None.
 * @details R = R_pitch(right_after_yaw,pitch) * R_yaw(world_up,yaw).
 */
static void	camera_from_angles(t_camera *cam)
{
	t_quat	q_yaw;
	t_quat	q_pitch;
	t_vec3	right_after_yaw;

	q_yaw = quat_from_axis_angle((t_vec3){0.0f, 1.0f, 0.0f}, cam->yaw);
	right_after_yaw = quat_rotate_vec((t_vec3){1.0f, 0.0f, 0.0f}, q_yaw);
	right_after_yaw = vec_normalize(right_after_yaw);
	q_pitch = quat_from_axis_angle(right_after_yaw, cam->pitch);
	cam->orient = quat_mul(q_pitch, q_yaw);
	cam->orient = quat_normalize(cam->orient);
	camera_compute_basis(cam);
}

/**
 * @brief Init per-camera yaw/pitch from current dir once.
 * @param cam Camera.
 * @return None.
 */
static void	cam_angles_init_if_needed(t_camera *cam)
{
	float	y;
	float	p;
	float	cy;

	if (cam->angles_set)
		return ;
	y = atan2f(cam->dir.x, -cam->dir.z);
	cy = clampf(cam->dir.y, -1.0f, 1.0f);
	p = asinf(cy);
	cam->yaw = y;
	cam->pitch = p;
	cam->angles_set = true;
}

/**
 * @brief Apply yaw/pitch rotation to active camera.
 * @param d Global runtime.
 * @param cam Active camera.
 * @param dx Delta X (px).
 * @param dy Delta Y (px).
 * @return None.
 */
void	apply_mouse_rotation(t_data *d, t_camera *cam, double dx, double dy)
{
	cam_angles_init_if_needed(cam);
	mouse_update_angles(cam, dx, dy);
	camera_from_angles(cam);
	rt_preview_restart(d);
}
