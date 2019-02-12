/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 19:44:33 by chorange          #+#    #+#             */
/*   Updated: 2019/02/12 22:32:42 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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
}   t_transform;

typedef struct 	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image;
	t_transform	transform;
	t_map 		map_struct;
}				the_fdf;

void    map_drawing(the_fdf *fdf);
void	provider(int key, char *file_name);
void	line_drawing(the_fdf *fdf, t_point f, t_point s);
t_point t_point_init(int x, int y, t_map *map_struct, t_transform transform);
void	read_map(char *file_name, t_map *map_struct);
void    put_point_to_image(char *image_data, int x, int y, int color);
void    clear_image_data(char *image_data);
int	key_press(int key, void *param);
void	key_utils(t_transform *transform, int key);
void    norme_beater(t_transform *transform, int key);
void    norminette_fight(t_transform *transform, int key);
void    defeat_norm(t_transform *transform, int key);