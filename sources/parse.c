/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:48:54 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/31 17:58:39 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_nb_col(char *av, t_fdf *fdf)
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

void	get_nb_row(char *av, t_fdf *fdf)
{
	int		fd;
	char	*line;

	fdf->row = 0;
	fd = open(av, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
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
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		elements = ft_split(line, ' ');
		set_dot_position(elements, fdf);
		ft_free_table(elements);
		free(line);
	}
	close(fd);
}

int	parse_color(char *elements)
{
	int	i;
	int	color;

	i = 0;
	while (elements[i])
	{
		if (elements[i] == ',')
		{
			if (elements[i + 1] == '0' && \
			(elements[i + 2] == 'x' || elements[i + 2] == 'X'))
			{
				color = hex_to_dec(&elements[i + 3]);
				return (color);
			}
		}
		i++;
	}
	if (ft_atoi(elements) == 0)
		color = BLACK;
	else
		color = WHITE;
	return (color);
}
