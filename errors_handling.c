/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:06:28 by chorange          #+#    #+#             */
/*   Updated: 2019/02/21 19:07:26 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	malloc_error(void)
{
	ft_putendl("Malloc error.");
	exit(-2);
}

void	open_errors(char *file_name)
{
	ft_putstr(file_name);
	if (errno == EISDIR)
	{
		ft_putendl(":\tIt is a directory.");
		exit(-2);
	}
	else if (errno == EACCES)
	{
		ft_putendl(":\tPermission denied");
		exit(-2);
	}
	else if (errno == ENOENT)
	{
		ft_putendl(":\tNo such file or directory");
		exit(-2);
	}
}

void	read_errors(void)
{
	ft_putendl("Wrong file.");
	exit(-2);
}

void	argc_count_errors(int argc)
{
	if (argc < 2)
	{
		ft_putendl("No argument, please, choose file.");
		exit(-2);
	}
	else if (argc > 2)
	{
		ft_putendl("Too much arguments, please, choose only one file.");
		exit(-2);
	}
}
