/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:41:14 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/29 14:58:09 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void iso(t_fdf *fdf)
{
    int x0;
    int y0;
	int i = 0;
	int z0 = 0;

	while (i < fdf->nb_dots)
    {
		x0 = fdf->dot[i].x;
		y0 = fdf->dot[i].y;
		z0 = fdf->dot[i].z;
		if (z0 != 0)
			z0 += fdf->alt * z0;
		fdf->dot[i].x = fdf->x_offset + (x0 - y0) * cos(0.23599);
		fdf->dot[i].y = fdf->y_offset - z0 + (x0 + y0) * sin(8.623599);

		// printf("dot #%d ::: iso coord (x;y) = (%d;%d)\n", i, fdf->dot[i].x, fdf->dot[i].y);
		i++;
	}
}

void	my_mlx_bg_color(t_fdf *fdf)
{
	char	*dst;
	int i;

	i = 0;

	while (i < (fdf->width * fdf->height))
	{
		int color =0xFFFFFF;
		if (i % 2 == 0)
			color = 0x6F8FAF;
		else
			color = 0x9FE2BF;
		dst = fdf->addr + (i * (fdf->bits_per_pixel / 8));
		*(unsigned int*)dst = color + 1;
		i++;
	}
}

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;
	
	// condition if to only put a dot within limits FDF Window
	if (x >= 0 && x < fdf->width && y >= 0 && y < fdf->height)
	{
		dst = fdf->addr + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	connect_dots(t_fdf *fdf)
{
	int i;
	double x;
	double y;

	i = 0;
	
	my_mlx_bg_color(fdf);

	// COMMENT OUT iso(fdf) to have parallel lines
	if (fdf->iso == 1)
		iso(fdf);

	// "HORIZONTAL" LINES WHILE LOOP when not in ISO projection
	while (i < fdf->nb_dots)
	{
		x = fdf->dot[i].x;
		y = fdf->dot[i].y;
		if (round(x) < fdf->dot[i + 1].x && fdf->dot[i + 1].missing == 0)
		{
			get_dda_slope(fdf, &fdf->dot[i], &fdf->dot[i + 1]);
			while (fdf->dot->steps-- > 0)
			{
					my_mlx_pixel_put(fdf, round(x), round(y), fdf->dot[i].color);
					x += (fdf->dot->x_dir * fdf->dot->x_inc);
					y += (fdf->dot->y_dir * fdf->dot->y_inc);
			}
		}

		// "VERTICAL" LINES  WHILE LOOP when not in ISO projection
		x = fdf->dot[i].x;
		y = fdf->dot[i].y;
		if ((i + fdf->column < fdf->nb_dots) && (fdf->dot[i].missing == 0 && fdf->dot[i + fdf->column].missing == 0))
		{
			get_dda_slope(fdf, &fdf->dot[i], &fdf->dot[i + fdf->column]);
			while (fdf->dot->steps-- > 0)
			{
					my_mlx_pixel_put(fdf, round(x), round(y), fdf->dot[i].color);
					x += (fdf->dot->x_dir * fdf->dot->x_inc);
					y += (fdf->dot->y_dir * fdf->dot->y_inc);
			}
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

// int zoom(int keycode, t_fdf *fdf)
// {
// 	if (keycode == 1)
// 		fdf->scale *= 1.2;
// 	if (keycode == 2)
// 		fdf->scale /= 1.2;
// }

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