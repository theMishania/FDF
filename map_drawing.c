/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 10:39:42 by cocummin          #+#    #+#             */
/*   Updated: 2018/12/29 17:07:02 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "map_drawing.h"

// int arr[5][5] =
// 	{
// 		0, 0, 0, 0, 0,
// 		0, 2, 2, 2, 0,
// 		0, 2, 2, 2, 0,
// 		0, 2, 2, 2, 0,
// 		-0, -0, 0, 0, 0
// 	};


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
            printf("LOOOP!!!!11111\n");
            if (j != 4)
            {
                right_point = t_point_init(j + 1, i,arr[i][j + 1], *transform);
                line_drawing(mlx_ptr, win_ptr, *main_point, *right_point);
            }
            printf("LOOOP!!!!2222\n");
            if (i != 4)
            {
                printf("WHAT IS GOING ON!!!!2222\n");
                down_point = t_point_init(j, i + 1, arr[i + 1][j], *transform);
                printf("DONT KNOWWWWW!!!!2222\n");
                line_drawing(mlx_ptr, win_ptr, *main_point, *down_point);
                printf("DONT KNOWWWWW!!!!3333\n");
            }
            printf("LOOOP!!!!3333\n");
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
    printf("TMP X = %i\n TMP Y = %i\n", tmp_x, tmp_y);
    printf("SEcon X = %i Second Y = %i\n", second.x, second.y);
    if ((ABS(first.x - second.x)) >= (ABS(first.y - second.y)))
    {
        while (tmp_x != second.x)
        {
            // printf("1\n");
            tmp_y = (-a * tmp_x - c) / b;
            mlx_pixel_put(mlx_ptr, win_ptr, tmp_x, tmp_y, 0xFFFFFF);
            tmp_x += first.x <= second.x ? 1 : -1;
        }
    }
    else
    {
        while (tmp_y != second.y)
        {
            // printf("2\n");
            tmp_x = (-b * tmp_y - c) / a;
            mlx_pixel_put(mlx_ptr, win_ptr, tmp_x, tmp_y, 0xFFFFFF);
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


// int main()
// {
//     void    *mlx_ptr;
//     void    *win_ptr;
//     t_point first;
//     t_point second;

//     int a = 10;
//     int b = 20;
//     int c = 15;
//     int d = 20;

//     printf("%i\n", a - b);
//     printf("%i\n", ABS(a - b));
//     printf("%i\n", ABS(c - d));
//     if ((ABS(a - b)) <= (ABS(c - d)))
//         printf("YOOOOOOOOO\n");

//     //Initializetion
//     first.x = 500;
//     first.y = 0;

//     second.x = 500;
//     second.y = 500;

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "Line Drawing");

//     line_drawing(mlx_ptr, win_ptr, first, second);

//     mlx_key_hook(win_ptr, escape_pressed, (void*)0);
//     mlx_loop(mlx_ptr);
//     return (0);
// }