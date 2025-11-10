/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:27:23 by iriadyns          #+#    #+#             */
/*   Updated: 2025/11/10 12:48:15 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>
# include <string.h>
# include "MLX42.h"
# include "scene.h"
# include "input.h"
# include "libft.h"
# include "parser.h"
# include "debug.h"

typedef struct s_camera			t_camera;
typedef struct s_pixel			t_pixel;
typedef struct s_thread_ctx		t_thread_ctx;

# define TAU			6.2831854f
# define PITCH_MAX_RAD	1.5533430f
# define YAW_SENS		0.002f
# define PITCH_SENS		0.002f
# define MOUSE_MAX_PERC	0.10f
# define MOUSE_MAX_PX	24.0
# define MAX_RAYS 20
# define MAX_BOUNCES 10

typedef struct s_data
{
	t_scene				scene;
	mlx_t				*mlx;
	mlx_image_t			*image_buffer;
	t_pixel				**pixels;
	int					max_rays;
	int					max_bounces;
	bool				preview_mode;
	double				last_move_time;
	double				last_frame_time;
	t_keys				keys;
	bool				first_mouse;
	double				last_mouse_x;
	double				last_mouse_y;
	double				mouse_block_until;
	bool				suppress_next_mouse;
	volatile bool		keep_rendering;
	int					nthreads;
	int					nthreads_success;
	pthread_t			*threads;
	t_thread_ctx		*thread_ctx;
	pthread_mutex_t		render_lock;
	pthread_cond_t		render_cond;
	bool				pool_started;
	bool				should_stop;
	bool				rendering_on;
	bool				exiting;
	uint32_t			frame_id;
}	t_data;

// Shutdown and error handling
void	exit_success(t_data *data);
void	exit_error(t_data *data, char *msg);
void	exit_error_errno(t_data *data, char *msg, int errcode);

// Resource management
void	free_data(t_data *data);
void	free_scene(t_scene *scene);
void	free_pixels(t_pixel ***pixels, uint32_t y);

// Window / graphics initialisation
void	initialise_mlx_window(t_data *data);

// Main loop hook
void	loop_hook(void *param);

// Mouse input & rotation helpers
bool	mouse_jump_too_large(t_data *d, double dx, double dy);
void	mouse_clamp_deltas(double *dx, double *dy);
void	mouse_update_angles(t_camera *cam, double dx, double dy);
void	apply_mouse_rotation(t_data *d, t_camera *cam, double dx, double dy);

#endif
