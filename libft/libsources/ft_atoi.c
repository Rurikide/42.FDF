/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:36:30 by tshimoda          #+#    #+#             */
/*   Updated: 2021/06/07 10:40:42 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_atoi_core(char *s, int minus)
{
	int		i;
	long	nombre;

	i = 0;
	nombre = 0;
	while (((unsigned char)s[i] >= '0') && ((unsigned char)s[i] <= '9'))
	{
		if ((((nombre * 10) + (s[i] - 48)) < nombre) && (minus == 1))
			return (-1);
		else if ((((nombre * 10) + (s[i] - 48)) < nombre) && (minus == -1))
			return (0);
		nombre = (nombre * 10) + ((unsigned char)s[i] - 48);
		i++;
	}
	return (nombre);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	nombre;
	char	*s;
	int		minus;

	i = 0;
	s = (char *)str;
	minus = 1;
	while ((9 <= s[i] && s[i] <= 13) || (s[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	nombre = ft_atoi_core(&s[i], minus);
	nombre = nombre * minus;
	return ((int)nombre);
}
