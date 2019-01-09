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

void	err_fdf(int err_type)
{
	printf("error\t");
	if (err_type == 2)
		puts("wrong sym");
	if (err_type == 3)
		puts("wrong count");
	exit(-2);
}

int line_check(char *line)
{
	static int	x_size = 0;
	int			curr_x_size;
	
	curr_x_size = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line && !isdigit(*line) && *line != '-')
			err_fdf(3);
		if (*line == '-')
			line++;
		while (isdigit(*line))
			line++;
		if (*line && (*line != ' ') && *line != ',')
			err_fdf(3);
		while (*line == ' ')
			line++;
		if (*line == ',')
		{
			line++;
			while (isdigit(*line) || *line == 'x' || *line == 'X' || (*line >= 'A' && *line <= 'F'))
				line++;
		}
		curr_x_size++;
	}
	if (!x_size)
		x_size = curr_x_size;
	else
		if (x_size != curr_x_size)
			err_fdf(2);
	return (x_size);
}

int		get_strings_count(char *name)
{
	int		count;
	int		fd;
	char	*line;
	
	//puts("begin get count");
	count = 0;	
	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		//puts("line");
		if (*line)
			count++;
		free (line);
	}
	close (fd);
	//puts("get count done");
	return (count);
}

void	map_set(t_map *map_struct, char *line, int i)
{
	int j;
	
	j = 0;	
	map_struct->map[i] = (int *)malloc(sizeof(int) * map_struct->m);////mallcheck
	while (*line)
	{
		while (*line == ' ')
			line++;
		map_struct->map[i][j] = atoi(line);
		//printf("%d\n", atoi(line));
		while (isdigit(*line) || *line == '-')
			line++;
		while (*line == ' ')
			line++;
		if (*line == ',')
		{
			line++;
			while (isdigit(*line) || *line == 'x' || *line == 'X' || (*line >= 'A' && *line <= 'F'))
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
	map_struct->n = get_strings_count(file_name);
	map_struct->map = (int **)malloc(sizeof(int *) * (map_struct->n));/////mallcheck
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		map_struct->m = line_check(line);
		map_set(map_struct, line, i);
		free (line);
		i++;
	}
	close (fd);
}
