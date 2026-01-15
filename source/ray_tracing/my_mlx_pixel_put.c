#include "rendering.h"

void	my_mlx_pixel_put(t_mlx *app, int x, int y, int color)
{
	char	*dst;

	if (!app || !app->img_addr)
		return ;
	if (x < 0 || x >= MLX_X || y < 0 || y >= MLX_Y)
		return ;
	dst = app->img_addr + (y * app->img_size_line + x * (app->img_bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

unsigned int	my_mlx_pixel_get(t_mlx *app, int x, int y)
{
	char *dst;

	if (!app || !app->img_addr)
		return (0);
	if (x < 0 || x >= MLX_X || y < 0 || y >= MLX_Y)
		return (0);
	dst = app->img_addr + (y * app->img_size_line + x * (app->img_bpp / 8));
	return (*(unsigned int *)dst);
}
