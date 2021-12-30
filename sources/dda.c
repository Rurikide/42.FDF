/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 10:26:07 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/29 22:32:25 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_dda_slope(t_fdf *fdf, t_dot *a, t_dot *b)
{
	int	i;

	i = 0;
	fdf->dot->x_dir = 1;
	fdf->dot->y_dir = 1;
	if (a[i].x > b[i].x)
		fdf->dot->x_dir = -1;
	if (a[i].y > b[i].y)
		fdf->dot->y_dir = -1;
	fdf->dot->dx = ft_absolute(b[i].x - a[i].x);
	fdf->dot->dy = ft_absolute(b[i].y - a[i].y);
	if (fdf->dot->dx > fdf->dot->dy)
		fdf->dot->steps = fdf->dot->dx;
	else
		fdf->dot->steps = fdf->dot->dy;
	fdf->dot->x_inc = fdf->dot->dx / fdf->dot->steps;
	fdf->dot->y_inc = fdf->dot->dy / fdf->dot->steps;
}

void	hook_collection(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, key_event, fdf);
}

void	iso(t_fdf *fdf)
{
	int	i;
	int	x0;
	int	y0;
	int	z0;

	i = 0;
	z0 = 0;
	while (i < fdf->nb_dots)
	{
		x0 = fdf->dot[i].x;
		y0 = fdf->dot[i].y;
		z0 = fdf->dot[i].z;
		if (z0 != 0)
			z0 += fdf->alt * z0;
		fdf->dot[i].x = fdf->x_offset + (x0 - y0) * cos(0.23599);
		fdf->dot[i].y = fdf->y_offset - z0 + (x0 + y0) * sin(8.623599);
		i++;
	}
}

void	my_mlx_bg_color(t_fdf *fdf)
{
	int		i;
	int		color;
	char	*dst;

	color = WHITE;
	i = 0;
	while (i < (fdf->width * fdf->height))
	{
		if (i % 2 == 0)
			color = 0x6F8FAF;
		else
			color = 0x9FE2BF;
		dst = fdf->addr + (i * (fdf->bpp / 8));
		*(unsigned int *)dst = color + 1;
		i++;
	}
}

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < fdf->width && y >= 0 && y < fdf->height)
	{
		dst = fdf->addr + (y * fdf->w_len + x * (fdf->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
