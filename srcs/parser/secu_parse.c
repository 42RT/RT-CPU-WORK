/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secu_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaquant <vcaquant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:44:43 by vcaquant          #+#    #+#             */
/*   Updated: 2017/04/27 13:55:45 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtdefs.h>
#include <parser.h>
#include <unistd.h>
#include <fcntl.h>

int		ac_count(t_env *e, int ac, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '{')
		{
			ac++;
			if (str[i + 1] != '\0')
			code_error_parser(e, -8);
		}
		if (str[i] == '}')
			ac--;
	}
	return (ac);
}

int		gui_count(t_env *e, int gui, char *str)
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
				code_error_parser(e, -3);
		}
	}
	if (gui != 0)
		code_error_parser(e, -2);
	return (gui);
}

void	check_coma(t_env *e, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ',')
		{
			e->coma = 1;
			if (str[i + 1] != '\0')
				code_error_parser(e, -9);
		}
		else
			e->coma = 0;
	}
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
	e->coma = 0;
	e->nb_line = 0;
	if ((fd = open(str, O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		e->nb_line++;
		if (ft_strchr(line, '{') == NULL && *line != '\0')
		{
			if ((ft_strchr(line, '}') == NULL) && e->coma == 0)
				return (-6);
			else if ((ft_strchr(line, '}') != NULL) && e->coma == 1)
				return (-7);
			check_coma(e, line);
		}
		else
			e->coma = 1;
		ac = ac_count(e, ac, line);
		gui = gui_count(e, gui, line);
		free(line);
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
	else if (error == -6)
	{
		ft_putstr("Missing Coma line ");
		e->nb_line--;
	}
	else if (error == -7)
	{
		ft_putstr("Bad syntax, Not need Coma in the line ");
		e->nb_line--;
	}
	else if (error == -8)
		ft_putstr("Something after Opening brace in line ");
	else if (error == -9)
		ft_putstr("Character after a Coma, line ");
	ft_putnbr(e->nb_line);
	exit(EXIT_SUCCESS);
}
