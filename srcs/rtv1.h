/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 13:26:09 by rfriscca          #+#    #+#             */
/*   Updated: 2016/12/16 15:52:34 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define EPS 0.01
# define WIDTH 640
# define HEIGHT 480
# define VPWIDTH 10
# define VPHEIGHT 7.2
# define VPDIST 20
# define PI 3.14159265
# define SPEC 50
# define KD 0.6
# define KS 0.2
# define KA 0.2
# define RA 255
# define GA 255
# define BA 255
# define MAX_DEPTH 25

/*
** FOV = atan(VPWIDTH / 2 / VPDIST)
** With VPWIDTH = 6.4 and VPDIST = 12 FOV = 30
*/

# define CAMPOSX env->cam.campos.x
# define CAMPOSY env->cam.campos.y
# define CAMPOSZ env->cam.campos.z
# define CAMPOS env->cam.campos
# define XINDENT env->cam.xindent
# define YINDENT env->cam.yindent
# define VPUL env->cam.vpul
# define OBJCOLOR env->obj->color
# define XS env->obj->vec1.x
# define YS env->obj->vec1.y
# define ZS env->obj->vec1.z
# define POS env->obj->vec1
# define NX env->obj->vec2.x
# define NY env->obj->vec2.y
# define NZ env->obj->vec2.z
# define N env->obj->vec2
# define RS env->obj->r
# define D1 env->obj->d1
# define D2 env->obj->d2

/*
** ray define
*/

# define RCOLOR ray->color
# define VDIR ray->vecdir
# define RDIST ray->dist
# define REFLECT ray->reflect

/*
**  define vec dir camera
*/

# define VDZX cam.vecdirz.x
# define VDZY cam.vecdirz.y
# define VDZZ cam.vecdirz.z
# define VDYX cam.vecdiry.x
# define VDYY cam.vecdiry.y
# define VDYZ cam.vecdiry.z
# define VDXX cam.vecdirx.x
# define VDXY cam.vecdirx.y
# define VDXZ cam.vecdirx.z

# define LINE env->file->line
# define LINENEXT env->file->next->line

# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct		s_line
{
	char			*line;
	int				size;
	struct s_line	*next;
}					t_line;

typedef struct		s_obj
{
	char			type;
	t_vector		vec1;
	t_vector		vec2;
	int				reflect;
	double			r;
	double			d1;
	double			d2;
	t_color			color;
	struct s_obj	*next;
	struct s_obj	*first;
}					t_obj;

typedef struct		s_parse
{
	t_vector		pos;
	t_vector		n;
	t_color			color;
	double			r;
}					t_parse;

typedef struct		s_ray
{
	t_vector		vecdir;
	t_vector		pos;
	t_vector		reflect;
	double			dist;
	t_color			color;
}					t_ray;

typedef struct		s_camera
{
	t_vector		campos;
	t_vector		vecdirx;
	t_vector		vecdiry;
	t_vector		vecdirz;
	t_vector		vpul;
	double			xindent;
	double			yindent;
}					t_camera;

typedef struct		s_spot
{
	t_vector		spotpos;
	t_color			color;
	t_ray			ray;
	struct s_spot	*first;
	struct s_spot	*next;
}					t_spot;

typedef struct		s_env
{
	void			*mlx;
	void			*img;
	void			*win;
	char			*img_data;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				i;
	double			x;
	double			y;
	t_parse			data;
	t_line			*file;
	t_obj			*obj;
	t_camera		cam;
	t_spot			*spot;
}					t_env;

void				raycaster(t_env *env);
t_color				trace(t_env *env, t_ray *ray, int i);
int					lightcaster(t_env *env, t_vector pos, t_ray ray, t_obj *obj);
void				reflect(t_env *env, int i);
void				mlx_pixel_put_img(t_env *env, t_color color);
t_ray				init_ray(t_env *env);
t_color				calc_color(t_ray *ray, t_color cobj, t_color clight,
		double angle);
t_color				calc_shadow(t_ray *ray, t_color cobj);
t_color				extract_color(int color);
int					event(int n, t_env *env);
void				error(int n);
t_line				*ft_new_line(char *line, int size);
t_line				*save_file(int fd);
double				ft_atof(char *str);
t_color				default_color(void);
t_color				default_color_spot(void);
t_vector			default_pos(void);
t_vector			default_n(void);
void				free_file(t_env *env);
int					gotonextvalue(t_env *env, int i);
t_color				init_color_black(void);

/*
** PARSER FUNCTIONS
*/

t_vector			get_vector(t_env *env);
t_color				get_color(t_env *env);
t_color				get_color_spot(t_env *env);
t_color				color_correc_spot(t_color color);
t_color				color_correc_obj(t_color color);
void				parse_camera(t_env *env);
void				parse_sphere(t_env *env);
void				parse_spot(t_env *env);
void				parse_plane(t_env *env);
void				parse_cylinder(t_env *env);
void				parse_cone(t_env *env);
void				parse_file(t_env *env);

/*
** VECTOR FUNCTIONS
*/

t_vector			rotx(t_vector vec, double angle);
t_vector			roty(t_vector vec, double angle);
t_vector			rotz(t_vector vec, double angle);
t_vector			rotvec(t_vector vec, t_vector trans);
t_vector			translation(t_vector vec, t_vector translation);
t_vector			normalize_vec(t_vector vec);
t_vector			calc_vect(t_vector p1, t_vector p2);
t_vector			ray_point(t_env *env);
t_vector			ray_point_reflect(t_env *env);
t_vector			calc_ncylinder(t_ray *ray, t_obj *obj);
t_vector			calc_ncone(t_ray *ray, t_obj *obj);
t_vector			inv_vect(t_vector vec);
t_vector			reflect_vect(t_vector dir, t_vector n);
t_vector			sub_vect(t_vector v, t_vector w);
t_vector			mult_vect(t_vector v, double mult);
double				dotproduct(t_vector vec1, t_vector vec2);

/*
** CAMERA FUNCTIONS
*/

t_camera			init_cam(double x, double y, double z);
void				transcam(t_env *env, t_vector trans);
void				rotcam(t_env *env, double rx, double ry, double rz);
void				camangle(t_env *env, double rx, double ry, double rz);

/*
** OBJECTS FUNCTIONS
*/

void				create_sphere(t_env *env, t_vector pos, t_color color,
		double r);
t_obj				*test_sphere(t_env *env, t_ray *ray);
int					test_sphere2(t_env *env, t_vector pos, t_ray ray);
int					test_sphere3(t_env *env, t_vector pos);
void				create_spot(t_env *env, t_vector pos, t_color color);
t_color				test_spot(t_env *env, t_ray *ray, t_obj *obj,
		t_vector point);
void				create_plan(t_env *env, t_vector pos, t_color color,
		t_vector n);
t_obj				*test_plan(t_env *env, t_ray *ray);
int					test_plan2(t_env *env, t_vector pos, t_ray ray);
int					test_plan3(t_env *env, t_vector pos);
void				create_cylinder(t_env *env, t_parse data);
t_obj				*test_cylinder(t_env *env, t_ray *ray);
int					test_cylinder2(t_env *env, t_vector pos, t_ray ray);
int					test_cylinder3(t_env *env, t_vector pos);
void				create_cone(t_env *env, t_parse data);
t_obj				*test_cone(t_env *env, t_ray *ray);
int					test_cone2(t_env *env, t_vector pos, t_ray ray);
int					test_cone3(t_env *env, t_vector pos);
void				trans_rotation(t_env *env);
t_obj				*test_obj(t_env *env, t_ray *ray);

#endif
