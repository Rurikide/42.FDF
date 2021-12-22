/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:48:54 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/21 21:33:36 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		if (switch_is_nb == 0 && line[i] != ' ' && ft_isprint(line[i]))
		{
			switch_is_nb = 1;
			fdf->column++;
		}
		else if (switch_is_nb == 1 && line[i] == ' ')
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

void	set_missing_dot_pos(int i, t_fdf *fdf)
{
	fdf->dot[i].missing = 1;
	fdf->dot[i].dcol = i % fdf->column; 
	fdf->dot[i].drow = i / fdf->column; 	
	// fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
	// fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
	fdf->dot[i].x = (fdf->dot[i].dcol * fdf->line_len);
	fdf->dot[i].y = (fdf->dot[i].drow * fdf->line_len);
	fdf->dot[i].z = 0;
}

void	set_dot_position(char **elements, t_fdf *fdf)
{
	static int i;
	int pos;

	pos = 0;
	if (fdf->nb_dots > 900)
	{
		fdf->line_len = 10;
	}
	while (*elements && **elements != '\n')
	{
		fdf->dot[i].dcol = i % fdf->column; 
		fdf->dot[i].drow = i / fdf->column; 	
		// fdf->dot[i].x = fdf->x_offset + (fdf->dot[i].dcol * fdf->line_len);
		// fdf->dot[i].y = fdf->y_offset + (fdf->dot[i].drow * fdf->line_len);
		fdf->dot[i].x = (fdf->dot[i].dcol * fdf->line_len);
		fdf->dot[i].y = (fdf->dot[i].drow * fdf->line_len);
		fdf->dot[i].z = ft_atoi(*elements);

		if (fdf->dot[i].z == 0)
			fdf->dot[i].color = 0x00000000;
		else
			fdf->dot[i].color = 0x00FFFFFF;
		
		fdf->dot[i].missing = 0;

		i++;
		pos++;
		elements++;
	}
	if (pos < (fdf->column))
		{
			set_missing_dot_pos(i, fdf);
			i++;
		}
}