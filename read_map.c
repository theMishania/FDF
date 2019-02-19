/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 19:44:52 by chorange          #+#    #+#             */
/*   Updated: 2019/01/04 19:44:52 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "string.h"
#include <fcntl.h>
#include <stdio.h>
#include "map_drawing.h"
#include "libft/libft.h"

int line_check(char *line)
{
	static int	x_size = 0;
	int			curr_x_size;
	
	curr_x_size = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if ((*line && !ft_isdigit(*line) && *line != '-') || (!ft_isdigit(*line) && !curr_x_size))
			read_errors();
		if (*line == '-')
			line++;
		while (ft_isdigit(*line))
			line++;
		if (*line && (*line != ' ') && *line != ',')
			read_errors();
		while (*line == ' ')
			line++;
		if (*line == ',')
		{
			line++;
			while (ft_isdigit(*line) || *line == 'x' || *line == 'X' || (*line >= 'A' && *line <= 'F') || (*line >= 'a' && *line <= 'f'))
				line++;
		}
		curr_x_size++;
	}
	if (!x_size)
		x_size = curr_x_size;
	else
		if (x_size != curr_x_size)
			read_errors();
	return (x_size);
}

int		get_strings_count(char *name)
{
	int		count;
	int		fd;
	char	*line;

	count = 0;	
	fd = open(name, O_RDWR);
	if (fd < 0)
		open_errors(name);
	while (get_next_line(fd, &line))
	{
		if (*line)
			count++;
		free (line);
	}
	close (fd);
	return (count);
}

void	map_set(t_map *map_struct, char *line, int i)
{
	int j;
	
	j = 0;	
	CHECK((map_struct->map[i] = (int *)malloc(sizeof(int) * map_struct->m)));
	while (*line)
	{
		while (*line == ' ')
			line++;
		map_struct->map[i][j] = ft_atoi(line);
		while (ft_isdigit(*line) || *line == '-')
			line++;
		while (*line == ' ')
			line++;
		if (*line == ',')
		{
			line++;
			while (ft_isdigit(*line) || *line == 'x' || *line == 'X' || (*line >= 'A' && *line <= 'F') || (*line >= 'a' && *line <= 'f'))
				line++;
		}
		j++;		
	}
}

void	read_map(char *file_name, t_map *map_struct)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	if (!(map_struct->n = get_strings_count(file_name)))
		read_errors();
	CHECK((map_struct->map = (int **)malloc(sizeof(int *) * (map_struct->n))));
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		map_struct->m = line_check(line);
		map_set(map_struct, line, i);
		free(line);
		i++;
	}
	if (!(map_struct->m > 1 || map_struct->m > 1))
	{
		free_all(map_struct);
		read_errors();
	}
	close (fd);
}

void	free_all(t_map *map_struct)
{
	int i;

	i = 0;
	if (map_struct->map)
	{
		while (i < map_struct->n)
		{
			if (map_struct->map[i])
				free(map_struct->map[i]);
			i++;
		}
		free(map_struct->map);
	}
}
