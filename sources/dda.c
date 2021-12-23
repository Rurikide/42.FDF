/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 10:26:07 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/22 22:36:34 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    get_dda_slope(t_fdf *fdf, t_dot *a, t_dot *b)
{
    int i;

    i = 0;
    fdf->dot->x_dir = 1;
    fdf->dot->y_dir = 1;

    if (a[i].x > b[i].x)
		  fdf->dot->x_dir = -1;
        
    if (a[i].y > b[i].y)
		  fdf->dot->y_dir = -1;
  // printf("coord of a is (%d;%d)\n", a[i].x, a[i].y); 
  // printf("coord of b is (%d;%d)\n", b[i].x, b[i].y);

  fdf->dot->dx = ft_absolute(b[i].x - a[i].x);
	fdf->dot->dy = ft_absolute(b[i].y - a[i].y);

  // printf("dx is %f and dy is %f\n", fdf->dot->dx, fdf->dot->dy); 

  if (fdf->dot->dx > fdf->dot->dy)
		fdf->dot->steps = fdf->dot->dx;
	else
		fdf->dot->steps = fdf->dot->dy;
	
	fdf->dot->x_inc = fdf->dot->dx / fdf->dot->steps;
	fdf->dot->y_inc = fdf->dot->dy / fdf->dot->steps;
}
