/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:34:48 by alisharu          #+#    #+#             */
/*   Updated: 2026/03/13 15:22:27 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_TYPES_H
# define OBJECT_TYPES_H
# include "../libs/libft/libft.h"
# include <math.h>
# include <stdbool.h>

/* ------------------------ Constants ------------------------ */
# define INVALID_ARGUMENT 1
# define INVALID_PATH 2
# define INVALID_FILE 3
# define INVALID_MAP 4
# define MALLOC_ERROR 5

# define MLX_X 1000
# define MLX_Y 800

/* ------------------------ Hit types ------------------------ */
typedef enum e_hit_type
{
	HIT_NONE,
	HIT_CYLINDER_SIDE,
	HIT_CYLINDER_TOP,
	HIT_CYLINDER_BOTTOM
}					t_hit_type;

/* ------------------------ Texture ------------------------ */
typedef struct s_texture
{
	char			*path;
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
}					t_texture;

/* ------------------------ Validation flags ------------------------ */
typedef struct s_valid_object
{
	bool			camera;
	bool			light;
	bool			ambient;
}					t_valid_object;

/* ------------------------ Color & Vector ------------------------ */
typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;

typedef struct s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

/* ------------------------ Lighting primitives ------------------------ */
typedef struct s_ambient
{
	double			light_ratio;
	t_color			*color;
}					t_ambient;

/* ------------------------ Camera ------------------------ */
typedef struct s_camera
{
	t_vector		*position;
	t_vector		*direction;
	int				field_of_view;
}					t_camera;

/* ------------------------ Light ------------------------ */
typedef struct s_light
{
	t_vector		*position;
	double			brightness_ratio;
	t_color			*color;
}					t_light;

/* ------------------------ Geometric primitives ------------------------ */
typedef struct s_sphere
{
	t_vector		*position;
	double			diameter;
	t_color			*color;
	t_texture		*texture;
	t_texture		*bump;
}					t_sphere;

typedef struct s_plane
{
	t_vector		*position;
	t_vector		*normal;
	t_color			*color;
	t_texture		*texture;
	t_texture		*bump;
}					t_plane;

typedef struct s_cylinder
{
	t_vector		*position;
	t_vector		*direction;
	t_color			*color;
	double			diameter;
	double			height;
	t_texture		*texture;
	t_texture		*bump;
}					t_cylinder;

typedef enum e_render_mode
{
	MODE_TEXTURE,
	MODE_BUMP,
	MODE_CHECKERBOARD
}					t_render_mode;

typedef struct s_cone
{
	t_vector		*apex;
	t_vector		*axis;
	double			angle;
	double			height;
	t_color			*color;
	t_texture		*texture;
	t_texture		*bump;
}					t_cone;

/* ------------------------ Object data ------------------------ */
typedef union u_object_data
{
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_cone			*cone;
}					t_object_data;

/* ------------------------ Object ------------------------ */
typedef struct s_object
{
	char			type;
	t_object_data	*data;
}					t_object;

/* ------------------------ Scene ------------------------ */
typedef struct s_scene
{
	t_ambient		*ambient;
	t_list			*camera;
	t_list			*active_camera;
	t_list			*lights;
	t_list			*objects;
	t_object		*selected_object;
	t_render_mode	selected_mode;
}					t_scene;

#endif
