/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:04:33 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/05 09:51:20 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtdefs.h>
#include <parser.h>

int		obj_gettype(char *str)
{
	if (!ft_strncmp(str, "\"sphere\"", 8))
		return (SPHERE);
	else if (!ft_strncmp(str, "\"plan\"", 6))
		return (PLANE);
	else if (!ft_strncmp(str, "\"dplane\"", 8))
		return (DPLANE);
	else if (!ft_strncmp(str, "\"cylindre\"", 10))
		return (CYLINDER);
	else if (!ft_strncmp(str, "\"cone\"", 6))
		return (CONE);
	else if (!ft_strncmp(str, "\"disk\"", 6))
		return (DISK);
	else if (!ft_strncmp(str, "\"square\"", 8))
		return (SQUARE);
	else if (!ft_strncmp(str, "\"cube\"", 6))
		return (CUBE);
	else if (!ft_strncmp(str, "\"paraboloid\"", 13))
		return (PARABOLOID);
	else if (!ft_strncmp(str, "\"glass\"", 7))
		return (GLASS);
	else
		return (NONE);
}

void	add_obj(t_env *e, t_obj *obj)
{
	if (obj->negative)
	{
		obj->next = e->neg_obj;
		e->neg_obj = obj;
	}
	else
	{
		obj->next = e->obj;
		e->obj = obj;
	}
}

void	load_texture(t_obj *obj)
{
	char	*path;
	char	*path2;

	path = ft_strjoin("ressources/textures/", obj->texture);
	path2 = ft_strjoin(path, ".bmp");
	free(path);
	obj->surface = SDL_LoadBMP(path2);
	if (obj->surface)
	{
		obj->tex_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, obj->surface->w,
			obj->surface->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff,
			0xff000000);
		SDL_BlitSurface(obj->surface, NULL, obj->tex_surface, NULL);
		SDL_FreeSurface(obj->surface);
	}
	else
		obj->tex_surface = NULL;
	free(path2);
}

void	load_normalmap(t_obj *obj)
{
	char	*path;
	char	*path2;

	path = ft_strjoin("ressources/normalmap/", obj->normalmap);
	path2 = ft_strjoin(path, ".bmp");
	free(path);
	obj->surface = SDL_LoadBMP(path2);
	if (obj->surface)
	{
		obj->nm_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, obj->surface->w,
			obj->surface->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff,
			0xff000000);
		SDL_BlitSurface(obj->surface, NULL, obj->nm_surface, NULL);
		SDL_FreeSurface(obj->surface);
	}
	else
		obj->nm_surface = NULL;
	free(path2);
}

void	parse_object(t_env *e, t_item *item)
{
	t_obj	*obj;
	int		i;

	obj = new_obj();
	i = -1;
	while (++i < item->setnb)
		i = parse_compare(e, item, obj, i);
	obj->type = obj_gettype(item->type);
	if (obj->type == 128)
		obj->cap2 = 1000;
	if (obj->type == GLASS)
		glass(obj);
	if (obj->texture)
		load_texture(obj);
	if (obj->normalmap)
		load_normalmap(obj);
	obj->func = get_func(obj->type, obj->negative);
	obj->normale = get_normale(obj->type);
	obj->base = new_base();
	if (obj->type)
		add_obj(e, obj);
	e->yon = 1;
}
