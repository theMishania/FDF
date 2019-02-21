/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_guide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:48:58 by chorange          #+#    #+#             */
/*   Updated: 2019/02/21 20:00:40 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_string(t_fdf *fdf, int x, int y, char *string)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xFFFFFF, string);
}

void		drow_guide(t_fdf *fdf)
{
	if (!fdf->transform.guide_visible)
		put_string(fdf, 40, 20, "Press H to show Info & Guide");
	else
	{
		put_string(fdf, 40, 20, "FDF");
		put_string(fdf, 40, 40, "File:");
		put_string(fdf, 100, 40, fdf->file_name);
		put_string(fdf, 40, 80, "Guide:");
		put_string(fdf, 40, 100, "Press ARROWS, NUM4 and NUM6 to rotate map");
		put_string(fdf, 40, 120, "Press + or - to change scale");
		put_string(fdf, 40, 140, "Press 3 or 4 to change altitude scale");
		put_string(fdf, 40, 160,
			"Press C to activate/disactivate AltitudeGradientColor mode");
		put_string(fdf, 40, 180, "Press I to set iso projection");
		put_string(fdf, 40, 200,
			"Press O to set ortogonal (parallel) projection");
		put_string(fdf, 40, 220,
			"Press P to set perspective (central) projection");
		put_string(fdf, 40, 240, "Press ESC to exit");
		put_string(fdf, 40, 260, "Press H to hide Info & Guide");
	}
}
