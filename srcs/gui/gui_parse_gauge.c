/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_gauge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 01:29:15 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_parse_gauge_suite(t_gauge *gauge, char **tmp)
{
	char	**tmp2;

	tmp2 = NULL;
	if (!CMP(tmp[0], "\t\ttag"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		gauge->tag = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\t\ttxt"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		gauge->txt->content = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\t\ttxt_anchor"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		gauge->txt->anchor = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_array((void ***)&tmp2, 2);
}

t_gauge	*gui_parse_gauge(int fd, int nb)
{
	t_gauge	*gauge;
	char	**tmp;
	char	*line;

	gauge = gui_gauge_init();
	while (nb > 0)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!CMP(tmp[0], "\t\tx"))
			gauge->dest.x = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\t\ty"))
			gauge->dest.y = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\t\tmin"))
			gauge->min = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\t\tmax"))
			gauge->max = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\t\ttxt_align"))
			gauge->txt->align = ft_atoi(tmp[1]);
		else
			gui_parse_gauge_suite(gauge, tmp);
		gui_free_array((void ***)&tmp, 2);
		nb--;
	}
	return (gauge);
}
