/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 19:44:33 by chorange          #+#    #+#             */
/*   Updated: 2019/02/26 20:10:27 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include "minilibx/mlx.h"

# define TR transform
# define IMAGE_WIDTH 1000
# define IMAGE_HEIGHT 1000
# define SIZE_LEN 1000

# define ABS(a) (a) >= 0 ? (a) : -(a)
# define CHECK(a) if (!a) malloc_error();
# define CHECK_GNL(a) if (a == -1) read_errors();
# define IF_DO_CONT(a, x) if (a) {x; continue ;}

typedef struct	s_map
{
	int		**map;
	int		m;
	int		n;
	int		min_alt;
	int		max_alt;

	char	*image_data;
}				t_map;

typedef struct	s_point
{
	int x;
	int y;
	int alt_255;
}				t_point;

typedef struct	s_transform
{
	double	alpha;
	double	beta;
	double	gamma;
	int		proj_type;
	int		color_on;
	int		delta_x;
	int		delta_y;

	int		scale;
	int		default_scale;
	double	height_scale;
	double	max_height_scale;
	int		guide_visible;
}				t_transform;

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image;
	t_transform	transform;
	t_map		map_struct;
	char		file_name[64];
}				t_fdf;

typedef struct	s_variables
{
	int		tmp_x;
	int		tmp_y;
	int		i;
	double	step;
	int		a;
	int		b;
	int		c;
}				t_variables;

typedef struct	s_matrix
{
	int x;
	int y;
	int z;
}				t_matrix;

void			read_map(char *file_name, t_map *map_struct);
void			fdf_init(t_fdf *fdf, char *file_name);

void			provider(int key, char *file_name);

void			map_drawing(t_fdf *fdf);
t_point			t_point_init(int x, int y, t_map *map_struct, t_fdf *fdf);

int				draw_right(t_fdf *fdf, int i, int j, t_point main_point);
int				draw_down(t_fdf *fdf, int i, int j, t_point main_point);

void			draw_guide(t_fdf *fdf);

void			put_point_to_image(char *image_data, int x, int y, int color);
void			clear_image_data(char *image_data);

void			key_utils(t_fdf *fdf, int key);
void			change_view_side(t_fdf *fdf, int key);

void			open_errors(char *file_name);
void			read_errors();
void			malloc_error();
void			argc_count_errors(int argc);

void			free_all(t_map *map_struct);

#endif
