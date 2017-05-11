/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <rdieulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/11 12:13:12 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include <parser.h>

char	*gui_old_path(char *path)
{
	char	*old;
	char	*tmp;

	tmp = ft_strjoin("cp ", path);
	old = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_strjoin(old, path);
	free(old);
	old = ft_strjoin(tmp, ".old");
	free(tmp);
	return (old);
}

char	*gui_new_path(char *path)
{
	char	*new;
	char	*tmp;

	tmp = ft_strjoin("rm ", path);
	new = ft_strjoin(tmp, " |");
	free(tmp);
	tmp = ft_strjoin(new, "mv ");
	free(new);
	new = ft_strjoin(tmp, "scene/tmpsave.rts");
	free(tmp);
	tmp = ft_strjoin(new, " ");
	free(new);
	new = ft_strjoin(tmp, path);
	free(tmp);
	return (new);
}

void	gui_save_object(t_gui *gui, t_env *e)
{
	(void)gui;
	system(gui_old_path(e->scene));
	if (!save_scene(e))
		gui_error(15);
	system(gui_new_path(e->scene));
}
