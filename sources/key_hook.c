/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:30:49 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/22 16:09:39 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int key_arrow_move(int keycode, t_fdf *fdf)
{
	int i;

	i = 0;
	(void)fdf;
	if (keycode == KEY_UP)
		fdf->y_offset -= 10;
	if (keycode == KEY_DOWN)
		fdf->y_offset += 10;
	if (keycode == KEY_LEFT)
		fdf->x_offset -= 10;
	if (keycode == KEY_RIGHT)
		fdf->x_offset += 10;
	while (i < fdf->nb_dots)
	{
		fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
		fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
		i++;
	}
	connect_dots(fdf);
	return (0);
}

int key_event(int keycode, t_fdf *fdf)
{
	(void)fdf;
	if (keycode == KEY_ESC || keycode == KEY_Q)
		exit(0);
	// else if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT || keycode == KEY_RIGHT)
	// {
	// 	my_mlx_bg_color(fdf);
	// 	key_arrow_move(keycode, fdf);
	// }
	// else if (keycode == ZOOM_IN || keycode == ZOOM_OUT)
	// {
	// 	my_mlx_pixel_clear(fdf);
	// 	zoom(keycode, fdf);
	// 	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	// 	ft_printf("pressing the key: %d\n", keycode);
	// }
	return (0);
}

void hook_collection(t_fdf *fdf)
{
	// mlx_key_hook(fdf->win, key_hook, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, key_event, fdf);
}