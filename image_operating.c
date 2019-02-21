/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_operate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:47:41 by chorange          #+#    #+#             */
/*   Updated: 2019/02/21 19:49:41 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_point_to_image(char *image_data, int x, int y, int color)
{
	int	index;

	if (x < 0 || y < 0 || x > IMAGE_WIDTH - 1 || y > IMAGE_HEIGHT - 1)
		return ;
	else
	{
		index = SIZE_LEN * y * 4 + x * 4;
		image_data[index + 2] = color >> 16;
		image_data[index + 1] = (color & 0x00ff00) >> 8;
	}
}

void	clear_image_data(char *image_data)
{
	int index;

	index = 0;
	while (index < IMAGE_HEIGHT * IMAGE_HEIGHT * 4)
		image_data[index++] = 0;
}
