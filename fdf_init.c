/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:50:45 by chorange          #+#    #+#             */
/*   Updated: 2019/02/21 19:55:12 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		transform_init(t_fdf *fdf)
{
	fdf->transform.proj_type = 0;
	fdf->transform.delta_x = 500;
	fdf->transform.delta_y = 500;
	fdf->transform.color_on = 0;
	fdf->transform.guide_visible = 0;
}

static void		get_min_n_max_alt(t_map *map_struct)
{
	int i;
	int j;

	i = 0;
	map_struct->max_alt = map_struct->map[0][0];
	map_struct->min_alt = map_struct->map[0][0];
	while (i < map_struct->n)
	{
		j = 0;
		while (j < map_struct->m)
		{
			if (map_struct->map[i][j] > map_struct->max_alt)
				map_struct->max_alt = map_struct->map[i][j];
			if (map_struct->map[i][j] < map_struct->min_alt)
				map_struct->min_alt = map_struct->map[i][j];
			j++;
		}
		i++;
	}
}

void			fdf_init(t_fdf *fdf, char *file_name)
{
	int bytes;
	int len;
	int endian;

	bytes = 8;
	len = 1000;
	endian = 0;
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1000, 1000, "FDF");
	fdf->image = mlx_new_image(fdf->mlx_ptr, 1000, 1000);
	transform_init(fdf);
	ft_strcpy(fdf->file_name, file_name);
	read_map(file_name, &(fdf->map_struct));
	get_min_n_max_alt(&(fdf->map_struct));
	(fdf->map_struct.m >= fdf->map_struct.n) ?
		(fdf->transform.default_scale = 800 / fdf->map_struct.m) :
		(fdf->transform.default_scale = 800 / fdf->map_struct.n);
	fdf->transform.height_scale = 1.0;
	fdf->transform.max_height_scale = (double)84.0 /
			(double)fdf->transform.default_scale;
	fdf->transform.scale = fdf->transform.default_scale;
	fdf->map_struct.image_data = mlx_get_data_addr(fdf->image,
			&bytes, &len, &endian);
}
