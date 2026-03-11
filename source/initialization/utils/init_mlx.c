/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:24:28 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 21:09:42 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

t_mlx	*alloc_app(t_scene *scene)
{
	t_mlx	*app;

	app = malloc(sizeof(t_mlx));
	if (!app)
		return (NULL);
	ft_bzero(app, sizeof(t_mlx));
	app->scene = scene;
	return (app);
}

int	init_mlx(t_mlx *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (0);
	return (1);
}

int	init_window_img(t_mlx *app, int w, int h, char *title)
{
	app->window = mlx_new_window(app->mlx, w, h, title);
	if (!app->window)
		return (0);
	app->img = mlx_new_image(app->mlx, w, h);
	if (!app->img)
		return (0);
	app->img_addr = mlx_get_data_addr(app->img, &app->img_bpp,
			&app->img_size_line, &app->img_endian);
	if (!app->img_addr)
		return (0);
	return (1);
}

t_mlx	*mlx_init_scene(t_scene *scene, int width, int height, char *title)
{
	t_mlx	*app;

	app = alloc_app(scene);
	if (!app)
		return (NULL);
	if (!init_mlx(app) || !init_window_img(app, width, height, title))
	{
		destroy_app(app);
		return (NULL);
	}
	return (app);
}
