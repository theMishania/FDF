/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:14:13 by cocummin          #+#    #+#             */
/*   Updated: 2019/02/19 20:18:31 by chorange         ###   ########.fr       */
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
            transform->beta +=  (M_PI / 60);
        else
            transform->beta -=  (M_PI / 60);
    }

    if (key == 0x7E || key == 0x7D)//Op or dow arrow pressed
    {
        if (key == 0x7E)
            transform->gamma +=  (M_PI / 60);
        else
            transform->gamma -=  (M_PI / 60);
    }

    if (key == 0x12 || key == 0x13)
    {
        if (key == 0x12)
            transform->alpha += (M_PI / 60);
        else
            transform->alpha -= (M_PI / 60);
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
                transform->scale -= 1;//-
            }
        }
        else
        {
            transform->scale += 1;//+ 
        }
                  
    }
    if (key == 0x56 || key == 0x58)
    {
		if (key == 0x58)
			transform->alpha += (M_PI / 60);//num 6
		else
			transform->alpha -= (M_PI / 60);// num 4
    }

	if (key == 0x23 || key == 0x22 || key == 0x1F)
    {
        projection_changes(key, transform);
    }
		// if (!transform->proj_type)
		// {
		// 	transform->proj_type = 1; // num 5
		// }
		// else
		// 	transform->proj_type = 0;
        
}

void    defeat_norm(t_transform *transform, int key)
{
    if (key == 0x08)
    {
        if (!transform->color_on)// c
            transform->color_on = 1;
        else
            transform->color_on = 0;
    }
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
    if (key == 0x14 || key == 0x15)
    {
        if (key == 0x14)
        {
            if (transform->height_scale <= transform->max_height_scale)
            {
                transform->height_scale += 0.1;
            }
        } 
        else
        {
            if (transform->height_scale > -transform->max_height_scale)
            {
                transform->height_scale -= 0.1;
            }
        }
    }
}

void    projection_changes(int key, t_transform *transform)
{
    transform->delta_x = 500;
	transform->delta_y = 500;
    if (key == 0x1F)
    {
        transform->scale = transform->default_scale;
	    transform->proj_type = 0;
        transform->alpha = 0.0;
        transform->beta = 0.0;
        transform->gamma = 0.0;
    }else if (key == 0x22)
    {
        transform->scale = transform->default_scale;
	    transform->proj_type = 0;
        transform->alpha = M_PI / 6;
        transform->beta = -M_PI / 4;
        transform->gamma = M_PI / 4;
    }
    else if (key == 0x23)
    {
        transform->scale = transform->default_scale;
	    transform->proj_type = 1;
        transform->alpha = 0.0;
        transform->beta = 0.0;
        transform->gamma = 0.0;
    }
}