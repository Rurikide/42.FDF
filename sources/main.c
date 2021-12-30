/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:41:14 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/29 22:31:03 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	connect_dots_loop(t_fdf *fdf, int i, double *x, double *y)
{
	while (fdf->dot->steps-- > 0)
	{
		my_mlx_pixel_put(fdf, round(*x), round(*y), fdf->dot[i].color);
		*x += (fdf->dot->x_dir * fdf->dot->x_inc);
		*y += (fdf->dot->y_dir * fdf->dot->y_inc);
	}
}

void	refresh_map(t_fdf *fdf)
{
	my_mlx_bg_color(fdf);
	if (fdf->iso == 1)
		iso(fdf);
}

void	connect_dots(t_fdf *fdf)
{
	int		i;
	double	x;
	double	y;

	i = -1;
	refresh_map(fdf);
	while (++i < fdf->nb_dots)
	{
		x = fdf->dot[i].x;
		y = fdf->dot[i].y;
		if (round(x) < fdf->dot[i + 1].x && fdf->dot[i + 1].missing == 0)
		{
			get_dda_slope(fdf, &fdf->dot[i], &fdf->dot[i + 1]);
			connect_dots_loop(fdf, i, &x, &y);
		}
		x = fdf->dot[i].x;
		y = fdf->dot[i].y;
		if ((i + fdf->column < fdf->nb_dots) && \
		(fdf->dot[i].missing == 0 && fdf->dot[i + fdf->column].missing == 0))
		{
			get_dda_slope(fdf, &fdf->dot[i], &fdf->dot[i + fdf->column]);
			connect_dots_loop(fdf, i, &x, &y);
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	check_command_line(ac, av);
	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	init_fdf(av[1], fdf);
	parse_map(av[1], fdf);
	connect_dots(fdf);
	hook_collection(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
