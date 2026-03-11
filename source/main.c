/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:33:32 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/21 09:15:41 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rendering.h"

static int	mouse_hook(int button, int x, int y, t_mlx *app)
{
	t_object	*clicked_obj;

	if (button == 1)
	{
		clicked_obj = get_object_at_pixel(app, x, y);
		if (clicked_obj)
			cycle_render_mode(app, clicked_obj);
	}
	return (0);
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
	if (num == INVALID_ARGUMENT)
		ft_putstr_fd("Error: Invalid argument\n", 2);
	else if (num == INVALID_PATH)
		ft_putstr_fd("Error: Invalid path\n", 2);
	else if (num == FAILED_TO_OPEN_FILE)
		ft_putstr_fd("Error: Failed to open file\n", 2);
	else if (num == INVALID_MAP)
		ft_putstr_fd("Error: Invalid map\n", 2);
	else if (num == FAILED_TO_MALLOC)
		ft_putstr_fd("Error: Failed to malloc\n", 2);
	exit(num);
}

static t_scene	*prepare_scene(char *path)
{
	int		fd;
	char	**map_array;
	t_scene	*scene;

	fd = check_and_open_map_file(path);
	map_array = read_in_map_file(fd);
	validate_map(map_array);
	scene = initialize_scene(map_array);
	ft_free_matrix(map_array);
	normalize_vectors(scene);
	return (scene);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	t_mlx	*app;

	if (argc != 2)
		error_handling(INVALID_ARGUMENT);
	scene = prepare_scene(argv[1]);
	if (!scene)
		return (1);
	app = mlx_init_scene(scene, MLX_X, MLX_Y, "miniRT");
	if (!app)
		return (free_scene(scene), 1);
	load_scene_textures(scene, app->mlx);
	drawing(app);
	mlx_key_hook(app->window, key_hook, app);
	mlx_mouse_hook(app->window, mouse_hook, app);
	mlx_hook(app->window, 17, 0, close_window, app);
	mlx_loop(app->mlx);
	destroy_app(app);
	free_scene(app->scene);
	return (0);
}
