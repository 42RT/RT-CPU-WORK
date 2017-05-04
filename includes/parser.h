/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 03:28:43 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/03 20:24:01 by vcaquant         ###   ########.fr       */
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

/*PARSE COMPOSE*/
int 		parse_compose(t_env *e, t_item *item, t_obj *obj, int i);

/*PARSE FILE*/
char		*ft_getfile(char *name);

/*PARSE LIGHT*/
void		parse_light(t_env *e, t_item *item);
int			parse_dis(t_item *it, t_vector *v, int i, void (*f)(t_vector *, char *));

/*PARSE OBJ UTILS*/
void		parse_object_other(t_obj *obj, char *str);
void		parse_obj_exp(t_vector *v, char *str);
void		parse_obj_color(t_obj *obj, char *str);

/*PARSE OBJ*/
void		parse_object(t_env *e, t_item *item);
int 		parse_dis2(t_item *it, t_obj *o, int i, void (*f)(t_obj *, char *));
void 		parse_cap(t_obj *obj, char *str);
int			obj_gettype(char *str);

/*PARSE SETTINGS UTILS*/
void		parse_set_cam(t_env *e, char *str);
void		parse_other_setting(t_env *e, char *str);
void		parse_set_focus(t_env *e, char *str);

/*PARSE SETTINGS*/
void		parse_settings(t_env *e, t_item *item, int i);

/*PARSE UTILS 2*/
int			add_next_set(t_item *item, char **file);

/*PARSE UTILS*/
t_item		*get_next_item(char **str);
void		parse_pos(t_vector *v, char *str);
void		parse_ang(t_vector *v, char *str);
char		*get_value(char *str);

/*PARSE*/
void		parse(t_env *e, char *filename);

/*SECU PARSE*/
void		code_error_parser(t_env *e, int error);
void		first_chek(t_env *e, char *str);

/*PLUS*/
void		aff_obj(t_obj *obj);
void		aff_settings(t_settings *set);
void		aff_light(t_light *light);
t_obj		*new_obj(void);
t_settings	*new_settings(void);
t_light		*new_light(void);


#endif
