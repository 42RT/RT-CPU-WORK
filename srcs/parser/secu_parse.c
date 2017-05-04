/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secu_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaquant <vcaquant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:44:43 by vcaquant          #+#    #+#             */
/*   Updated: 2017/05/03 19:35:20 by vcaquant         ###   ########.fr       */
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

void	coma_count(t_env *e, char *line)
{
	if (ft_strchr(line, '{') == NULL && *line != '\0')
	{
		if ((ft_strchr(line, '}') == NULL) && e->coma == 0)
			code_error_parser(e, -6);
		else if ((ft_strchr(line, '}') != NULL) && e->coma == 1)
			code_error_parser(e, -7);
		check_coma(e, line);
	}
	else if (ft_strchr(line, '{') != NULL && e->coma == 0)
		code_error_parser(e, -6);
	else
		e->coma = 1;
}

void	return_error(t_env *e, int ac, int gui, int ret)
{
	if (e->nb_line < 3)
		code_error_parser(e, -4);
	if (ac != 0)
		code_error_parser(e, -1);
	if (gui != 0)
		code_error_parser(e, -2);
	if (ret == -1)
		code_error_parser(e, -5);
}

void	first_chek(t_env *e, char *str)
{
	char	*line;
	int		fd;
	int		ret;
	int		ac;
	int		gui;

	ac = 0;
	gui = 0;
	e->coma = 1;
	e->nb_line = 0;
	if ((fd = open(str, O_RDONLY)) == -1)
		code_error_parser(e, 0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		e->nb_line++;
		coma_count(e, line);
		ac = ac_count(e, ac, line);
		gui = gui_count(e, gui, line);
		free(line);
	}
	close(fd);
	return_error(e, ac, gui, ret);
}

void	code_error_parser(t_env *e, int error)
{
	if (error == 0)
		ft_printf("Open return : -1\n");
	else if (error == -1)
		ft_printf("Missing or Too much Brace. Between 1 to %d\n", e->nb_line);
	else if (error == -2)
		ft_printf("Missing or Too much Quotes. Between 1 to %d\n", e->nb_line);
	else if (error == -3)
		ft_printf("Missing Two points, line %d\n", e->nb_line);
	else if (error == -4)
		ft_printf("Too short file. Number of line is %d\n", e->nb_line);
	else if (error == -5)
		ft_printf("get_next_line crash at the line %d\n", e->nb_line);
	else if (error == -6)
		ft_printf("Missing Coma line %d\n", e->nb_line - 1);
	else if (error == -7)
		ft_printf("Bad syntax, Not need Coma in the line %d\n", e->nb_line - 1);
	else if (error == -8)
		ft_printf("Something after Opening brace in line %d\n", e->nb_line);
	else if (error == -9)
		ft_printf("Character after a Coma, line %d\n", e->nb_line);
	else if (error == -10)
		ft_printf("No Object in file\n");
	exit(EXIT_SUCCESS);
}
