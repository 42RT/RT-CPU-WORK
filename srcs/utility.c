/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 23:03:33 by jrouilly          #+#    #+#             */
/*   Updated: 2014/03/27 23:03:33 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <raytracer.h>


#include <stdio.h>

/*
void		compute_vector(t_env *e, t_vector *v)
{
	v->x = (int)e->x - (int)(e->set->width / 2);
	v->y = (int)e->y - (int)(e->set->height / 2);
	v->z = -720;
	rotate_vector(v, e->set->cam->ang.x, e->set->cam->ang.y, e->set->cam->ang.z);
//	rotate_vector(v, ts->cam.angle.x, ts->cam.angle.y, ts->cam.angle.z);
}*/

void		compute_vector(t_env *e, t_vector *v)
{
	float	k;
	float	ang;

	ang = (M_PI_2 * (float)e->set->fov) / 180;


	v->x = e->x - (e->set->width / 2);
	v->y = e->y - (e->set->height / 2);
	v->z = -((int)e->set->width / (2 * fabs(cos(ang / 2)))); // a modifier par rapport au fov
	rotate_vector(v, e->set->cam->ang.x, e->set->cam->ang.y, e->set->cam->ang.z);

	k = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= k;
	v->y /= k;
	v->z /= k;
	(void)k;
}

/* a modifier pour enlever le fish eye */
/*
void		compute_vector(t_env *e, t_vector *v)
{
	float	k;
	float	ang_x;
	float	ang_y;
	float	fov;
	float	ratio;

	ratio = (float)e->set->height / (float)e->set->width;
	fov = M_PI_2 * (float)e->set->fov / 100;
	ang_y = fov / 2 - ((float)e->x / (float)e->set->width) *
								fov;
	ang_x = (-fov / 2 + ((float)e->y / (float)e->set->height)
				* fov) * ratio;
	v->x = 0;
	v->y = 0;
	v->z = -1;
	rotate_vector(v, ang_x, ang_y, 0);
	rotate_vector(v, e->set->cam->ang.x + ang_x, e->set->cam->ang.y
					+ ang_y, e->set->cam->ang.z);
	//pas obligatoire ?
	k = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= k;
	v->y /= k;
	v->z /= k;
}*/

int			**new_base()
{
	int		**res;

	res = (int **)malloc(3 * sizeof(int *));
	res[0] = (int *)malloc(3 * sizeof(int));
	res[1] = (int *)malloc(3 * sizeof(int));
	res[2] = (int *)malloc(3 * sizeof(int));
	res[0][0] = 1;
	res[0][1] = 0;
	res[0][2] = 0;
	res[1][0] = 0;
	res[1][1] = 1;
	res[1][2] = 0;
	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = 1;
	return (res);
}

unsigned int	limit_nb(unsigned int nb, unsigned int max)
{
	if (nb > max)
		nb = max;
	return (nb);
}


t_vector		*reflect_vector(t_vector *o, t_vector *v, t_vector *n, t_obj *obj)
{
//	t_vector	n; // refaire avec n dans ts
	float		scal;

//	o->x += obj->dst * v->x;
//	o->y += obj->dst * v->y;
//	o->z += obj->dst * v->z;
//	(obj->normale)(&n, o, obj); // au lieu de creer n (la normale), essayer d'ajouter directement a obj
	scal = vec_dot(v, n);
	(void)scal;
	v->x -= 2 * n->x * scal;
	v->y -= 2 * n->y * scal;
	v->z -= 2 * n->z * scal;
	(void)o;
	(void)obj;
	return (v);
}

/*
t_vector		*refract_vector(ts, v, shorter)
{
// a faire
}
*/

unsigned int	new_ray(t_env *e, t_vector *o, t_vector *v, t_obj *obj, unsigned int deph)
{
	t_obj		*start;

	start = obj;
	while (obj)
	{
		trace_ray(e, obj, o, v, 0);
		obj = obj->next;
	}
	return (ray_effect(e, o, v, start, deph));// a verifier, et penser a compter le nombre de recursions
}

int				ray_effect(t_env *e, t_vector *o, t_vector *v, t_obj *obj, unsigned int deph)
{
	t_obj			*shorter;
	t_obj			*start;
	unsigned int	color;
	unsigned int	c;
	t_vector		n;
	float			dst;

	dst = 1e8;
	if (!obj)
		return(0);
	shorter = 0;
	start = obj;
	while (obj)
	{
		if (obj->dst >= 0 && obj->dst < dst)
			shorter = obj;
		dst = (shorter ? shorter->dst : 1e8);
		obj = obj->next;
	}
	e = e;
	v = v;
	color = 0;
	if (!shorter)
		return (0);
	color = shorter->color;
//	color_add(&color, shorter->color, 255);//shorter->diffusion_k);
	o->x += shorter->dst * v->x;
	o->y += shorter->dst * v->y;
	o->z += shorter->dst * v->z;
	(shorter->normale)(&n, o, shorter);
	if (--deph > 0 && shorter && (shorter->type == SPHERE))// || shorter->type == DFLOOR)) // ne fonctionne pas correctement
	{
		// relief objets
		color = color_attenuate(color, vec_dot_abs(v, &n));
		//printf("42: %f:%f:%f\n", o->x, o->y, o->z);
		c = new_ray(e, o, reflect_vector(o, v, &n, shorter), start, deph);
		// attention. pas de copie de o et v, donc modifications indesirables dans la recursion (comme pour la profondeur)
		(void)c;
		c |= 0xFF000000;
//		color_mix_k(&color, c, 100);
		color_add(&color, c, 150);
//		color_add(&color, c, shorter->reflect_k);
//		c = new_ray(e, refract_vector(ts, v, shorter), start, deph);
//		color_add(&color, shorter->refract_color, shorter->refract_k);
	}
	// brouillard de guerre
	color = mod_light(color, dst, 256);
	return (color);
}

unsigned int	compute_color(t_env *e, t_obj *obj, unsigned int deph)
{
	t_obj		*start;
	t_vector	v;
	t_vector	o;

//	ft_printf("test\n");
	compute_vector(e, &v);
	//VECTEUR IDENTIQUE APPAREMENT
//	printf("vec: %f, %f, %f\n", v.x, v.y, v.z);
	start = obj;
	o.x = e->set->cam->pos.x;
	o.y = e->set->cam->pos.y;
	o.z = e->set->cam->pos.z;
	// identique
//	printf("%f | %f | %f\n", o.x, o.y, o.z);
	while (obj)
	{
//	ft_printf("test2\n");
		trace_ray(e, obj, &o, &v, 1); // bug here
//	ft_printf("test3\n");
		obj = obj->next;
	}
//	ts->act_deph = e->set->deph;// refaire principe profondeur
	return (ray_effect(e, &o, &v, start, deph));
}

