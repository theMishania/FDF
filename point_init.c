/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 20:02:35 by chorange          #+#    #+#             */
/*   Updated: 2019/02/21 20:03:58 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_point_color(int alt, t_point *point, t_map *map_struct)
{
	if (map_struct->min_alt == map_struct->max_alt)
		point->alt_255 = 0;
	else
		point->alt_255 = -((map_struct->min_alt * 255)
			+ alt * (-255)) / (map_struct->max_alt - map_struct->min_alt);
}

static void	scale_n_rotate(t_matrix *matrix, t_fdf *fdf, int x, int y)
{
	int z;

	z = fdf->TR.scale * fdf->map_struct.map[y][x] -
		fdf->TR.scale * (fdf->map_struct.max_alt - fdf->map_struct.min_alt) / 2;
	y = fdf->TR.scale * y - fdf->TR.scale * (fdf->map_struct.n - 1) / 2;
	x = fdf->TR.scale * x - fdf->TR.scale * (fdf->map_struct.m - 1) / 2;
	z = fdf->TR.height_scale * (double)(z);
	matrix->x = (x * cos(fdf->TR.alpha) * cos(fdf->TR.beta) +
		y * cos(fdf->TR.alpha) * sin(fdf->TR.beta) * sin(fdf->TR.gamma) -
		y * sin(fdf->TR.alpha) * cos(fdf->TR.gamma) +
		z * cos(fdf->TR.alpha) * sin(fdf->TR.beta) * cos(fdf->TR.gamma) +
		z * sin(fdf->TR.alpha) * sin(fdf->TR.gamma));
	matrix->y = (x * sin(fdf->TR.alpha) * cos(fdf->TR.beta) +
		y * sin(fdf->TR.alpha) * sin(fdf->TR.beta) * sin(fdf->TR.gamma) +
		y * cos(fdf->TR.alpha) * cos(fdf->TR.gamma) +
		z * sin(fdf->TR.alpha) * sin(fdf->TR.beta) * cos(fdf->TR.gamma) -
		z * cos(fdf->TR.alpha) * sin(fdf->TR.gamma));
	matrix->z = (-x * sin(fdf->TR.beta) + y * cos(fdf->TR.beta)
		* sin(fdf->TR.gamma) + z * cos(fdf->TR.beta) * cos(fdf->TR.gamma));
}

t_point		t_point_init(int x, int y, t_map *map_struct, t_fdf *fdf)
{
	t_point		point;
	t_matrix	matrix;

	if (fdf->transform.color_on)
		get_point_color(map_struct->map[y][x], &point, map_struct);
	else
		point.alt_255 = 0;
	scale_n_rotate(&matrix, fdf, x, y);
	if (1000 - matrix.z <= 0 && fdf->transform.proj_type == 1)
	{
		point.alt_255 = 1000;
		return (point);
	}
	if (fdf->transform.proj_type == 1)
	{
		matrix.x = (int)((double)matrix.x *
			(double)(1000.0 / (1000 - matrix.z)));
		matrix.y = (int)((double)matrix.y *
			(double)(1000.0 / (1000 - matrix.z)));
	}
	point.x = matrix.x + fdf->transform.delta_x;
	point.y = matrix.y + fdf->transform.delta_y;
	return (point);
}
