/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 03:28:43 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/11 12:21:24 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <libft.h>
# include <raytracer.h>

# define MAX_PARAM		100

typedef struct		s_item
{
	char			*type;
	int				setnb;
	char			*set[MAX_PARAM];
	struct s_item	*next;
}					t_item;

int					save_scene(t_env *e);
void				save_dis_nbr_nocoma(float obj, char *str, int fd, int tab);
void				save_dis_cap(int cap1, int cap2, int fd, int tab);
void				save_dis_angle(t_vector obj, int fd, int tab);
void				save_dis_triple(t_vector obj, char *str, int fd, int tab);
void				save_dis_str(char *str, char *name, int fd, int tab);
void				save_dis_nbr(float obj, char *str, int fd, int tab);
void				save_dis_next(t_obj *obj, int fd, int tab);
void				save_dis_compose(t_obj *obj, int fd, int tab);
void				save_dis_color(t_color color, int fd, int tab);
void				write_obj(int fd, t_obj *obj, int tab);
void				write_light_attributes(int fd, t_light *light, int tab);
void				write_padding(int fd, int nb);
char				*get_obj_name(t_obj *obj);
void				save_objs(int fd, t_obj *obj);
void				write_lights(int fd, t_light *light, int tab);
void				save_lights(int fd, t_light *light);
void				write_obj_attributes(int fd, t_obj *obj, int tab);
int					parse_dis_rgb(t_item *it, t_color *c, int i,
									void (*f)(t_color *, char *));
void				parse_rgb(t_color *c, char *str);
void				error_compose(void);
char				*ft_strtrim_coma(char const *s);
void				verif_obj_validity(t_obj *obj);
int					parse_compose(t_env *e, t_item *item, t_obj *obj, int i);
char				*ft_getfile(char *name);
void				parse_light(t_env *e, t_item *item);
int					parse_dis(t_item *it, t_vector *v, int i,
								void (*f)(t_vector *, char *));
int					parse_compare(t_env *e, t_item *item, t_obj *obj, int i);
void				parse_object_other(t_obj *obj, char *str);
void				parse_obj_exp(t_vector *v, char *str);
void				parse_obj_color(t_obj *obj, char *str);
void				parse_object(t_env *e, t_item *item);
int					parse_dis2(t_item *it, t_obj *o, int i,
								void (*f)(t_obj *, char *));
void				parse_cap(t_obj *obj, char *str);
int					obj_gettype(char *str);
void				parse_set_cam(t_env *e, char *str);
void				parse_other_setting(t_env *e, char *str);
void				parse_set_focus(t_env *e, char *str);
void				parse_settings(t_env *e, t_item *item, int i);
int					add_next_set(t_item *item, char **file);
t_item				*get_next_item(char **str);
void				parse_pos(t_vector *v, char *str);
void				parse_ang(t_vector *v, char *str);
char				*get_value(char *str);
void				parse(t_env *e, char *filename);
void				code_error_parser(t_env *e, int error);
void				first_chek(t_env *e, char *str);
void				check_coma(t_env *e, char *str);
int					ac_count(t_env *e, int ac, char *str);
int					gui_count(t_env *e, int gui, char *str);
void				coma_count(t_env *e, char *line);
void				aff_obj(t_obj *obj);
void				aff_settings(t_settings *set);
void				aff_light(t_light *light);
t_obj				*new_obj(void);
t_settings			*new_settings(void);
t_light				*new_light(void);
void				parse_error(void);

#endif
