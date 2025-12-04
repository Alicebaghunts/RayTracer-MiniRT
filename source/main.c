/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:33:32 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/04 17:42:27 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

#ifdef __APPLE__
# define KEY_ESC 53
# define KEY_SPACE 49
#else
# define KEY_ESC 65307
# define KEY_SPACE 32
#endif

static void	destroy_app(t_mlx *app)
{
	if (!app)
		return ;
	if (app->window && app->mlx)
		mlx_destroy_window(app->mlx, app->window);
	if (app->scene)
		free_scene(app->scene);
	if (app->mlx)
		free(app->mlx);
	free(app);
}

static int	close_window(t_mlx *app)
{
	destroy_app(app);
	exit(0);
	return (0);
}

static void	switch_camera(t_mlx *app)
{
	t_list	*cur;

	if (!app || !app->scene || !app->scene->camera)
		return ;
	cur = app->scene->active_camera;
	if (!cur)
		cur = app->scene->camera;
	else if (cur->next)
		cur = cur->next;
	else
		cur = app->scene->camera;
	app->scene->active_camera = cur;
	mlx_clear_window(app->mlx, app->window);
	drawing(app);
}

static int	key_hook(int keycode, t_mlx *app)
{
	if (keycode == KEY_ESC)
		close_window(app);
	else if (keycode == KEY_SPACE)
		switch_camera(app);
	return (0);
}

void	error_handling(int num)
{
	if (num == 1)
		ft_putstr_fd("Error: Invalid argument\n", 2);
	else if (num == 2)
		ft_putstr_fd("Error: Invalid path\n", 2);
	else if (num == 3)
		ft_putstr_fd("Error: Failed to open file\n", 2);
	else if (num == 4)
		ft_putstr_fd("Error: Invalid map\n", 2);
	else if (num == 5)
		ft_putstr_fd("Error: Failed to malloc\n", 2);
	exit(num);
}

t_mlx	*mlx_init_scene(t_scene *scene, int width, int height, char *title)
{
	t_mlx	*mlx_struct;

	mlx_struct = malloc(sizeof(t_mlx));
	if (!mlx_struct)
		return (NULL);
	mlx_struct->mlx = mlx_init();
	if (!mlx_struct->mlx)
	{
		free(mlx_struct);
		return (NULL);
	}
	mlx_struct->window = mlx_new_window(mlx_struct->mlx, width, height, title);
	if (!mlx_struct->window)
	{
		free(mlx_struct->mlx);
		free(mlx_struct);
		return (NULL);
	}
	mlx_struct->scene = scene;
	return (mlx_struct);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	char	**map_array;
	int		fd;
	t_mlx	*app;

	if (argc != 2)
		error_handling(INVALID_ARGUMENT);
	fd = check_and_open_map_file(argv[1]);
	map_array = read_in_map_file(fd);
	validate_map(map_array);
	scene = initialize_scene(map_array);
	ft_free_matrix(map_array);
	normalize_vectors(scene);
	app = mlx_init_scene(scene, MLX_X, MLX_Y, "miniRT");
	if (!app)
		return (free_scene(scene), 1);
	load_scene_textures(scene, app->mlx);
	drawing(app);
	mlx_key_hook(app->window, key_hook, app);
	mlx_hook(app->window, 17, 0, close_window, app);
	mlx_loop(app->mlx);
	return (0);
}
