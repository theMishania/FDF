#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "map_drawing.h"

/*int deal_key(int key)
{
	if (key == 0x35) // Escape pressed
	{
		exit(-2);
	}

	provider(key, "lo");
	
	return (0);
}*/

int	key_press(int key, void *param)
{
		provider(key, "lo");
		return (0);
}

void	get_min_n_max_alt(t_map *map_struct)
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

void	fdf_init(the_fdf *fdf, char *file_name)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1000, 1000, "NICEEEEEE");
	fdf->image = mlx_new_image(fdf->mlx_ptr, 1000, 1000);


	fdf->transform.scale = 30;
	fdf->transform.proj_type = 0;
	fdf->transform.delta_x = 500;
	fdf->transform.delta_y = 500;
	fdf->transform.color_on  = 0;
	read_map(file_name, &(fdf->map_struct));
	get_min_n_max_alt(&(fdf->map_struct));
		
	int bytes = 8;
	int len = 1000;
	int endian = 0;
	fdf->map_struct.image_data = mlx_get_data_addr(fdf->image, &bytes, &len, &endian);
}

void provider(int key, char *file_name)
{
	static the_fdf fdf;
	int i = 0;
	int j;

	if (!fdf.mlx_ptr)
		fdf_init(&fdf, file_name);
	mlx_clear_window(fdf.mlx_ptr, fdf.win_ptr);

	key_utils(&(fdf.transform), key);
	
	

	
	

/*
	if (key == 0xff51 || key == 0xff53) // Left or right arrow pressed
	{
		if (key == 0xff53)
			transform.beta +=  0.05;
		else
			transform.beta -=  0.05;
	}

	if (key == 0xff52 || key == 0xff54)//Op or dow arrow pressed
	{
		if (key == 0xff52)
			transform.gamma +=  0.05;
		else
			transform.gamma -=  0.05;
	}
	
	if (key == 0xffad || key == 0xffab)
	{
		if (key == 0xffad)
			transform.scale -= 2;//-
		else
			transform.scale += 2;//+
	}

	if (key == 0xff96 || key == 0xff98)
		if (key == 0xff98)
			transform.alpha += 0.05;//num 6
		else
			transform.alpha -= 0.05;// num 4

	if (key == 0xff9d)
		if (!transform.proj_type)
			transform.proj_type = 1;  // num 5
		else
			transform.proj_type = 0;
	if (key == 0x63)
		if (!transform.color_on)// c
			transform.color_on = 1;
		else
			transform.color_on = 0;
	if (key == 0x77 || key == 0x73)
	{
		if (key == 0x77)
			transform.delta_y -= 20;// w
		else
			transform.delta_y +=20;// s
	}
		if (key == 0x61 || key == 0x64)
	{
		if (key == 0x64)
			transform.delta_x += 20;// d
		else
			transform.delta_x -=20;// a
	}*/
	map_drawing(&fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.image, 0, 0);

	mlx_hook(fdf.win_ptr, 2, 1L<<0, key_press, (void*)0);
	//mlx_hook(fdf->win, 17, 1L << 17, close, fdf);
	//mlx_hook(fdf->win, 4, 1L << 4, mouse_press, fdf);
	//mlx_hook(fdf->win, 5, 1L << 5, mouse_release, fdf);
	//mlx_hook(fdf->win, 6, 1L << 6, mouse_move, fdf);

	mlx_loop(fdf.mlx_ptr);


}

int main(int ac, char **av)
{
	//puts("begin");
	//printf("%d", ABS(0));
	provider(4, av[1]);
	return (0);
}
