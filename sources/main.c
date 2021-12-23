/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:41:14 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/22 20:57:58 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void iso(t_fdf *fdf)
{
    int x0;
    int y0;
	int i = 0;
	while (i < fdf->nb_dots)
    {
		x0 = fdf->dot[i].x;
		y0 = fdf->dot[i].y;
		fdf->dot[i].x = fdf->x_offset + (x0 - y0) * cos(0.523599);
		fdf->dot[i].y = fdf->y_offset + fdf->dot[i].z + (x0 + y0) * sin(0.523599);

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

	iso(fdf);
	
	while (i < fdf->nb_dots)
	{
		x = fdf->dot[i].x;
		y = fdf->dot[i].y;
		
		// coordonnées des points : 
		// printf("dot #%d ::: iso coord (x;y) = (%d;%d)\n", i, fdf->dot[i].x, fdf->dot[i].y);
		
		// LOOP pour relier les dots "sur la même : row dot[i].x"
		while (x < fdf->dot[i + 1].x && fdf->dot[i + 1].missing == 0)
		{
			get_dda_slope(fdf, &fdf->dot[i], &fdf->dot[i + 1]);
			while (fdf->dot->steps-- > 0)
			{
				// if (x >= 0 && x <= fdf->width && fdf->dot[i].y <= fdf->height)
				// {
					my_mlx_pixel_put(fdf, round(x), round(y), fdf->dot[i].color);
					x += (fdf->dot->x_dir * fdf->dot->x_inc);
					y += (fdf->dot->y_dir * fdf->dot->y_inc);
				// }
				// printf("x value = %d & y value = %d\n", x, y);
			}
		}

		// x = fdf->dot[i].x;
		// y = fdf->dot[i].y;
		
		// // // // LOOP pour relier les dots "sur la même : colonne dot[i].y"
		// while ((i + fdf->column < fdf->nb_dots) && y < fdf->dot[i + fdf->column].y && (fdf->dot[i].missing == 0 && fdf->dot[i + fdf->column].missing == 0))
		// {
		// 	get_dda_slope(fdf, &fdf->dot[i + fdf->column], &fdf->dot[i + fdf->column]);
		// 	while (fdf->dot->steps-- > 0)
		// 	{
		// 		// if (fdf->dot[i].x >= 0 && fdf->dot[i].x <= fdf->width && y >= 0 && fdf->dot[i].y <= fdf->height)
		// 		// {
		// 			my_mlx_pixel_put(fdf, round(x), round(y), fdf->dot[i].color);
		// 			x += (fdf->dot->x_dir * fdf->dot->x_inc);
		// 			y += (fdf->dot->y_dir * fdf->dot->y_inc);
		// 		// }
		// 		// printf("x value = %d & y value = %d\n", x, y);
		// 	}
		// }
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}



	// OLD VERSION BELOW
	// iso(fdf);
	// get_dda_slope(fdf, &fdf->dot[i], &fdf->dot[i + 1]);
// 	fdf->dot->dx = ft_absolute(fdf->dot[1].x - fdf->dot[0].x);
// 	fdf->dot->dy = ft_absolute(fdf->dot[fdf->column].y - fdf->dot[0].y);

// 	if (fdf->dot->dx > fdf->dot->dy)
// 		fdf->dot->steps = fdf->dot->dx;
// 	else
// 		fdf->dot->steps = fdf->dot->dy;
	
// 	fdf->dot->x_inc = fdf->dot->dx / (float) fdf->dot->steps;
// 	fdf->dot->y_inc = fdf->dot->dy / (float) fdf->dot->steps;

// 	// TRYING ISO, doesnt work
// 	// int z = 0;
// 	// while (z < fdf->nb_dots)
// 	// {
// 	// 	iso(&fdf->dot[z].x, &fdf->dot[z].y, fdf->dot[z].z);
// 	// 	z++;
// 	// }
	
// 	while (i < fdf->nb_dots)
// 	{
// 		int x_temp = fdf->dot[i].x;
// 		int y_temp = fdf->dot[i].y;

// 		// dessine de gauche à droite
// 		while (x_temp < fdf->dot[i + 1].x && fdf->dot[i + 1].missing == 0)
// 		{
// 			if (x_temp >= 0 && x_temp <= fdf->width && fdf->dot[i].y <= fdf->height)
// 				my_mlx_pixel_put(fdf, x_temp, fdf->dot[i].y, fdf->dot[i].color);
// 			x_temp += round(fdf->dot->x_inc);
// 		}
// 		// dessine de haut en bas
// 		while ((i + fdf->column < fdf->nb_dots) && y_temp <= fdf->dot[i + fdf->column].y && (fdf->dot[i].missing == 0 && fdf->dot[i + fdf->column].missing == 0))
// 		{
// 			if (fdf->dot[i].x >= 0 && fdf->dot[i].x <= fdf->width && y_temp >= 0 && fdf->dot[i].y <= fdf->height)
// 				my_mlx_pixel_put(fdf, fdf->dot[i].x, y_temp, fdf->dot[i].color);
// 			y_temp += round(fdf->dot->y_inc);
// 			// ft_printf("i + col = %d\n", (i + fdf->column));
// 			// ft_printf("nb of dots = %d\n", fdf->nb_dots);
// 		}
// 		i++;
// 	}
// 	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
// }

// int zoom(int keycode, t_fdf *fdf)
// {
// 	if (keycode == ZOOM_IN)
// 		fdf->scale *= 1.2;
// 	if (keycode == ZOOM_OUT)
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