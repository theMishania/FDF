/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 10:39:42 by cocummin          #+#    #+#             */
/*   Updated: 2019/02/12 23:13:30 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "map_drawing.h"
#define IMAGE_WIDTH 1000
#define IMAGE_HEIGHT 1000
#define SIZE_LEN 1000

void    put_point_to_image(char *image_data, int x, int y, int color)
{
    int index;

    if (x < 0 || y < 0 || x > IMAGE_WIDTH - 1 || y > IMAGE_HEIGHT - 1)
        return ;
    else
    {
        index = SIZE_LEN * y * 4 + x * 4;
        image_data[index + 2] = color >> 16; // RED COLOR COMPONENT
        image_data[index + 1] = (color & 0x00ff00) >> 8; // GREEN COLOR COMPONENT

    }
}


void    clear_image_data(char *image_data)
{
    int index;

    index = 0;
    while (index < IMAGE_HEIGHT * IMAGE_HEIGHT * 4)
        image_data[index++] = 0;
}





void    map_drawing(the_fdf *fdf)
{
    int i;
    int j;
    t_point main_point;
    t_point right_point;
    t_point down_point;

static int points_count;

    clear_image_data(fdf->map_struct.image_data);
    i = 0;
    while (i < fdf->map_struct.n)
    {
        j = 0;
        while (j < fdf->map_struct.m)
        {
            if (i == 0 && j == 0)
                points_count = 0;
            main_point = t_point_init(j, i, &(fdf->map_struct), fdf->transform);
            if (main_point.alt_255 == 1000)
            {
                j++;
                continue;
            }
            //printf("point %d\nx %d\n", points_count, main_point.x);
            //printf("y %d\n\n", main_point.y);
            if (j != fdf->map_struct.m - 1)
            {
                right_point = t_point_init(j + 1, i, &(fdf->map_struct), fdf->transform);
               if ((main_point.x <= IMAGE_WIDTH && main_point.x >=0 && main_point.y <= IMAGE_HEIGHT && main_point.y >= 0) || 
                        (right_point.x <= IMAGE_WIDTH  && right_point.x >=0 && right_point.y <= IMAGE_HEIGHT && right_point.y >= 0))
                line_drawing(fdf, main_point, right_point);//, fdf->map_struct.image_data);
            }
            if (i != fdf->map_struct.n - 1)
            {
                down_point = t_point_init(j, i + 1, &(fdf->map_struct), fdf->transform);
                if ((main_point.x <= IMAGE_WIDTH && main_point.y <= IMAGE_HEIGHT && main_point.x >=0 && main_point.y >= 0) || 
                        (down_point.x <= IMAGE_WIDTH && down_point.y <= IMAGE_HEIGHT && down_point.x >=0 && down_point.y >= 0))
                line_drawing(fdf, main_point, down_point);//, fdf->map_struct.image_data);
            }
            points_count++;
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
    t_matrix matrix;
    int x3;
    int y3;
    int z;
    int z3;

    if (transform.color_on)
        get_point_color(map_struct->map[y][x], &point, map_struct);
    else
        point.alt_255 = 0;

    scale_n_rotate_matrix(&matrix, map_struct, transform, x, y);

    if (1000 - matrix.z <= 0)
    {
        point.alt_255 = 1000;
        return(point);
    }
    if (transform.proj_type == 1)
    {
        
        matrix.x = (int)((double)matrix.x *                (double)(1000.0/(1000 - matrix.z)));
        matrix.y = (int)((double)matrix.y *                 (double)(1000.0/(1000 - matrix.z)));
    }
    point.x = matrix.x + transform.delta_x;
    point.y = matrix.y + transform.delta_y;
    return (point);
}


void    scale_n_rotate_matrix(t_matrix *matrix, t_map *map_struct, t_transform transform, int x, int y)
{
    int z;

    z = transform.scale * map_struct->map[y][x] - transform.scale * (map_struct->max_alt - map_struct->min_alt) / 2;
    y = transform.scale * y -  transform.scale * (map_struct->n - 1) / 2;
    x = transform.scale *  x -  transform.scale * (map_struct->m -1) / 2;

    matrix->x = (x*cos(transform.alpha)*cos(transform.beta) + 
        y*cos(transform.alpha)*sin(transform.beta)*sin(transform.gamma) - 
        y*sin(transform.alpha)*cos(transform.gamma) +
        z*cos(transform.alpha)*sin(transform.beta)*cos(transform.gamma) + 
        z*sin(transform.alpha)*sin(transform.gamma));
    matrix->y = (x*sin(transform.alpha)*cos(transform.beta) + 
        y*sin(transform.alpha)*sin(transform.beta)*sin(transform.gamma) + 
        y*cos(transform.alpha)*cos(transform.gamma) +
        z*sin(transform.alpha)*sin(transform.beta)*cos(transform.gamma) - 
        z*cos(transform.alpha)*sin(transform.gamma));
    matrix->z =(-x*sin(transform.beta) + y* cos(transform.beta)
        * sin (transform.gamma) + z* cos(transform.beta) * cos(transform.gamma));
}





static void    line_drow_x(the_fdf *fdf, t_point f, t_point s)
{
    t_variables vars;
    int     color;

    vars.a = f.y - s.y;
    vars.b = s.x - f.x;
    vars.c = f.x * s.y - s.x * f.y;
    vars.tmp_x = f.x;
    vars.tmp_y = f.y;
    vars.i = 0;
    if (f.x - s.x == 0)
        vars.step = 255.0;
    else
        vars.step = (double)(s.alt_255 - f.alt_255)/(ABS((s.x - f.x)));
    while (vars.tmp_x != s.x)
    {
        vars.tmp_y = (-vars.a * vars.tmp_x - vars.c) / vars.b;
        put_point_to_image(fdf->map_struct.image_data, vars.tmp_x, vars.tmp_y, (f.alt_255 + (int)(vars.step * vars.i)) * 0x010000 + (255 - f.alt_255 - (int)(vars.step * vars.i)) * 0x000100);
        vars.tmp_x += f.x <= s.x ? 1 : -1;
        vars.i++;
    }
}

static void    line_drow_y(the_fdf *fdf, t_point f, t_point s)
{
    t_variables vars;

    vars.a = f.y - s.y;
    vars.b = s.x - f.x;
    vars.c = f.x * s.y - s.x * f.y;
    vars.tmp_x = f.x;
    vars.tmp_y = f.y;
    vars.i = 0;
    if (f.y - s.y == 0)
        vars.step = 255.0;
    else
        vars.step = (double)(s.alt_255 - f.alt_255)/(ABS((s.y - f.y)));
    while (vars.tmp_y != s.y)
    {
        vars.tmp_x = (-vars.b * vars.tmp_y - vars.c) / vars.a;
        put_point_to_image(fdf->map_struct.image_data, vars.tmp_x, vars.tmp_y, (f.alt_255 + (int)(vars.step * vars.i)) * 0x010000 + (255 - f.alt_255 - (int)(vars.step * vars.i)) * 0x000100);
        vars.tmp_y += f.y <= s.y ? 1 : -1;
        vars.i++;
    }
}



void    line_drawing(the_fdf *fdf, t_point f, t_point s)
{
    if ((ABS(f.x - s.x)) >= (ABS(f.y - s.y)))
        line_drow_x(fdf, f, s);
    else
        line_drow_y(fdf, f, s);
}




static int  escape_pressed(int key_code)
{
    if (key_code == 53)
        exit(-2);
    return (0);
}