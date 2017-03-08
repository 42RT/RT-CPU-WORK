/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 22:50:11 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/23 14:52:12 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include <libft.h>
# include <libxmlx.h>
# include <rtdefs.h>
# include <pthread.h>

# ifdef __APPLE__
#  define DEF_MULTITHREAD	1
#  include <osx_keyset.h>
#  include <SDL_ttf.h>
# else
#  define DEF_MULTITHREAD	1
#  include <x11_keyset.h>
#  include <SDL2/SDL_ttf.h>
# endif

# define TURN_VAL			0.16
# define MOVE_VAL			100

# define MAX_PARAM			100
# define EPS				0.1
# define NOISE_HEIGHT		128
# define NOISE_WIDTH		128
# define SPEC				30
# define RAMBIENT			255
# define GAMBIENT			255
# define BAMBIENT			255
# define COEFSPEC			0.0
# define COEFDIFFUSE		0.8
# define COEFAMBIENT		0.2

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
}					t_vector;

typedef struct		s_color
{
	float			r;
	float			g;
	float			b;
}					t_color;

typedef struct		s_cam
{
	t_vector		pos;
	t_vector		ang;
}					t_cam;

typedef struct		s_settings
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	aa;
	unsigned int	deph;
	unsigned int	reflect;
	unsigned int	refract;
	unsigned int	fov;
	unsigned int	d3_mode;
	float			d3_offset;
	float			d3_conv;
	char			*name;
	unsigned int	focus;
	int				focus_dst;
	int				focus_range;
	float			focus_k;
	t_cam			*cam;
	t_cam			*cam2;
	int				preview;
	int				display;
	int				threads;
	int				verbose;
}					t_settings;

typedef struct		s_obj
{
	int				type;
	void			(*func)();
	void			(*normale)();
	int				**base;
	int				negative;
	int				cap1;
	int				cap2;
	float			coef_ambient;
	float			coef_diffuse;
	float			coef_spec;
	t_vector		pos;
	t_vector		ang;
	t_vector		exp;
	t_vector		def;
	t_vector		n;
	unsigned int	color;
	unsigned int	color2;
	unsigned int	color3;
	unsigned int	color_refract;
	unsigned int	size;
	float			mod;
	float			reflect_k;
	float			refract_k;
	float			refract_ind;
	float			dst;
	float			x1;
	float			x2;
	struct s_obj	*compose;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_light
{
	int				type;
	t_vector		pos;
	t_vector		ang;
	unsigned int	color;
	float			mod;
	float			k1;
	float			k2;
	float			k3;
	struct s_light	*next;
}					t_light;

typedef struct		s_env
{
	t_gfx			*gfx;
	t_img			*load_bar;
	t_settings		*set;
	t_obj			*obj;
	t_obj			*neg_obj;
	t_light			*light;
	float			last_refract;
	float			x;
	float			y;
	float			noise[NOISE_HEIGHT][NOISE_WIDTH];
	int				inside_obj;
	int				ac;
	char			**av;
	float			last_dst;
}					t_env;

typedef struct		s_equation
{
	double			delta;
	double			a;
	double			b;
	double			c;
	float			x1;
	float			x2;
	t_obj			*obj;
	t_vector		v;
	t_vector		o;
}					t_equation;

typedef struct		s_th_arg
{
	t_env			*e;
	t_obj			*obj;
	int				*map;
	int				*nb;
}					t_th_arg;

typedef struct		s_th_data
{
	t_env			*e;
	int				*map;
	int				res;
	int				nb;
	pthread_mutex_t	mutex;
}					t_th_data;

typedef struct		s_ray_data
{
	t_vector		*o;
	t_vector		*v;
	t_vector		n;
	t_obj			*start;
	t_obj			*shorter;
}					t_ray_data;

typedef struct		s_trace_lights_data
{
	float			len;
	t_obj			*obj;
}					t_trace_lights_data;

/*
** Rendering parts
*/
unsigned int		compute_color(t_env *e, t_obj *obj, unsigned int deph);
unsigned int		trace_lights(t_env *e, t_ray_data d, t_light *light);

unsigned int		new_ray(t_env *e, t_vector *o, t_vector *v, t_obj *obj,
							unsigned int deph);
void				trace_ray(t_env *e, t_obj *obj, t_vector *o, t_vector *v);
int					ray_effect(t_env *e, t_vector *vec[2], t_obj *obj,
								unsigned int deph);
void				fill_pixel(t_env *e, t_obj *obj);
void				launch_threads(t_th_data *data);
void				change_cam(t_env *e);
void				reload(t_env *e);
int					get_pos(int *map, int res, int *nb);

/*
** Various utils
*/
void				ft_err(char *str);
t_obj				*copy_obj_elem(t_obj *obj);
t_obj				*copy_obj(t_obj *obj);
t_env				*copy_env(t_env *e);
void				matrice_to_vector(t_vector *v, int **base);
float				solve_equation(t_equation *eq);
unsigned int		get_color(char *str);
void				print_debug(t_env *e);
void				exp_compute(t_vector *o, t_vector *exp);
unsigned int		mod_light(unsigned int color, float dst, float coef2);
unsigned int		limit_nb(unsigned int color, unsigned int max);

/*
** Init
*/
int					init(t_env *e, char *scene);
int					*init_map(int nb);
t_env				*init_vars(t_env *e);
int					**new_base();

/*
** Antialiasing
*/
unsigned int		aa_2(t_env *e, t_obj *obj, unsigned int deph);
unsigned int		aa_4(t_env *e, t_obj *obj, unsigned int deph);
unsigned int		aa_8(t_env *e, t_obj *obj, unsigned int deph);
unsigned int		aa_16(t_env *e, t_obj *obj, unsigned int deph);

/*
** Trace objects
*/
void				trace_floor(t_obj *obj, t_vector o, t_vector v);
void				trace_dfloor(t_obj *obj, t_vector o, t_vector v);
void				trace_sphere(t_obj *obj, t_vector o, t_vector v);
void				trace_cylinder(t_obj *obj, t_vector o, t_vector v);
void				trace_cone(t_obj *obj, t_vector o, t_vector v);
void				trace_disk(t_obj *obj, t_vector o, t_vector v);
void				trace_square(t_obj *obj, t_vector o, t_vector v);
void				trace_cube(t_obj *obj, t_vector o, t_vector v);
void				trace_paraboloid(t_obj *obj, t_vector o, t_vector v);

/*
** Negative objects
*/
void				neg_floor(t_obj *obj, t_equation *eq);
void				neg_sphere(t_obj *obj, t_equation *eq);
void				neg_cylinder(t_obj *obj, t_equation *eq);
void				neg_sphere_fill(t_obj *obj, t_equation *eq);
void				neg_floor_fill(t_obj *obj, t_equation *eq);
void				neg_cylinder_fill(t_obj *obj, t_equation *eq);

/*
** Composed objects
*/
void				compose_obj(t_obj *obj, t_equation *eq);

/*
** Objects normale
*/
void				sphere_normale(t_vector *n, t_vector *o, t_obj *obj);
void				plane_normale(t_vector *n, t_vector *o, t_obj *obj);
void				dplane_normale(t_vector *n, t_vector *o, t_obj *obj);
void				cylinder_normale(t_vector *n, t_vector *o, t_obj *obj);
void				cone_normale(t_vector *n, t_vector *o, t_obj *obj);
void				disk_normale(t_vector *n, t_vector *o, t_obj *obj);
void				square_normale(t_vector *n, t_vector *o, t_obj *obj);
void				cube_normale(t_vector *n, t_vector *o, t_obj *obj);
void				paraboloid_normale(t_vector *n, t_vector *o, t_obj *obj);

/*
** Procedural textures
*/
void				generate_noise(t_env *e);

/*
** Events
*/
int					key_hook(int keycode, t_env *e);
int					expose_hook(t_env *e);
int					event(t_env *env, SDL_Event event);
void				event_poll(t_env *e);
void				wait_event(t_env *e);

/*
** rendering
*/
void				ft_aff(t_env *e, t_obj *obj);
void				ft_aff_quick(t_env *e, t_obj *obj);
void				ft_aff_random(t_env *e, t_obj *obj, int multithread);
void				ft_aff_multithread(t_env *e, t_obj *obj);
void				ft_aff_rand(t_th_data *a, t_env *e);

/*
** Vector utils
*/
void				rotate_vector(t_vector *v, float ang_x, float ang_y,
									float ang_z);
void				rotate_vector2(t_vector *v, t_vector *r);
void				vec_cpy(t_vector *src, t_vector *dest);
void				add_vector(t_vector *v1, t_vector *v2);
void				sub_vector(t_vector *v1, t_vector *v2);
float				vec_dot(t_vector *v, t_vector *n);
float				vec_dot_abs(t_vector *v, t_vector *n);
void				translate_vector(t_vector *origin, t_vector *dest,
										float dst);
void				mod_vector(t_obj *obj, t_vector *o, t_vector *v);
void				compute_vector(t_env *e, t_vector *v);
t_vector			*reflect_vector(t_obj *obj, t_vector *o, t_vector *v,
									t_vector *n);
t_vector			*refract_vector(t_vector *v, t_vector *o, float ref1,
		t_obj *obj);
float				vec_len(t_vector *v);
void				normalize(t_vector *v);
void				not_vec(t_vector *v);

/*
** Color utils
*/
unsigned int		mix_color(unsigned int c1, unsigned int c2);
void				color_mix_k(unsigned int *src, unsigned int color,
								unsigned int k);
void				color_add(unsigned int *src, unsigned int color,
								unsigned int k);
unsigned int		color_attenuate(unsigned int color, float k);
void				get_spec(unsigned int *color, t_light light, t_vector v, 
								t_env *e);
unsigned int		calc_color(float refangle, float angle,
								t_obj *obj, t_light *light);
unsigned int		shadow(unsigned int obj_color);

/*
** Loading bar
*/
t_img				*create_new_load_bar(t_gfx *gfx);
void				init_bar(t_img *bar, unsigned int color,
								unsigned int background);
void				change_percent(float percent, t_img *bar,
									unsigned int color,
									unsigned int background);
void				load_add_line(t_img *bar, unsigned int x,
									unsigned int color);

/*
** Get functions
*/
t_env				*get_env(void);
void				*get_normale(unsigned int i);
void				*get_func(unsigned int i, int negative);

/*
** Console
*/
int					rt_console(int keycode, t_env *e, int free_buff);
int					save_image(t_img *img, char *name);

void				error(int n);

#endif
