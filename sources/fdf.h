/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:35:30 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/22 21:25:02 by tshimoda         ###   ########.fr       */
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
	int		x_dir;
	int		y_dir;
	double	x_inc;
	double	y_inc;
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
	t_dot	*dot_bu;
}   t_fdf;


void	init_fdf(char *title, t_fdf *fdf);
void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
void	my_mlx_bg_color(t_fdf *fdf);
int		check_command_line(int ac, char **av);
int		ft_is_valid_file(char *av);
void	connect_dots(t_fdf *fdf);

void	get_nb_col(char *av, t_fdf *fdf);
void	get_nb_row(char *av, t_fdf *fdf);
void	parse_map(char *av, t_fdf *fdf);

int key_arrow_move(int keycode, t_fdf *fdf);
int key_event(int keycode, t_fdf *fdf);
void hook_collection(t_fdf *fdf);

void	set_missing_dot_pos(int i, t_fdf *fdf);
void	set_dot_position(char **elements, t_fdf *fdf);

void	back_up_dots(t_fdf *fdf);

void    get_dda_slope(t_fdf *fdf, t_dot *a, t_dot *b);
#endif