/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:30:49 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/29 22:49:38 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_change_projection(int keycode, t_fdf *fdf)
{
	int	i;

	i = 0;
	if (keycode == 34 && fdf->iso != 1)
	{
		fdf->iso = 1;
		fdf->x_offset = 0;
		fdf->y_offset = 0;
		fdf->alt = 0;
	}
	if (keycode == 35 && fdf->iso != 0)
	{
		fdf->iso = 0;
		fdf->x_offset = 0;
		fdf->y_offset = 0;
		fdf->alt = 0;
	}
	while (i < fdf->nb_dots)
	{
		fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
		fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
		i++;
	}
	connect_dots(fdf);
	return (0);
}

void	key_arrow_value(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_UP)
	{
		fdf->y_offset -= 10;
		if (fdf->iso == 1)
			fdf->x_offset -= 5;
	}
	if (keycode == KEY_DOWN)
	{
		fdf->y_offset += 10;
		if (fdf->iso == 1)
			fdf->x_offset += 5;
	}
	if (keycode == KEY_LEFT)
	{
		fdf->x_offset -= 10;
		if (fdf->iso == 1)
			fdf->y_offset += 4;
	}
	if (keycode == KEY_RIGHT)
	{
		fdf->x_offset += 10;
		if (fdf->iso == 1)
			fdf->y_offset -= 4;
	}	
}

int	key_arrow_move(int keycode, t_fdf *fdf)
{
	int	i;

	i = 0;
	key_arrow_value(keycode, fdf);
	while (i < fdf->nb_dots)
	{
		fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
		fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
		i++;
	}
	connect_dots(fdf);
	return (0);
}

int	key_transform_map(int keycode, t_fdf *fdf)
{
	int	i;

	i = 0;
	if (keycode == KEY_HIGH)
		fdf->alt += 1;
	if (keycode == KEY_LOW)
		fdf->alt -= 1;
	if (keycode == KEY_ZOOM_IN)
		fdf->line_len += 1;
	if (keycode == KEY_ZOOM_OUT)
	{
		if (fdf->line_len - 1 > 0)
			fdf->line_len -= 1;
	}
	while (i < fdf->nb_dots)
	{
		fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
		fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
		i++;
	}
	connect_dots(fdf);
	return (0);
}

int	key_event(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		free(fdf->dot);
		free(fdf);
		mlx_destroy_image(fdf->mlx, fdf->img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		exit(0);
	}
	if (keycode == KEY_I || keycode == KEY_P)
		key_change_projection(keycode, fdf);
	else if (keycode == KEY_UP || keycode == KEY_DOWN || \
	keycode == KEY_LEFT || keycode == KEY_RIGHT)
		key_arrow_move(keycode, fdf);
	else if (keycode == KEY_HIGH || keycode == KEY_LOW || \
	keycode == KEY_ZOOM_IN || keycode == KEY_ZOOM_OUT)
		key_transform_map(keycode, fdf);
	return (0);
}
