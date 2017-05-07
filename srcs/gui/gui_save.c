/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

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

void	gui_save_object(t_gui *gui, t_env *e)
{
	(void)gui;
	system(gui_old_path(e->scene));
//	if (!save_scene(e))
//		gui_error(15);
}
