/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:48:54 by tshimoda          #+#    #+#             */
/*   Updated: 2021/12/20 10:54:43 by tshimoda         ###   ########.fr       */
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