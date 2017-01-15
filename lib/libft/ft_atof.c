/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 14:57:56 by jrouilly          #+#    #+#             */
/*   Updated: 2014/11/28 14:57:56 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		ft_atof(char *str)
{
	int		decimal;
	int		floating;
	int		divide;
	int		sign;

	decimal = 0;
	floating = 0;
	divide = 1;

	sign = 1 - ((*str == '-') << 1);
	str += (*str == '-' || *str == '+');
	while (*str && *str != '.')
		decimal = decimal * 10 + (*(str++) - 060);
	if (!*str)
		return (sign * decimal);
	while (*++str >= '0' && *str <= '9')
	{
		floating = floating * 10 + (*str - 060);
		divide *= 10;
	}
	return (sign * (decimal + (float)floating / divide));
}