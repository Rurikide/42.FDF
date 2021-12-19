/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 08:41:14 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/03 15:55:00 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static void iso(int *x, int *y, int z)
// {
//     int previous_x;
//     int previous_y;

//     previous_x = *x;
//     previous_y = *y;
//     *x = (previous_x - previous_y) * cos(0.523599);
//     *y = -z + (previous_x + previous_y) * sin(0.523599);
// }

// t_dot project(t_dot p, t_fdf *fdf)
// {
//     if (fdf->camera->projection == ISO)
//         iso(&p.x, &p.y, p.z);
// }

int key_hook(int keycode, t_fdf *fdf)
{
	(void)fdf;
	printf("The keycode is %d\n", keycode);
	if (keycode == 53 || keycode == 12 )
		exit(0);
	return (0);
}

void get_nb_col(char *av, t_fdf *fdf)
{
	int		i;
	int		fd;
	char	*line;
	int		switch_is_nb;
	
	i = 0;
	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	fdf->column = 0;
	switch_is_nb = 0;
	while (line[i])
	{
		if (switch_is_nb == 0 && line[i] != 32 && ft_isprint(line[i]))
		{
			switch_is_nb = 1;
			fdf->column++;
		}
		else if (switch_is_nb == 1 && line[i] == 32)
			switch_is_nb = 0;
		i++;
	}
	free(line);
	close(fd);
}

void get_nb_row(char *av, t_fdf *fdf)
{
	int		fd;
	char	*line;

	fdf->row = 0;
	fd = open(av, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		fdf->row++;
		free(line);
	}
	close(fd);
}

void	set_dot_position(char **elements, t_fdf *fdf)
{
	static int i;
	int pos;

	pos = 0;
	while (*elements && **elements != '\n')
	{
		fdf->dot[i].dcol = i % fdf->column; 
		fdf->dot[i].drow = i / fdf->column; 	
		fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
		fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
		fdf->dot[i].z = ft_atoi(*elements);

		if (fdf->dot[i].z == 0)
			fdf->dot[i].color = 0x00FFFFFF;
		else
			fdf->dot[i].color = 0x00FF0000;
		
		fdf->dot[i].missing = 0;

		i++;
		pos++;
		elements++;
	}
	if (pos < (fdf->column))
		{
			fdf->dot[i].missing = 1;
			fdf->dot[i].dcol = i % fdf->column; 
			fdf->dot[i].drow = i / fdf->column; 	
			fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
			fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
			fdf->dot[i].z = 0;
			i++;
		}
}

void	parse_map(char *av, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	**elements;

	get_nb_col(av, fdf);
	get_nb_row(av, fdf);

	fdf->nb_dots = (fdf->column * fdf->row);
	fdf->dot = (t_dot *)ft_calloc(fdf->nb_dots, sizeof(t_dot));
	fd = open(av, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		elements = ft_split(line, ' ');
		set_dot_position(elements, fdf);
		// free(elements);
		free(line);
	}
	close(fd);
} 

void	init_fdf(char *title, t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->width = 1280;
	fdf->height = 720;
	fdf->x_offset = 1;
	fdf->y_offset = 25;
	fdf->scale = 1;
	fdf->line_len = 10;
	fdf->title = title;
	fdf->win = mlx_new_window(fdf->mlx, fdf->width, fdf->height, "Fils de fer");
}

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;
	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void dda_line_algorithm(t_fdf *fdf)
{
	fdf->dot->dx = fdf->dot[1].x - fdf->dot[0].x;
	fdf->dot->dy = fdf->dot[fdf->column].y - fdf->dot[0].y;

	if (ft_absolute(fdf->dot->dx) > ft_absolute(fdf->dot->dy))
		fdf->dot->steps = fdf->dot->dx;
	else
		fdf->dot->steps = fdf->dot->dy;
	
	fdf->dot->x_increment = fdf->dot->dx / (float) fdf->dot->steps;
	fdf->dot->y_increment = fdf->dot->dy / (float) fdf->dot->steps;
}

void	connect_dots(t_fdf *fdf)
{
	int i = 0;

	dda_line_algorithm(fdf);
	while (i < fdf->nb_dots)
	{
		int x_temp = fdf->dot[i].x;
		int y_temp = fdf->dot[i].y;
		// ligne de gauche à droite
		while (fdf->dot[i + 1].missing == 0 && x_temp <= fdf->dot[i + 1].x)
		{
			if (x_temp < fdf->width && fdf->dot[i].y < fdf->height)
				my_mlx_pixel_put(fdf, x_temp, fdf->dot[i].y, fdf->dot[i].color);
			x_temp += fdf->dot->x_increment;
		}
		// ligne de haut en bas
		while ((i + fdf->column < fdf->nb_dots) && (fdf->dot[i].missing == 0 && fdf->dot[i + fdf->column].missing == 0) && y_temp <= fdf->dot[i + fdf->column].y)
		{
			if (x_temp < fdf->width && fdf->dot[i].y < fdf->height)
				my_mlx_pixel_put(fdf, fdf->dot[i].x, y_temp, fdf->dot[i].color);
			y_temp += fdf->dot->y_increment;
			// ft_printf("i + col = %d\n", (i + fdf->column));
			// ft_printf("nb of dots = %d\n", fdf->nb_dots);
		}
		i++;
	}
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

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	check_command_line(ac, av);

	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	init_fdf(av[1], fdf);
	parse_map(av[1], fdf);

	fdf->img = mlx_new_image(fdf->mlx, fdf->width, fdf->height);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);

	connect_dots(fdf);

	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);

	mlx_string_put(fdf->mlx, fdf->win, 0, 0, 0xFFFFFF, fdf->title);

	mlx_key_hook(fdf->win, key_hook, fdf);

	mlx_loop(fdf->mlx);

	return (0);
}