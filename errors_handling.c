/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 10:26:09 by cocummin          #+#    #+#             */
/*   Updated: 2019/02/19 20:22:34 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "map_drawing.h"
#include "libft/libft.h"

void    open_errors(char *file_name)
{
    if (errno == EISDIR)
    {
        ft_putstr(file_name);
        ft_putendl(":\tIt is a directory.");
        exit(-2);
    }
    else if (errno == EACCES)
    {
        ft_putstr(file_name);
        ft_putendl(":\tPermission denied");
        exit(-2);
    }
    else if (errno == ENOENT)
    {
        ft_putstr(file_name);
        ft_putendl(":\tNo such file or directory");
        exit(-2);
    }
}

void	read_errors(void)
{
	ft_putendl("Wrong file.");
	exit(-2);
}

void    argc_count_errors(int argc)
{
    if (argc < 2)
    {

        ft_putendl("No argument, please, choose file.");
        exit(-2);
    }else if (argc > 2)
    {
        ft_putendl("Too much arguments, please, choose only one file.");
        exit(-2);
    }
}

