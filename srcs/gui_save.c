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
	item =	i = gui->container[1]->scroll[0]->nb_value - 1;
	errno = 0;
	(void)gui;
	system(gui_old_path(e->av[1]));
	if ((fd1 = open(e->av[1], O_RDONLY)) != -1)
	{
		if ((fd2 = creat("scene/tmpsave.rts", O_CREAT | S_IRWXU | S_IRWXG | S_IRWXO)) != -1)
		{
			close(fd1);
			close(fd2);
		}
		else
			gui_error(15);
	}
	else
		gui_error(9);
}
