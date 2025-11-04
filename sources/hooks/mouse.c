/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:15:28 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/04 18:59:26 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Apply yaw/pitch rotation to the active camera from mouse deltas.
 * @param d Global runtime data (used to toggle preview and restart rendering).
 * @param cam Camera to rotate.
 * @param dx Mouse delta X (pixels).
 * @param dy Mouse delta Y (pixels).
 * @return None.
 * @details Keeps a persistent yaw/pitch accumulator per-camera. Yaw wraps to
 * (-π, π]; pitch is clamped to ±89°. Orientation is composed as:
 *   R = R_pitch(right_yaw, pitch) * R_yaw(world_up, yaw),
 * then the camera basis is recomputed. Switches to preview mode (1 spp, 0 bounces),
 * clears the pixel buffer and restarts progressive rendering.
 * @note Sensitivity is fixed; extremely large deltas are clamped before use.
 */
static void apply_mouse_rotation(t_data *d, t_camera *cam, double dx, double dy)
{
	const float	yaw_sens = 0.002f;
	const float	pitch_sens = 0.002f;
	const float	PITCH_MAX = degree_to_radian(89.0f);
	const t_vec3	WORLD_UP = (t_vec3){0.0f, 1.0f, 0.0f};
	const t_vec3	FWD0 = (t_vec3){0.0f, 0.0f, -1.0f};
	const t_vec3	UP0 = (t_vec3){0.0f, 1.0f,  0.0f};
	static bool		s_init = false;
	static t_camera	*s_cam = NULL;
	static float	s_yaw = 0.0f;
	static float	s_pitch = 0.0f;

	if (!s_init || s_cam != cam)
	{
		s_yaw = atan2f(cam->dir.x, -cam->dir.z);
		s_pitch = asinf(fmaxf(-1.0f, fminf(1.0f, cam->dir.y)));
		s_cam = cam;
		s_init  = true;
	}
	s_yaw += (float)dx * yaw_sens;
	s_pitch += (float)dy * pitch_sens;
	if (s_pitch > PITCH_MAX)
		s_pitch = PITCH_MAX;
	if (s_pitch < -PITCH_MAX)
		s_pitch = -PITCH_MAX;
	if (s_yaw > (float)M_PI)
		s_yaw -= (float)(2.0 * M_PI);
	if (s_yaw < -(float)M_PI)
		s_yaw += (float)(2.0 * M_PI);
	t_quat q_yaw = quat_from_axis_angle(WORLD_UP, s_yaw);
	t_vec3 dir_yaw = vec_normalize(quat_rotate_vec(FWD0, q_yaw));
	t_vec3 up_yaw = vec_normalize(quat_rotate_vec(UP0, q_yaw));
	t_vec3 right_yaw = vec_normalize(vec_cross(up_yaw, dir_yaw));
	t_quat q_pitch = quat_from_axis_angle(right_yaw, s_pitch);
	cam->orient = quat_normalize(quat_mul(q_pitch, q_yaw));
	camera_compute_basis(cam);
	d->preview_mode = true;
	d->max_rays = 1;
	d->max_bounces = 0;
	d->last_move_time = mlx_get_time();
	reset_pixel_buffer(d);
	start_progressive_render(d);
}

/**
 * @brief Mouse cursor callback: filters jumps, computes deltas and rotates camera.
 * @param mx Current mouse X (pixels).
 * @param my Current mouse Y (pixels).
 * @param param Opaque pointer to t_data.
 * @return None.
 * @details Ignores the very first event, respects temporary suppression/window
 * block, clamps deltas by both percentage-of-screen and absolute pixel caps,
 * then forwards to apply_mouse_rotation().
 */
void	mouse_move(double mx, double my, void *param)
{
	t_data		*d;
	t_camera	*cam;
	double		dx;
	double		dy;

	d = param;
	cam = d->scene.active_cam;
	if (d->first_mouse)
	{
		d->first_mouse = false;
		d->last_mouse_x = mx;
		d->last_mouse_y = my;
		return ;
	}
	if (mlx_get_time() < d->mouse_block_until)
	{
		d->last_mouse_x = mx;
		d->last_mouse_y = my;
		return ;
	}
	if (d->suppress_next_mouse)
	{
		d->suppress_next_mouse = false;
		d->last_mouse_x = mx;
		d->last_mouse_y = my;
		return ;
	}
	dx = mx - d->last_mouse_x;
	dy = my - d->last_mouse_y;
	{
		double max_jump_x = d->scene.width * 0.10;
		double max_jump_y = d->scene.height * 0.10;
		if (fabs(dx) > max_jump_x || fabs(dy) > max_jump_y)
		{
			d->last_mouse_x = mx;
			d->last_mouse_y = my;
			return ;
		}
	}
	{
		const double max_px = 24.0;
		if (dx >  max_px) dx =  max_px;
		if (dx < -max_px) dx = -max_px;
		if (dy >  max_px) dy =  max_px;
		if (dy < -max_px) dy = -max_px;
	}
	d->last_mouse_x = mx;
	d->last_mouse_y = my;
	apply_mouse_rotation(d, cam, dx, dy);
}
