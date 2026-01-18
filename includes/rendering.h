/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:12:05 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/18 20:08:56 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H
# include "initialization.h"
# include "intersect.h"

# define RAY_EPS 1e-6
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_SPACE 49
# else
#  define KEY_ESC 65307
#  define KEY_SPACE 32
# endif

// ray info
typedef struct s_rayinfo
{
	double		aspect;
	double		scale;
	double		sx;
	double		sy;
}				t_rayinfo;

// roots
typedef struct s_roots
{
	double		t1;
	double		t2;
	int			valid;
}				t_roots;

// the all shadow info
typedef struct s_shade_info
{
	t_scene		*scene;
	t_vector	hit_point;
	t_vector	normal;
	t_vector	view_dir;
	t_object	*obj;
	t_color		obj_color;
	t_color		*result;
}				t_shade_info;

// shadow info
typedef struct s_shadow_info
{
	t_scene		*scene;
	t_vector	hit_point;
	t_vector	normal;
	t_vector	light_dir;
	double		light_dist;
	t_object	*ignore;
}				t_shadow_info;

// lighte info
typedef struct s_light_info
{
	t_color		*result;
	t_color		obj_color;
	t_light		*light;
	t_vector	normal;
	t_vector	view_dir;
	t_vector	hit_point;
}				t_light_info;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	t_scene		*scene;
	void		*img;
	char		*img_addr;
	int			img_bpp;
	int			img_size_line;
	int			img_endian;
}				t_mlx;

typedef struct s_hit
{
	double		min_t;
	t_object	*closest;
	t_vector	hit_point;
	t_vector	normal;
	t_color		shaded;
}				t_hit;

void			drawing(t_mlx *app);
double			vector_length(t_vector vector);
double			vector_dot(t_vector a, t_vector b);
t_vector		vector_sub(t_vector a, t_vector b);
t_vector		vector_cross(t_vector a, t_vector b);
t_vector		vector_scale(t_vector v, double s);
t_vector		vector_addition(t_vector a, t_vector b);
t_object		*find_closest_object(t_scene *scene, t_camera *cam,
					t_vector ray_dir, double *min_t);
double			intersect_sphere(t_camera *camera, t_vector ray_dir,
					t_sphere *sphere);
t_vector		compute_ray(t_camera *cam, double u, double v);
double			intersect_plane(t_camera *camera, t_vector ray_dir,
					t_plane *plane);
t_color			shade(t_scene *scene, t_vector hit_point, t_vector normal,
					t_object *obj);

double			intersect_sphere_shadow(t_vector ray_origin, t_vector ray_dir,
					t_sphere *sphere);

double			intersect_plane_shadow(t_vector ray_origin, t_vector ray_dir,
					t_plane *plane);
int				in_shadow(t_shadow_info info);
t_color			get_object_color(t_object *obj);
t_color			compute_ambient(t_scene *scene, t_color obj_color);
void			add_light_contribution_struct(t_light_info *info);

//
float			get_sphere_bump(t_sphere *sp, float u, float v);
t_vector		sphere_tangent(t_vector normal);
t_vector		sphere_bitangent(t_vector normal, t_vector tangent);
t_vector		apply_sphere_bump(t_vector normal, float bump_value,
					t_vector tangent);

void			my_mlx_pixel_put(t_mlx *app, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_mlx *app, int x, int y);

void			destroy_app(t_mlx *app);
int				close_window(t_mlx *app);
void			switch_camera(t_mlx *app);
t_object		*get_object_at_pixel(t_mlx *app, int x, int y);
void			cycle_render_mode(t_mlx *app, t_object *obj);
t_vector		get_normal(t_object *obj, t_vector hit_point);

#endif
