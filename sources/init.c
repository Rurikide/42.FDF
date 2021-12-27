/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:38:35 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/23 14:54:22 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_fdf(char *title, t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->width = 1280;
	fdf->height = 720;
	fdf->x_offset = 0;
	fdf->y_offset = 0;
	fdf->alt = 0;
	fdf->scale = 1;
	fdf->line_len = 20;
	fdf->title = title;
	fdf->img = mlx_new_image(fdf->mlx, fdf->width, fdf->height);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);	
	fdf->win = mlx_new_window(fdf->mlx, fdf->width, fdf->height, "Fils de fer");
}

int	ft_is_valid_file(char *av)
{
	int len;
	int v_len = 3;
	char *valid = ".fdf";
	
	len = ft_strlen(av) - 1;
	while (valid[v_len])
	{
		if (valid[v_len] != av[len])
			return (0);
		v_len--;
		len--;
	}
	return (1);
}

int	check_command_line(int ac, char **av)
{
	if (ac < 2)
	{
		ft_printf("\033[1;31m Please select a test map .fdf\033[0;39m\n");
		exit (0);
	}
	else if ((ac > 2))
	{
		ft_printf("Please select \033[1;31monly 1\033[0;39m test map .fdf\n");
		exit (0);
	}
	else if (ft_is_valid_file(av[1]) == 0)
	{
		ft_printf("Please select a \033[1;31m.fdf file\033[0;39m\n");
		exit (0);
	}
	return (0);
}
