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
	int		switch_is_nombre;
	
	i = 0;
	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
// split
// colum = sozeof split table
// free split;
	fdf->column = 0;
//	fdf->column = ft_wordcount(line, 32);
	switch_is_nombre = 0;
	while (line[i])
	{
		if (switch_is_nombre == 0 && line[i] != 32 && ft_isprint(line[i]))
		{
			switch_is_nombre = 1;
			fdf->column++;
		}
		else if (switch_is_nombre == 1 && line[i] == 32)
			switch_is_nombre = 0;
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
	while ((line = get_next_line(fd)) > 0)
	{
		fdf->row++;
		free(line);
	}
	close(fd);
}

void	set_dot_position(char **elements, t_fdf *fdf)
{
	static int i;

	// while (*elements && **elements != '\n')
	while (*elements)
	{
		if (i < fdf->column && *elements == NULL)
		{
			fdf->dot[i].missing = 1;
			// fdf->dot[i].dcol = i % fdf->column; 
			// fdf->dot[i].drow = i / fdf->column; 	
			// fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
			// fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
			// fdf->dot[i].z = 0;
			i++;
			return ;
		}
		fdf->dot[i].dcol = i % fdf->column; 
		fdf->dot[i].drow = i / fdf->column; 	
		fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
		fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
		fdf->dot[i].z = ft_atoi(*elements);
		fdf->dot[i].missing = 0;
		i++;
		elements++;
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
	while ((line = get_next_line(fd)) > 0)
	{
		elements = ft_split(line, ' ');
		set_dot_position(elements, fdf);
		// free(elements);
		free(line);
	}
	close(fd);
} 

void	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->width = 1200;
	fdf->height = 780;
	fdf->x_offset = 10;
	fdf->y_offset = 10;
	fdf->scale = 1;
	fdf->line_len = 10;
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



int	main(int ac, char **av)
{
	int i = 0;
	int color = 0x00FFFFFF;

	t_fdf	*fdf;
	
	if (ac < 2)
	{
		printf("\033[1;31m Please select a test map .fdf\033[0;39m\n");
		return (0);
	}
	else if ((ac > 2))
	{
		printf("Please select \033[1;31monly 1\033[0;39m test map .fdf\n");
		return (0);
	}
	else if (ft_is_valid_file(av[1]) == 0)
	{
		printf("Please select a \033[1;31m.fdf file\033[0;39m\n");
		return (0);
	}
	
	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	init_fdf(fdf);
	parse_map(av[1], fdf);

	fdf->img = mlx_new_image(fdf->mlx, fdf->width, fdf->height);
	
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);

	fdf->dot->dx = fdf->dot[1].x - fdf->dot[0].x;
	fdf->dot->dy = fdf->dot[fdf->column].y - fdf->dot[0].y;

	if (ft_absolute(fdf->dot->dx) > ft_absolute(fdf->dot->dy))
		fdf->dot->steps = fdf->dot->dx;
	else
		fdf->dot->steps = fdf->dot->dy;
	
	fdf->dot->x_increment = fdf->dot->dx / (float) fdf->dot->steps;
	fdf->dot->y_increment = fdf->dot->dy / (float) fdf->dot->steps;

	//int j = 0;
	// while (j < fdf->nb_dots)
	// {
	// 	ft_printf("(%d;", fdf->dot[j].x);
	// 	ft_printf("%d)", fdf->dot[j].y);
	// 	ft_printf(" Z value =.%d\n", fdf->dot[j].z);
	// 	j++;
	// }
	// ft_printf("number of columns : %d\n", fdf->column);
	// ft_printf("number of rows : %d\n", fdf->row);
	
	// DRAWING			
	while (i < fdf->nb_dots)
	{
		if (fdf->dot[i].z == 0)
			color = 0x00FFFFFF;
		else
			color = 0x00FF0000;

		int x_temp = fdf->dot[i].x;
		int y_temp = fdf->dot[i].y;
		
		while (fdf->dot[i + 1].missing == 0 && x_temp <= fdf->dot[i + 1].x)
		{
			if (x_temp < fdf->width && fdf->dot[i].y < fdf->height)
				my_mlx_pixel_put(fdf, x_temp, fdf->dot[i].y, color);
			x_temp += fdf->dot->x_increment;
		}
		while (fdf->dot[i + fdf->column].missing == 0 && y_temp <= fdf->dot[i + fdf->column].y)
		{
			if (x_temp < fdf->width && fdf->dot[i].y < fdf->height)
				my_mlx_pixel_put(fdf, fdf->dot[i].x, y_temp, color);
			y_temp += fdf->dot->y_increment;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);

	mlx_key_hook(fdf->win, key_hook, fdf);

	mlx_loop(fdf->mlx);

	return (0);
}