/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 15:59:32 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/06 13:57:38 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <parser.h>
#include <math.h>

char	*ft_strtrim_coma(char const *s)
{
	int		i;
	char	*ptr;
	char	*result;

	if (!s || !*s)
		return (NULL);
	i = 0;
	ptr = (char *)(s - 1);
	while (*ptr == ':')
		++ptr;
	result = (char *)malloc(ft_strlen(ptr) * sizeof(char));
	ptr -= 1;
	i = -1;
	while (*++ptr)
		*(++i + result) = *ptr;
	ptr = i + result;
	while (*ptr == ',')
	{
		*ptr = '\0';
		--ptr;
	}
	return (result);
}

char	*get_value(char *str)
{
	char	*tmp;

	tmp = str;
	while (*str && *str != ':')
		++str;
	if (*str)
		++str;
	if (*str == '}' || *str == ',')
	{
		ft_printf("Bad value\n");
		exit(EXIT_SUCCESS);
	}
	if (ft_strchr(str, ',') != NULL)
	{
		tmp = ft_strtrim_coma(str);
		str = tmp;
		free(tmp);
	}
	return (str);
}

char	*while_item(t_item *item, char *file)
{
	int		i;

	i = 0;
	while (file && *file)
	{
		if (ft_strcchr(file, '{', '\n') != NULL)
			i++;
		if (ft_strcchr(file, '}', '\n') != NULL && i == 0)
			break ;
		else if (ft_strcchr(file, '}', '\n') != NULL && i > 0)
			i--;
		if (add_next_set(item, &file) == 0)
			exit(EXIT_SUCCESS);
	}
	return (file);
}

t_item	*get_next_item(char **str)
{
	char	*file;
	t_item	*item;

	if (ft_strcchr(*str, '\"', '\n') == NULL)
		exit(EXIT_SUCCESS);
	file = *str;
	item = (t_item *)malloc(sizeof(t_item));
	item->type = ft_strdup_trim(file);
	item->setnb = 0;
	if (!item)
		exit(EXIT_SUCCESS);
	file = ft_strchr(file, '{');
	file++;
	file += (*file != 0);
	file = while_item(item, file);
	while (*file && (*file == ' ' || *file == '\n' || *file == '\r'
						|| *file == '\t' || *file == '}' || *file == ','))
		++file;
	*str = file;
	return (item);
}

int		init(t_env *e, char *scene)
{
	e->set = new_settings();
	e->obj = 0;
	e->neg_obj = 0;
	parse(e, scene);
	parse(e, "set.rtc");
	if (e->yon != 1)
	{
		ft_printf("No Object\n");
		exit(EXIT_SUCCESS);
	}
	e->worker = 0;
	e->worker_stop = (int *)malloc(sizeof(int));
	*(e->worker_stop) = 0;
	e->rendering_preview = 0;
	return (0);
}
