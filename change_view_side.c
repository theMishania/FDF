/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_view_side.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:33:40 by cocummin          #+#    #+#             */
/*   Updated: 2019/02/23 11:36:13 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void front_or_backside(t_fdf *fdf, int key)
{
    if (key == 0x03)
    {
        fdf->transform.scale = fdf->transform.default_scale;
        fdf->transform.alpha = 0;
        fdf->transform.beta = 0;
        fdf->transform.gamma = M_PI / 2;
    }
    else if (key == 0x2E)
    {
        fdf->transform.scale = fdf->transform.default_scale;
        fdf->transform.alpha = 0;
        fdf->transform.beta = M_PI;
        fdf->transform.gamma = M_PI / 2;
    }
}

static void left_or_rightside(t_fdf *fdf, int key)
{
    if (key == 0x0F)
    {
        fdf->transform.scale = fdf->transform.default_scale;
        fdf->transform.alpha = 0;
        fdf->transform.beta = -M_PI / 2;
        fdf->transform.gamma = M_PI / 2;
    }
    else if (key == 0x25)
    {
        fdf->transform.scale = fdf->transform.default_scale;
        fdf->transform.alpha = 0;
        fdf->transform.beta = M_PI / 2;
        fdf->transform.gamma = M_PI / 2;
    }
}

void    change_view_side(t_fdf *fdf, int key)
{
    if (key == 0x11)
    {
        fdf->transform.scale = fdf->transform.default_scale;
        fdf->transform.alpha = 0;
        fdf->transform.beta = 0;
        fdf->transform.gamma = 0;
    }
    else if (key == 0x0B)
    {
        fdf->transform.scale = fdf->transform.default_scale;
        fdf->transform.alpha = 0;
        fdf->transform.beta = 0;
        fdf->transform.gamma = M_PI;
    }else
    {
        front_or_backside(fdf, key);
        left_or_rightside(fdf, key);
    }
    
}