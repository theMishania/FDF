/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <cocummin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 10:39:42 by cocummin          #+#    #+#             */
/*   Updated: 2019/01/09 18:58:11 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "map_drawing.h"

void    map_drawing(void *mlx_ptr, void *win_ptr, t_map *map_struct, t_transform *transform)
{
    int i;
    int j;
    t_point main_point;
    t_point right_point;
    t_point down_point;

    i = 0;
    while (i < map_struct->n)
    {
        j = 0;
        while (j < map_struct->m)
        {
            main_point = t_point_init(j, i, map_struct, *transform);
            if (j != map_struct->m - 1)
            {
                right_point = t_point_init(j + 1, i, map_struct, *transform);
                line_drawing(mlx_ptr, win_ptr, main_point, right_point);
            }
            if (i != map_struct->n - 1)
            {
                down_point = t_point_init(j, i + 1, map_struct, *transform);
                line_drawing(mlx_ptr, win_ptr, main_point, down_point);
            }
            j++;
        }
        i++;        
    }
}

void    get_point_color(int alt, t_point *point, t_map *map_struct)
{
    if (map_struct->min_alt == map_struct->max_alt)
        point->alt_255 = 0;
    else
        point->alt_255 = -((map_struct->min_alt * 255)
            + alt * (-255))/(map_struct->max_alt - map_struct->min_alt);
}

t_point t_point_init(int x, int y, t_map *map_struct, t_transform transform)
{
    t_point point;
    int x3;
    int y3;
    int z;
    int z3;

    if (transform.color_on)
        get_point_color(map_struct->map[y][x], &point, map_struct);
    else
        point.alt_255 = 0;
    z = transform.scale * map_struct->map[y][x] - transform.scale * (map_struct->max_alt - map_struct->min_alt) / 2;
    y = transform.scale * y -  transform.scale * (map_struct->n - 1) / 2;
    x = transform.scale *  x -  transform.scale * (map_struct->m -1) / 2;
    
 
        x3 = (x*cos(transform.alpha)*cos(transform.beta) + 
            y*cos(transform.alpha)*sin(transform.beta)*sin(transform.gamma) - 
            y*sin(transform.alpha)*cos(transform.gamma) +
            z*cos(transform.alpha)*sin(transform.beta)*cos(transform.gamma) + 
            z*sin(transform.alpha)*sin(transform.gamma));
        y3 = (x*sin(transform.alpha)*cos(transform.beta) + 
            y*sin(transform.alpha)*sin(transform.beta)*sin(transform.gamma) + 
            y*cos(transform.alpha)*cos(transform.gamma) +
            z*sin(transform.alpha)*sin(transform.beta)*cos(transform.gamma) - 
            z*cos(transform.alpha)*sin(transform.gamma));
    if (transform.proj_type == 1)
    {
        z3 =(-x*sin(transform.beta) + y* cos(transform.beta)
            * sin (transform.gamma) + z* cos(transform.beta) * cos(transform.gamma));
        x3 = (int)((double)x3 * (double)(1000.0/(1000 - z3)));
        y3 = (int)((double)y3 * (double)(1000.0/(1000 - z3)));
    }
    point.x = x3 + transform.delta_x;
    point.y = y3 + transform.delta_y;
    return (point);
}

void    line_drow_x(void *mlx_ptr, void *win_ptr, t_point f, t_point s)
{
    int     tmp_x;
    int     tmp_y;
    int     i;
    double  step;
    int     a;
    int     b;
    int     c;
    int     color;

    a = f.y - s.y;
    b = s.x - f.x;
    c = f.x * s.y - s.x * f.y;
    tmp_x = f.x;
    tmp_y = f.y;
    i = 0;
    if (f.x - s.x == 0)
        step = 255.0;
    else
        step = (double)(s.alt_255 - f.alt_255)/(ABS((s.x - f.x)));
    while (tmp_x != s.x)
    {
        tmp_y = (-a * tmp_x - c) / b;
        mlx_pixel_put(mlx_ptr, win_ptr, tmp_x, tmp_y, (f.alt_255 + (int)(step * i)) * 0x010000 + (255 - f.alt_255 - (int)(step * i)) * 0x000100);
        tmp_x += f.x <= s.x ? 1 : -1;
        i++;
    }
}

void    line_drow_y(void *mlx_ptr, void *win_ptr, t_point f, t_point s)
{
    int     tmp_x;
    int     tmp_y;
    int     i;
    double  step;
    int     a;
    int     b;
    int     c;

    a = f.y - s.y;
    b = s.x - f.x;
    c = f.x * s.y - s.x * f.y;
    tmp_x = f.x;
    tmp_y = f.y;
    i = 0;
    if (f.y - s.y == 0)
        step = 255.0;
    else
        step = (double)(s.alt_255 - f.alt_255)/(ABS((s.y - f.y)));
    while (tmp_y != s.y)
    {
        tmp_x = (-b * tmp_y - c) / a;
        mlx_pixel_put(mlx_ptr, win_ptr, tmp_x, tmp_y, (f.alt_255 + (int)(step * i)) * 0x010000 + (255 - f.alt_255 - (int)(step * i)) * 0x000100);
        tmp_y += f.y <= s.y ? 1 : -1;
        i++;
    }
}

void    line_drawing(void *mlx_ptr, void *win_ptr, t_point f, t_point s)
{
    if ((ABS(f.x - s.x)) >= (ABS(f.y - s.y)))
        line_drow_x(mlx_ptr, win_ptr, f, s);
    else
        line_drow_y(mlx_ptr, win_ptr, f, s);
}


static int  escape_pressed(int key_code)
{
    if (key_code == 53)
        exit(-2);
    return (0);
}