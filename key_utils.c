/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:24:02 by chorange          #+#    #+#             */
/*   Updated: 2019/02/21 20:15:46 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	projection_changes(t_fdf *fdf, int key)
{
	fdf->transform.delta_x = 500;
	fdf->transform.delta_y = 500;
	if (key == 0x1F)
		fdf->transform.proj_type = 0;
	else if (key == 0x22)
	{
		fdf->transform.proj_type = 0;
		fdf->transform.alpha = M_PI / 6;
		fdf->transform.beta = -M_PI / 4;
		fdf->transform.gamma = M_PI / 4;
	}
	else if (key == 0x23)
		fdf->transform.proj_type = 1;
}

static void	norme_beater(t_fdf *fdf, int key)
{
	if (key == 53)
	{
		free_all(&(fdf->map_struct));
		exit(-2);
	}
	else if (key == 0x7B || key == 0x7C)
	{
		if (key == 0x7C)
			fdf->transform.beta += (M_PI / 60);
		else
			fdf->transform.beta -= (M_PI / 60);
	}
	else if (key == 0x7E || key == 0x7D)
	{
		if (key == 0x7E)
			fdf->transform.gamma += (M_PI / 60);
		else
			fdf->transform.gamma -= (M_PI / 60);
	}
}

static void	norminette_fight(t_fdf *fdf, int key)
{
	if (key == 0x1B || key == 0x18)
	{
		if (key == 0x1B)
		{
			if (fdf->transform.scale >= 2)
				fdf->transform.scale -= 1;
		}
		else
			fdf->transform.scale += 1;
	}
	else if (key == 0x56 || key == 0x58)
	{
		if (key == 0x58)
			fdf->transform.alpha += (M_PI / 60);
		else
			fdf->transform.alpha -= (M_PI / 60);
	}
	else if (key == 0x23 || key == 0x22 || key == 0x1F)
		projection_changes(fdf, key);
}

static void	defeat_norm(t_fdf *fdf, int key)
{
	if (key == 0x08)
		fdf->transform.color_on = (!fdf->transform.color_on) ? 1 : 0;
	else if (key == 0x04)
		fdf->transform.guide_visible = (!fdf->transform.guide_visible) ? 1 : 0;
	else if (key == 0x14 || key == 0x15)
	{
		if (key == 0x14)
		{
			if (fdf->transform.height_scale <= fdf->transform.max_height_scale)
				fdf->transform.height_scale += 0.1;
		}
		else
		{
			if (fdf->transform.height_scale > -fdf->transform.max_height_scale)
				fdf->transform.height_scale -= 0.1;
		}
	}
}

void		key_utils(t_fdf *fdf, int key)
{
	norme_beater(fdf, key);
	norminette_fight(fdf, key);
	defeat_norm(fdf, key);
}
