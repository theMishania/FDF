/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:48:58 by chorange          #+#    #+#             */
/*   Updated: 2019/02/23 11:46:37 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_string(t_fdf *fdf, int x, int y, char *string)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xFFFFFF, string);
}

static void draw_sides_guide(t_fdf *fdf)
{
	put_string(fdf, 650, 100, "Press F to see frontside");
	put_string(fdf, 650, 120, "Press M to see backside");
	put_string(fdf, 650, 140, "Press T to see topside");
	put_string(fdf, 650, 160, "Press B to see bottomside");
	put_string(fdf, 650, 180, "Press R ro see rightside");
	put_string(fdf, 650, 200, "Press L to see leftside");
}

static void put_projection(t_fdf *fdf)
{
	if (fdf->transform.proj_type == 0)
	{
		if (fdf->transform.alpha == M_PI / 6 && fdf->transform.beta == -M_PI / 4 &&
		fdf->transform.gamma == M_PI / 4)
		{
			put_string(fdf, 40, 960, "Projection Type: ISO");
		}
		else
			put_string(fdf, 40, 960, "Projection Type: Parallel");
	}
	else
	{
		put_string(fdf, 40, 960, "Projection Type: Central");
	}
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
		draw_sides_guide(fdf);
	}
	put_projection(fdf);
}
