/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 10:39:42 by cocummin          #+#    #+#             */
/*   Updated: 2018/12/29 19:26:34 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "map_drawing.h"




void    map_drawing(void *mlx_ptr, void *win_ptr, int arr[5][5], t_transform *transform)
{
    int i;
    int j;
    t_point *main_point;
    t_point *right_point;
    t_point *down_point;

    i = 0;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            main_point = t_point_init(j, i,arr[i][j], *transform);
            if (j != 4)
            {
                right_point = t_point_init(j + 1, i,arr[i][j + 1], *transform);
                line_drawing(mlx_ptr, win_ptr, *main_point, *right_point);
            }
            if (i != 4)
            {
                down_point = t_point_init(j, i + 1, arr[i + 1][j], *transform);
                line_drawing(mlx_ptr, win_ptr, *main_point, *down_point);
            }
            j++;
        }
        i++;
    }
}


t_point *t_point_init(int x, int y, int z, t_transform transform)
{
    t_point *point;
    int x3;
    int y3;

    z = z - 1;
    y = y - 4 / 2;
    x = x - 4 / 2;

    point = (t_point*)malloc(sizeof(t_point));
    x3 = transform.scale *(x*cos(transform.alpha)*cos(transform.beta) + 
            y*cos(transform.alpha)*sin(transform.beta)*sin(transform.gamma) - 
            y*sin(transform.alpha)*cos(transform.gamma) +
			z*cos(transform.alpha)*sin(transform.beta)*cos(transform.gamma) + 
            z*sin(transform.alpha)*sin(transform.gamma));
	y3 = transform.scale * (x*sin(transform.alpha)*cos(transform.beta) + 
            y*sin(transform.alpha)*sin(transform.beta)*sin(transform.gamma) + 
            y*cos(transform.alpha)*cos(transform.gamma) +
			z*sin(transform.alpha)*sin(transform.beta)*cos(transform.gamma) - 
            z*cos(transform.alpha)*sin(transform.gamma));
    point->x = x3 + 500;
    point->y = y3 + 500;

    return (point);
}



void    line_drawing(void *mlx_ptr, void *win_ptr, t_point first, t_point second)
{
    int tmp_x;
    int tmp_y;
    int a;
    int b;
    int c;

    a = first.y - second.y;
    b = second.x - first.x;
    c = first.x * second.y - second.x * first.y;
    tmp_x = first.x;
    tmp_y = first.y;
    if ((ABS(first.x - second.x)) >= (ABS(first.y - second.y)))
    {
        while (tmp_x != second.x)
        {
            tmp_y = (-a * tmp_x - c) / b;
            mlx_pixel_put(mlx_ptr, win_ptr, tmp_x, tmp_y, 0xF5F904);
            tmp_x += first.x <= second.x ? 1 : -1;
        }
    }
    else
    {
        while (tmp_y != second.y)
        {
            tmp_x = (-b * tmp_y - c) / a;
            mlx_pixel_put(mlx_ptr, win_ptr, tmp_x, tmp_y, 0xF5F904);
            tmp_y += first.y <= second.y ? 1 : -1;
        }
    }
}


static int  escape_pressed(int key_code)
{
    if (key_code == 53)
        exit(-2);
    return (0);
}