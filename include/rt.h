/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 13:26:09 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/17 21:21:46 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <rtdefs.h>

# define EPS 0.01
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
** COMPOSED OBJECTS DEFINE
*/

# define COMPOSEPOS env->obj->compose->vec1
# define COMPOSEN env->obj->compose->vec2

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

/*
** DEFINE GUI
*/

# define GUI_WIDTH 400
# define GUI_THEME 0
# define GUI_DYNAMIC 1
# define GUI_CONSTANT 0
# define GUI_RESS_PATH "./ressources/"
# define GUI_TEXTURE_PATH GUI_RESS_PATH"gui_texture/"
# define GUI_FONT_SIZE 18
# define GUI_FONT_FILE "gui_font/Xenotron.ttf"
# define GUI_FONT_STYLE
# define GUI_FONT_BORDER_STEP 5
# define GUI_ALIGN_LEFT 0
# define GUI_ALIGN_MID 1
# define GUI_ALIGN_RIGHT 2
# define GUI_CONTAINER_TOTAL_NB 6
# define GUI_CONTAINER_DYNAMIC_NB 2
# define GUI_CONTAINER_HEADER 80
# define GUI_CONTAINER_FOOT 40
# define GUI_CONTAINER_MIDDLE 0
# define GUI_CONTAINER_RESERVED ((GUI_CONTAINER_HEADER * 2) \
		+ (GUI_CONTAINER_FOOT * 2))
# define GUI_CONTAINER_RESIZED ((gui->height - \
			GUI_CONTAINER_RESERVED) / GUI_CONTAINER_DYNAMIC_NB)
# define CONTAINER gui->container[gui->cbcnt]
# define BLOCK gui->container
# define TTF gui->ttf
# define BUTTON BLOCK[id]->button

# include <math.h>
# include <fcntl.h>
# ifdef __APPLE__
#  include <SDL.h>
#  include <SDL_ttf.h>
# else
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_ttf.h>
# endif
# include <libft.h>
# include <lib_vec.h>

/*
** Unused now, but needed for compilation
*/

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
}					t_vector;

typedef struct		s_cam
{
	t_vector		pos;
	t_vector		ang;
}					t_cam;

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

/*
**end of unused structs
*/

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
	int				type;
	void			(*func)();
	void			(*normale)();
	int				**base;
	int				negative;
	t_vector		pos;
	t_vector		ang;
	t_vector		exp;
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
	struct s_obj	*next;
	t_vec			vec1;
	t_vec			vec2;
	int				cap1;
	int				cap2;
	int				reflect;
	double			r;
	double			d1;
	double			d2;
	t_color			color_t;
	char			*textures;
	struct s_obj	*compose;
	struct s_obj	*first;
}					t_obj;

typedef struct		s_parse
{
	t_vec			pos;
	t_vec			n;
	t_color			color;
	double			r;
}					t_parse;

typedef struct		s_ray
{
	t_vec			vecdir;
	t_vec			pos;
	t_vec			reflect;
	double			dist;
	t_color			color;
}					t_ray;

typedef struct		s_camera
{
	t_vec			campos;
	t_vec			vecdirx;
	t_vec			vecdiry;
	t_vec			vecdirz;
	t_vec			vpul;
	double			xindent;
	double			yindent;
}					t_camera;

typedef struct		s_spot
{
	t_vec			spotpos;
	t_color			color;
	t_ray			ray;
	struct s_spot	*first;
	struct s_spot	*next;
}					t_spot;

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

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*img;
	SDL_Event		event;
	t_settings		*set;
	int				i;
	unsigned int	x;
	unsigned int	y;
	t_parse			data;
	t_line			*file;
	t_obj			*obj;
	t_obj			*neg_obj;/////compilation only
	t_light			*light;//unused now
	t_camera		cam;
	t_spot			*spot;
}					t_env;

typedef struct		s_ttf
{
	TTF_Font		*font;
	SDL_Texture		*texture;
	SDL_Rect		rect;
	int				h_px;
	int				w_px;
}					t_ttf;

typedef struct		s_scroll
{
	int				align;
}					t_scroll;

typedef struct		s_button
{
	int				align;
	int				w;
	int				h;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
}					t_button;

typedef struct		s_textbox
{
	int				align;
}					t_textbox;

typedef struct		s_container
{
	int				up_lim;
	int				bot_lim;
	int				px;
	int				button_qt;
	int				scroll_qt;
	int				textbox_qt;
	SDL_Surface		*surface;
	SDL_Texture		*bmp;
	SDL_Rect		dest;
	t_button		**button;
	t_scroll		**scroll;
	t_textbox		**textbox;
}					t_container;

typedef struct		s_gui
{
	SDL_Window		*win;
	SDL_Renderer	*img;
	SDL_Event		gui_event;
	SDL_DisplayMode	*display;
	SDL_Surface		*bg_surface;
	SDL_Texture		*bg_bmp;
	SDL_Rect		bg_dest;
	t_color			*color;
	t_container		**container;
	t_ttf			*ttf;
	int				cbcnt;
	int				width;
	int				height;
	int				anchor_x;
	int				anchor_y;
	int				tmp_lim;
}					t_gui;

/*
** NOT SORTED - DAWNAUR
*/

t_env				*get_env(void);
//void				*get_normale(unsigned int i);
//void				*get_func(unsigned int i);
int					**new_base(void);
unsigned int		get_color(char *str);
void				aff_settings(t_settings *set);

/*
** COLOR_UTILS
*/
void				color_mix_k(unsigned int *src, unsigned int color,
								unsigned int k);
void				color_mix_float(t_color *src, t_color *color,
									float k);
unsigned int		limit_nb(unsigned int nb, unsigned int max);

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
double				ft_atod(char *str);
t_color				default_color(void);
t_color				default_color_spot(void);
t_vec				default_pos(void);
t_vec				default_n(void);
void				free_file(t_env *env);
int					gotonextvalue(t_env *env, int i);
t_color				init_color_black(void);

t_vec				calc_ncone(t_ray *ray, t_obj *obj);
t_vec				calc_ncylinder(t_ray *ray, t_obj *obj);

t_env				*init_env(int fd);
void				init_graphics(t_env *env);

/*
** PARSER FUNCTIONS
*/

t_vec				get_vector(t_env *env);
t_color				get_color_t(t_env *env);
t_color				get_color_spot(t_env *env);
t_color				color_correc_spot(t_color color);
t_color				color_correc_obj(t_color color);
void				old_parse_camera(t_env *env);
void				old_parse_sphere(t_env *env);
void				old_parse_spot(t_env *env);
void				old_parse_plane(t_env *env);
void				old_parse_cylinder(t_env *env);
void				old_parse_cone(t_env *env);
void				old_parse_file(t_env *env);

/*
** CAMERA FUNCTIONS
*/

t_camera			init_cam(t_env *env, double x, double y, double z);
void				transcam(t_env *env, t_vec trans);
void				rotcam(t_env *env, double rx, double ry, double rz);
void				camangle(t_env *env, double rx, double ry, double rz);

/*
** GUI FUNCTIONS
*/

t_gui				*get_gui(void);
t_gui				*gui_init(void);
void				gui_pixel_put(t_gui *gui, int x, int y);
void				gui_color_set(t_gui *gui, char *type, char *style);
void				gui_background_get_set_n_display(t_gui *gui);
void				gui_container_build(t_gui *gui, int mode, int px);
void				gui_error(int n);
void				gui_font_build(t_gui *gui);
void				gui_button_build(t_gui *gui);

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

/*
** COMPOSED OBJECTS
*/

int					compose_obj(t_env *env, t_ray *ray, float dist);
t_obj				*create_plan_compose(t_vec pos, t_color color, t_vec n);
t_obj				*create_sphere_compose(t_vec pos, t_color color, float r);

/*
** PROCEDURAL TEXTURES
*/

t_color				stripe(t_vec point);
t_color				square(t_vec point);

#endif
