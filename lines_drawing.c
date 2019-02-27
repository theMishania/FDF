/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <cocummin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 20:06:38 by chorange          #+#    #+#             */
/*   Updated: 2019/02/27 14:49:04 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static void	line_draw_x(t_fdf *fdf, t_point f, t_point s)
{
	t_variables	vars;

	vars.a = f.y - s.y;
	vars.b = s.x - f.x;
	vars.c = f.x * s.y - s.x * f.y;
	vars.tmp_x = f.x;
	vars.tmp_y = f.y;
	vars.i = 0;
	if (f.x - s.x == 0)
		vars.step = 255.0;
	else
		vars.step = (double)(s.alt_255 - f.alt_255) / (ABS((s.x - f.x)));
	while (vars.tmp_x != s.x)
	{
		vars.tmp_y = (-vars.a * vars.tmp_x - vars.c) / vars.b;
		put_point_to_image(fdf->map_struct.image_data, vars.tmp_x, vars.tmp_y,
			(f.alt_255 + (int)(vars.step * vars.i)) * 0x010000 +
			(255 - f.alt_255 - (int)(vars.step * vars.i)) * 0x000100);
		vars.tmp_x += f.x <= s.x ? 1 : -1;
		vars.i++;
	}
}

static void	line_draw_y(t_fdf *fdf, t_point f, t_point s)
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
		vars.step = (double)(s.alt_255 - f.alt_255) / (ABS((s.y - f.y)));
	while (vars.tmp_y != s.y)
	{
		vars.tmp_x = (-vars.b * vars.tmp_y - vars.c) / vars.a;
		put_point_to_image(fdf->map_struct.image_data, vars.tmp_x, vars.tmp_y,
		(f.alt_255 + (int)(vars.step * vars.i)) * 0x010000 +
			(255 - f.alt_255 - (int)(vars.step * vars.i)) * 0x000100);
		vars.tmp_y += f.y <= s.y ? 1 : -1;
		vars.i++;
	}
}

static void	line_drawing(t_fdf *fdf, t_point f, t_point s)
{
	if ((ABS(f.x - s.x)) >= (ABS(f.y - s.y)))
		line_draw_x(fdf, f, s);
	else
		line_draw_y(fdf, f, s);
}

int			draw_right(t_fdf *fdf, int i, int j, t_point main)
{
	t_point right;

	if (j != fdf->map_struct.m - 1)
	{
		right = t_point_init(j + 1, i, &(fdf->map_struct), fdf);
		if (right.alt_255 == 1000)
			return (0);
		if ((main.x <= IMAGE_WIDTH && main.x >= 0 && main.y <= IMAGE_HEIGHT &&
				main.y >= 0) ||
				(right.x <= IMAGE_WIDTH && right.x >= 0 &&
				right.y <= IMAGE_HEIGHT && right.y >= 0))
			line_drawing(fdf, main, right);
	}
	return (1);
}

int			draw_down(t_fdf *fdf, int i, int j, t_point main)
{
	t_point down;

	if (i != fdf->map_struct.n - 1)
	{
		down = t_point_init(j, i + 1, &(fdf->map_struct), fdf);
		if (down.alt_255 == 1000)
			return (0);
		if ((main.x <= IMAGE_WIDTH && main.y <= IMAGE_HEIGHT && main.x >= 0 &&
				main.y >= 0) ||
			(down.x <= IMAGE_WIDTH && down.y <= IMAGE_HEIGHT && down.x >= 0 &&
				down.y >= 0))
			line_drawing(fdf, main, down);
	}
	return (1);
}
