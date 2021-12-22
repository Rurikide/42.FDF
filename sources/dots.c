/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 22:25:23 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/22 09:57:24 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void	back_up_dots(t_fdf *fdf)
{
	int i;
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
	// fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
	// fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
	fdf->dot[i].x = (fdf->dot[i].dcol * fdf->line_len);
	fdf->dot[i].y = (fdf->dot[i].drow * fdf->line_len);
	fdf->dot[i].z = 0;
}

void	set_dot_position(char **elements, t_fdf *fdf)
{
	static int i;
	int pos;

	pos = 0;
	if (fdf->nb_dots > 900)
	{
		fdf->line_len = 10;
	}
	while (*elements && **elements != '\n')
	{
		fdf->dot[i].dcol = i % fdf->column; 
		fdf->dot[i].drow = i / fdf->column; 	
		// fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
		// fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
		fdf->dot[i].x = (fdf->dot[i].dcol * fdf->line_len);
		fdf->dot[i].y = (fdf->dot[i].drow * fdf->line_len);
		fdf->dot[i].z = ft_atoi(*elements);

		if (fdf->dot[i].z == 0)
			fdf->dot[i].color = 0x00000000;
		else
			fdf->dot[i].color = 0x00FFFFFF;
		
		fdf->dot[i].missing = 0;

		i++;
		pos++;
		elements++;
	}
	if (pos < (fdf->column))
		{
			set_missing_dot_pos(i, fdf);
			i++;
		}
}