/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 15:00:39 by cocummin          #+#    #+#             */
/*   Updated: 2018/12/29 17:05:49 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>

# define ABS(a) a >= 0 ? a : -(a)



typedef struct s_point
{
    int x;
    int y;
}               t_point;

typedef struct s_transform
{
    double alpha;
    double beta;
    double gamma;

    int scale;
}               t_transform;

void    map_drawing(void *mlx_ptr, void *win_ptr, int arr[5][5], t_transform *transform);
void provider(int key);
void    line_drawing(void *mlx_ptr, void *win_ptr, t_point first, t_point second);
t_point *t_point_init(int x, int y, int z, t_transform transform);