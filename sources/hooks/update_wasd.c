/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_wasd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:40:59 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 12:52:22 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"

/**
 * @brief Update camera position from WASD keys along local basis vectors.
 * @param d Global runtime data (reads keys).
 * @param cam Camera to move.
 * @param speed Movement step length for this frame.
 * @return None.
 * @details Moves along cam->dir (W/S) and cam->right (A/D).
 */
static void	update_camera_position(t_data *d, t_camera *cam, float speed)
{
	if (d->keys.w)
		cam->pos = vec_add(cam->pos, vec_scale(cam->dir, speed));
	if (d->keys.s)
		cam->pos = vec_subtract(cam->pos, vec_scale(cam->dir, speed));
	if (d->keys.a)
		cam->pos = vec_subtract(cam->pos, vec_scale(cam->right, speed));
	if (d->keys.d)
		cam->pos = vec_add(cam->pos, vec_scale(cam->right, speed));
}

/**
 * @brief Apply movement, mark activity and restart progressive rendering.
 * @param d Global runtime data.
 * @param cam Camera to move.
 * @param speed Movement step length.
 * @return None.
 */
static void	process_movement(t_data *d, t_camera *cam, float speed)
{
	update_camera_position(d, cam, speed);
	d->last_move_time = mlx_get_time();
	camera_compute_basis(cam);
	reset_pixel_buffer(d);
	start_progressive_render(d);
}

/**
 * @brief Prepare movement for this frame (compute dt speed and run).
 * @param d Global runtime data.
 * @param delta Delta time (seconds) for this frame.
 * @return None.
 * @details Speed is scaled linearly with delta time:
 *   speed = CAMERA_SPEED * delta.
 */
static void	prepare_movement(t_data *d, double delta)
{
	t_camera	*cam;
	float		speed;
	float		dt;

	cam = d->scene.active_cam;
	dt = (float)delta;
	camera_compute_basis(cam);
	speed = CAMERA_SPEED * dt;
	process_movement(d, cam, speed);
}

/**
 * @brief Per-frame update callback (time step & movement handling).
 * @param param Opaque pointer to t_data.
 * @return None.
 * @details Computes clamped delta time in [0, 0.05] to avoid huge steps, and
 * if any movement keys are pressed, advances the camera.
 */
void	update_cb(void *param)
{
	t_data	*d;
	double	now;
	double	delta;

	d = param;
	now = mlx_get_time();
	delta = now - d->last_frame_time;
	if (delta < 0.0)
		delta = 0.0;
	if (delta > 0.05)
		delta = 0.05;
	d->last_frame_time = now;
	if ((d->keys.w || d->keys.a || d->keys.s || d->keys.d) && delta > 0.0)
		prepare_movement(d, (float)delta);
}
