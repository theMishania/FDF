/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:23:37 by chorange          #+#    #+#             */
/*   Updated: 2019/02/26 20:09:39 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_drawing(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	main_point;

	clear_image_data(fdf->map_struct.image_data);
	i = 0;
	while (i < fdf->map_struct.n)
	{
		j = 0;
		while (j < fdf->map_struct.m)
		{
			main_point = t_point_init(j, i, &(fdf->map_struct), fdf);
			IF_DO_CONT((main_point.alt_255 == 1000), (j++));
			IF_DO_CONT((!draw_right(fdf, i, j, main_point)), (j++));
			IF_DO_CONT((!draw_down(fdf, i, j, main_point)), (j++));
			j++;
		}
		i++;
	}
}
