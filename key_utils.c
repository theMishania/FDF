/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:14:13 by cocummin          #+#    #+#             */
/*   Updated: 2019/02/12 22:33:23 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_drawing.h"
#include <math.h>

void    key_utils(t_transform *transform, int key)
{
    norme_beater(transform, key);
    norminette_fight(transform, key);
    defeat_norm(transform, key);
}

void    norme_beater(t_transform *transform, int key)
{
    if (key == 53)
            exit(-2);
    if (key == 0x7B || key == 0x7C) // Left or right arrow pressed
     {
        if (key == 0x7C)
            transform->beta +=  (M_PI / 56);
        else
            transform->beta -=  (M_PI / 56);
    }

        if (key == 0x7E || key == 0x7D)//Op or dow arrow pressed
        {
            if (key == 0x7E)
                transform->gamma +=  (M_PI / 56);
            else
                transform->gamma -=  (M_PI / 56);
        }
}

void    norminette_fight(t_transform *transform, int key)
{
    if (key == 0x1B || key == 0x18)
    {
        if (key == 0x1B)
        {
           if (transform->scale >= 2)
            {
                transform->scale -= 2;//-
            }
        }
        else
            transform->scale += 2;//+       
    }
    if (key == 0x56 || key == 0x58)
		if (key == 0x58)
			transform->alpha += (M_PI / 56);//num 6
		else
			transform->alpha -= (M_PI / 56);// num 4

	if (key == 0x21)
		if (!transform->proj_type)
		{
			if (transform->scale < 195)
				transform->proj_type = 1; // num 5
		}
		else
			transform->proj_type = 0;
}

void    defeat_norm(t_transform *transform, int key)
{
    if (key == 0x08)
        if (!transform->color_on)// c
            transform->color_on = 1;
        else
            transform->color_on = 0;
    if (key == 0x0D || key == 0x01)
    {
        if (key == 0x0D)
            transform->delta_y -= 20;// w
        else
            transform->delta_y +=20;// s
    }
    if (key == 0x00 || key == 0x02)
    {
        if (key == 0x02)
            transform->delta_x += 20;// d
        else
            transform->delta_x -=20;// a
    }
}