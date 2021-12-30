/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 22:25:23 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/29 21:07:34 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	back_up_dots(t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->dot_bu = (t_dot *)ft_calloc(fdf->nb_dots, sizeof(t_dot));
	while (i < fdf->nb_dots)
	{
		fdf->dot_bu[i] = fdf->dot[i];
		i++;
	}
}

void	set_missing_dot_pos(int i, t_fdf *fdf)
{
	fdf->dot[i].missing = 1;
	fdf->dot[i].dcol = i % fdf->column;
	fdf->dot[i].drow = i / fdf->column;
	fdf->dot[i].x = (fdf->dot[i].dcol * fdf->line_len);
	fdf->dot[i].y = (fdf->dot[i].drow * fdf->line_len);
	fdf->dot[i].z = 0;
}

int	hex_to_dec(char *elements)
{
	int	nb;
	int	len;
	int	base;
	int	decimal;

	len = ft_strlen(elements) - 1;
	base = 1;
	decimal = 0;
	while (len >= 0)
	{
		if (ft_isdigit(elements[len]))
			nb = elements[len] - '0';
		else
			nb = ft_toupper(elements[len]) - 'A' + 10;
		decimal += nb * base;
		base *= 16;
		len--;
	}
	return (decimal);
}

void	fdf_line_len(t_fdf *fdf)
{
	if (fdf->nb_dots > 10000)
	{
		fdf->line_len = 1;
	}
	else if (fdf->nb_dots > 900)
	{
		fdf->line_len = 5;
	}
}

void	set_dot_position(char **elements, t_fdf *fdf)
{
	static int	i;
	int			pos;

	pos = 0;
	fdf_line_len(fdf);
	while (*elements && **elements != '\n')
	{
		fdf->dot[i].dcol = i % fdf->column;
		fdf->dot[i].drow = i / fdf->column;
		fdf->dot[i].x = (fdf->dot[i].dcol * fdf->line_len);
		fdf->dot[i].y = (fdf->dot[i].drow * fdf->line_len);
		fdf->dot[i].z = ft_atoi(*elements);
		if (fdf->dot[i].z > fdf->z_highest)
			fdf->z_highest = fdf->dot[i].z;
		if (fdf->dot[i].z < fdf->z_lowest)
			fdf->z_lowest = fdf->dot[i].z;
		fdf->dot[i].color = parse_color(*elements);
		fdf->dot[i].missing = 0;
		i++;
		pos++;
		elements++;
	}
	if (pos < (fdf->column))
		set_missing_dot_pos(i++, fdf);
}
