/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <generated>                         +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:30:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/15 18:30:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	render_single(t_mlx *app, t_camera *cam)
{
	int	y;
	int	x;

	y = 0;
	while (y < MLX_Y)
	{
		x = 0;
		while (x < MLX_X)
		{
			render_pixel_to_app(app, cam, x, y);
			x++;
		}
		y++;
	}
}

void	cleanup_and_fallback(pthread_t threads[], int count, t_mlx *app,
		t_camera *cam)
{
	int	k;

	k = 0;
	while (k < count)
	{
		pthread_join(threads[k], NULL);
		k++;
	}
	render_single(app, cam);
	mlx_put_image_to_window(app->mlx, app->window, app->img, 0, 0);
}

t_camera	*get_active_camera(t_mlx *app)
{
	t_list	*cn;

	if (!app || !app->scene)
		return (NULL);
	if (app->scene->active_camera)
		cn = app->scene->active_camera;
	else
		cn = app->scene->camera;
	if (!cn)
		return (NULL);
	return ((t_camera *)cn->content);
}
