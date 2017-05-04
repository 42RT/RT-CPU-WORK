/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_secu_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaquant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 22:07:06 by vcaquant          #+#    #+#             */
/*   Updated: 2017/05/04 22:07:09 by vcaquant         ###   ########.fr       */
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
