/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 19:44:33 by chorange          #+#    #+#             */
/*   Updated: 2019/02/19 20:25:09 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

# define ABS(a) (a) >= 0 ? (a) : -(a)

typedef struct s_map
{
	int **map;
	int m;
	int n;
	int min_alt;
	int max_alt;

	char *image_data;
}				t_map;

typedef struct s_point
{
int x;
int y;
int alt_255;
}   t_point;

typedef struct s_transform
{
double	alpha;
double	beta;
double	gamma;
int		proj_type;
int		color_on;
int		delta_x;
int		delta_y;

int scale;
int default_scale;
double height_scale;
double max_height_scale;
}   t_transform;

typedef struct 	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image;
	t_transform	transform;
	t_map 		map_struct;
}				the_fdf;

typedef struct s_variables
{
	int     tmp_x;
    int     tmp_y;
    int     i;
    double  step;
    int     a;
    int     b;
    int     c;
}				t_variables;

typedef struct s_matrix
{
	int x;
	int y;
	int z;
}			t_matrix;

void    map_drawing(the_fdf *fdf);
void	provider(int key, char *file_name);
void	line_drawing(the_fdf *fdf, t_point f, t_point s);
t_point t_point_init(int x, int y, t_map *map_struct, t_transform transform);
void	read_map(char *file_name, t_map *map_struct);
void    put_point_to_image(char *image_data, int x, int y, int color);
void    clear_image_data(char *image_data);
int		key_press(int key);
void	key_utils(t_transform *transform, int key);
void    norme_beater(t_transform *transform, int key);
void    norminette_fight(t_transform *transform, int key);
void    defeat_norm(t_transform *transform, int key);
void	fdf_init(the_fdf *fdf, char *file_name);
void    scale_n_rotate_matrix(t_matrix *matrix, t_map *map_struct, t_transform transform, int x, int y);
void    open_errors(char *file_name);
void	read_errors();
void    argc_count_errors(int argc);
void    projection_changes(int key, t_transform *transform);