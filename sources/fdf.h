/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:35:30 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/20 10:55:15 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../libft/libsources/libft.h"
#include "../libft/libsources/ft_printf.h"
#include "../libft/libsources/get_next_line.h"
#include "../minilibx_macos/mlx.h"

# define KEY_ESC 53
# define KEY_Q 12
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ZOOM_OUT 27
# define KEY_ZOOM_IN 24
# define KEY_ALTITUDE_DEC 43
# define KEY_ALTITUDE_INC 47
# define BIRDS_EYE_VIEW 11
# define ISOMETRIC_PROJ 34
# define TRANSVERSAL_CUT 17

# define BLACK 0x00000000
# define WHITE 0x00FFFFFF

typedef struct s_dot
{
	int		x;
	int		y;
	int		z;
	double	dx;
	double	dy;
	double	steps;
	int		dcol;
	int		drow;
	int		missing;
	float	x_increment;
	float	y_increment;
	double	color;
}   t_dot;

typedef struct s_fdf
{
	void 	*mlx;
	void 	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		width;
	int		height;
	float	scale;
	int		line_len;
	int		line_length;
	int		endian;
	int		column;
	int		row;
	int 	nb_dots;
	int		nb_cols;
	int		x_offset;
	int		y_offset;
	char	*title;
	t_dot	*dot;
}   t_fdf;

void get_nb_col(char *av, t_fdf *fdf);
void get_nb_row(char *av, t_fdf *fdf);
#endif