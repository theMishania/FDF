/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   provider.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:02:32 by chorange          #+#    #+#             */
/*   Updated: 2019/02/26 20:07:58 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_press(int key)
{
	provider(key, "lo");
	return (0);
}

void		provider(int key, char *file_name)
{
	static t_fdf fdf;

	if (!fdf.mlx_ptr)
		fdf_init(&fdf, file_name);
	mlx_clear_window(fdf.mlx_ptr, fdf.win_ptr);
	key_utils(&fdf, key);
	map_drawing(&fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.image, 0, 0);
	draw_guide(&fdf);
	mlx_hook(fdf.win_ptr, 2, 1L << 0, key_press, (void*)0);
	mlx_loop(fdf.mlx_ptr);
}
