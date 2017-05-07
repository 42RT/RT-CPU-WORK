/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secu_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaquant <vcaquant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:44:43 by vcaquant          #+#    #+#             */
/*   Updated: 2017/05/07 05:32:49 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtdefs.h>
#include <parser.h>
#include <unistd.h>
#include <fcntl.h>

void	error_compose(void)
{
	ft_printf("No A Good Object in Compose\n");
	exit(EXIT_SUCCESS);
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
		if ((ft_strcchr(line, '\"', '\0') == NULL) && line[0] != '\0' &&
				(ft_strcchr(line, '}', '\0') == NULL))
			code_error_parser(e, -11);
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
	else if (error == -11)
		ft_printf("Bad syntax line %d\n", e->nb_line);
	exit(EXIT_SUCCESS);
}
