/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secu_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaquant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:44:43 by vcaquant          #+#    #+#             */
/*   Updated: 2017/04/26 16:49:21 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtdefs.h>
#include <parser.h>
#include <unistd.h>
#include <fcntl.h>

int		ac_count(int ac, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '{')
			ac++;
		if (str[i] == '}')
			ac--;
	}
	return (ac);
}

int		gui_count(int gui, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' && gui == 0)
			gui++;
		else if (str[i] == '\"' && gui == 1)
		{
			gui--;
			if (str[i + 1] != ':')
				return (-2);
		}
	}
	if (gui != 0)
		return (-1);
	return (gui);
}

int		first_chek(t_env *e, char *str)
{
	char	*line;
	int		fd;
	int		ret;
	int		ac;
	int		gui;

	ac = 0;
	gui = 0;
	e->nb_line = 1;
	if ((fd = open(str, O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ac = ac_count(ac, line);
		gui = gui_count(gui, line);
		if (gui == -1)
			return (-2);
		else if (gui == -2)
			return (-3);
		free(line);
		e->nb_line++;
	}
	if (e->nb_line < 3)
		return (-4);
	if (ac != 0)
		return (-1);
	if (gui != 0)
		return (-2);
	if (ret == -1)
		return (-5);
	close(fd);
	return (1);
}

void	code_error_parser(t_env *e, int error)
{
	if (error == -1)
		ft_putstr("Missing or Too much Brace. Between first line to ");
	else if (error == -2)
		ft_putstr("Missing or Too much Quotation mark. Between first line to ");
	else if (error == -3)
		ft_putstr("Missing Two points before Opening brace. In ");
	else if (error == -4)
		ft_putstr("The file is too short for a valid file. Number of line is ");
	else if (error == -5)
		ft_putstr("get_next_line crash at the line ");
	ft_putnbr(e->nb_line);
	exit(EXIT_SUCCESS);
}
