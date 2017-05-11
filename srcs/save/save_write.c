#include <fcntl.h>
#include <raytracer.h>
#include <parser.h>

void	write_padding(int fd, int nb)
{
	int		i;

	i = -1;
	while (++i < nb)
		ft_putchar_fd('\t', fd);
}

void	write_obj_att_other(int fd, t_obj *obj, int tab)
{
    if (obj->texture != NULL)
		save_dis_str("texture", obj->texture, fd, tab);
	if (obj->normalmap != NULL)
		save_dis_str("normalmap", obj->normalmap, fd, tab);
	if (obj->procedural != NULL)
		save_dis_str("procedural", obj->procedural, fd, tab);
	if (obj->cap1 != 0 || obj->cap2 != 0)
		save_dis_cap(obj->cap1, obj->cap2, fd, tab);
	if (obj->pos.x != 0 || obj->pos.y != 0 || obj->pos.z != 0)
		save_dis_triple(obj->pos, "position", fd, tab);
	if (obj->ang.x != 0 || obj->ang.y != 0 || obj->ang.z != 0)
		save_dis_angle(obj->ang, fd, tab);
	if (obj->exp.x != 1 || obj->exp.y != 1 || obj->exp.z != 1)
		save_dis_triple(obj->exp, "exp", fd, tab);
}

void	write_obj_attributes(int fd, t_obj *obj, int tab)
{
	if (obj->mod != 1)
		save_dis_nbr(obj->mod, "mod", fd, tab);
	if (obj->negative == 1)
	{
		write_padding(fd, tab);
		ft_putstr_fd("\"negative\": 1,\n", fd);
	}
	if (obj->reflect_k != 0)
		save_dis_nbr(obj->reflect_k, "reflect_k", fd, tab);
	if (obj->transparency != 0)
		save_dis_nbr(obj->transparency, "transparency", fd, tab);
	if (obj->refract_ind != 1)
		save_dis_nbr(obj->refract_ind, "refract_ind", fd, tab);
	if (obj->def.x != 0 || obj->def.y != 0 || obj->def.z != 0)
		save_dis_triple(obj->def, "def", fd, tab);
    write_obj_att_other(fd, obj, tab);
	if (obj->compose != NULL)
	{
		save_dis_compose(obj->compose, fd, tab);
		if (obj->compose->next != NULL)
			save_dis_next(obj->compose, fd, tab);
	}

	save_dis_color(obj->color, fd, tab);
	save_dis_nbr_nocoma(obj->size, "size", fd, tab);
}

void	write_light_attributes(int fd, t_light *light, int tab)
{
	if (light->mod != 1)
		save_dis_nbr(light->mod, "mod", fd, tab);
	if (light->pos.x != 0 || light->pos.y != 0 || light->pos.z != 0)
		save_dis_triple(light->pos, "position", fd, tab);
	if (light->ang.x != 0 || light->ang.y != 0 || light->ang.z != 0)
		save_dis_angle(light->ang, fd, tab);
	save_dis_color(light->color, fd, tab);
    save_dis_nbr(light->coef_ambient, "coef_ambient", fd, tab);
    save_dis_nbr(light->coef_diffuse, "coef_diffuse", fd, tab);
    save_dis_nbr_nocoma(light->coef_spec, "coef_spec", fd, tab);
}

void	write_obj(int fd, t_obj *obj, int tab)
{
	ft_putstr_fd("\"", fd);
	ft_putstr_fd(get_obj_name(obj), fd);
	ft_putstr_fd("\": {\n", fd);
	write_obj_attributes(fd, obj, tab);
	ft_putstr_fd("}", fd);
}
