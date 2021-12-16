/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:35:30 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/02 11:04:18 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	double	colour;
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
	t_dot	*dot;
}   t_fdf;
