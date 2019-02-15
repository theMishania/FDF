/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 10:26:09 by cocummin          #+#    #+#             */
/*   Updated: 2019/02/15 21:50:44 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "map_drawing.h"

void    open_errors(char *file_name)
{
    if (errno == EISDIR)
    {
        puts("It is a directory.");
        exit(-2);
    }
    else if (errno == EACCES)
    {
        puts("Permission denied");
        exit(-2);
    }
    else if (errno == ENOENT)
    {
        puts("No such file or directory");
        exit(-2);
    }
}

void    argc_count_errors(int argc)
{
    if (argc < 2)
    {

        puts("No argument, please, choose file.");
        exit(-2);
    }else if (argc > 2)
    {
        puts("Too much arguments, please, choose only one file.");
        exit(-2);
    }
}

