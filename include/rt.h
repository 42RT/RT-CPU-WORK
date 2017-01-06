/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 13:26:09 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 17:23:41 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define EPS 0.01
# define WIDTH 640
# define HEIGHT 480
# define VPWIDTH 10
# define VPHEIGHT 7.2
# define VPDIST 20
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
# include <SDL.h>
# include <libft.h>
# include <lib_vec.h>

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
	double			a;
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
	t_vec		vec1;
	t_vec		vec2;
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
	t_vec		pos;
	t_vec		n;
	t_color			color;
	double			r;
}					t_parse;

typedef struct		s_ray
{
	t_vec		vecdir;
	t_vec		pos;
	t_vec		reflect;
	double			dist;
	t_color			color;
}					t_ray;

typedef struct		s_camera
{
	t_vec		campos;
	t_vec		vecdirx;
	t_vec		vecdiry;
	t_vec		vecdirz;
	t_vec		vpul;
	double			xindent;
	double			yindent;
}					t_camera;

typedef struct		s_spot
{
	t_vec		spotpos;
	t_color			color;
	t_ray			ray;
	struct s_spot	*first;
	struct s_spot	*next;
}					t_spot;

typedef struct		s_env
{
	SDL_Renderer	*img;
	SDL_Window		*win;
	SDL_Event		event;
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
int					lightcaster(t_env *env, t_vec pos, t_ray ray, t_obj *obj);
void				reflect(t_env *env, int i);
void				pixel_put(t_env *env, t_color color);
t_ray				init_ray(t_env *env);
t_color				calc_color(t_ray *ray, t_color cobj, t_color clight,
		double angle);
t_color				calc_shadow(t_ray *ray, t_color cobj);
t_color				extract_color(int color);
int					event(SDL_Event event, t_env *env);
void				error(int n);
t_line				*ft_new_line(char *line, int size);
t_line				*save_file(int fd);
double				ft_atof(char *str);
t_color				default_color(void);
t_color				default_color_spot(void);
t_vec				default_pos(void);
t_vec				default_n(void);
void				free_file(t_env *env);
int					gotonextvalue(t_env *env, int i);
t_color				init_color_black(void);

t_vec				calc_ncone(t_ray *ray, t_obj *obj);
t_vec				calc_ncylinder(t_ray *ray, t_obj *obj);

/*
** PARSER FUNCTIONS
*/

t_vec				get_vector(t_env *env);
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
** CAMERA FUNCTIONS
*/

t_camera			init_cam(double x, double y, double z);
void				transcam(t_env *env, t_vec trans);
void				rotcam(t_env *env, double rx, double ry, double rz);
void				camangle(t_env *env, double rx, double ry, double rz);

/*
** OBJECTS FUNCTIONS
*/

void				create_sphere(t_env *env, t_vec pos, t_color color,
		double r);
t_obj				*test_sphere(t_env *env, t_ray *ray);
int					test_sphere2(t_env *env, t_vec pos, t_ray ray);
int					test_sphere3(t_env *env, t_vec pos);
void				create_spot(t_env *env, t_vec pos, t_color color);
t_color				test_spot(t_env *env, t_ray *ray, t_obj *obj,
		t_vec point);
void				create_plan(t_env *env, t_vec pos, t_color color,
		t_vec n);
t_obj				*test_plan(t_env *env, t_ray *ray);
int					test_plan2(t_env *env, t_vec pos, t_ray ray);
int					test_plan3(t_env *env, t_vec pos);
void				create_cylinder(t_env *env, t_parse data);
t_obj				*test_cylinder(t_env *env, t_ray *ray);
int					test_cylinder2(t_env *env, t_vec pos, t_ray ray);
int					test_cylinder3(t_env *env, t_vec pos);
void				create_cone(t_env *env, t_parse data);
t_obj				*test_cone(t_env *env, t_ray *ray);
int					test_cone2(t_env *env, t_vec pos, t_ray ray);
int					test_cone3(t_env *env, t_vec pos);
void				trans_rotation(t_env *env);
t_obj				*test_obj(t_env *env, t_ray *ray);

#endif
