#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "map_drawing.h"

int deal_key(int key)
{
	if (key == 0x35) // Escape pressed
	{
		exit(-2);
	}

	provider(key, "lo");
	
	return (0);
}

void	get_main_n_max_alt(t_map *map_struct)
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

void provider(int key, char *file_name)
{
	static void *mlx_ptr;
	static void *win_ptr;
	static void *image;

	static t_transform transform;
	static t_map map_struct;

	int i = 0;
	int j;

	if (!mlx_ptr)
	{
		mlx_ptr = mlx_init();
		win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "NICEEEEEE");
		image = mlx_new_image(mlx_ptr, 1000, 1000);


		transform.scale = 30;
		transform.proj_type = 0;
		transform.delta_x = 500;
		transform.delta_y = 500;
		transform.color_on  = 0;
		read_map(file_name, &map_struct);
		get_main_n_max_alt(&map_struct);
		
		int bytes = 8;
		int len = 1000;
		int endian = 0;
		map_struct.image_data = mlx_get_data_addr(image, &bytes, &len, &endian);
		//mlx_put_image_to_window(mlx_ptr, win_ptr, image, 0, 0);
	}
	mlx_clear_window(mlx_ptr, win_ptr);

if (key == 0x7B || key == 0x7C) // Left or right arrow pressed
	{
		if (key == 0x7C)
			transform.beta +=  (M_PI / 56);
		else
			transform.beta -=  (M_PI / 56);
	}

	if (key == 0x7E || key == 0x7D)//Op or dow arrow pressed
	{
		if (key == 0x7E)
			transform.gamma +=  (M_PI / 56);
		else
			transform.gamma -=  (M_PI / 56);
	}
	
	if (key == 0x4E || key == 0x45)
	{
		if (key == 0x4E)
			transform.scale -= 2;//-
		else
			transform.scale += 2;//+
	}

	if (key == 0x56 || key == 0x58)
		if (key == 0x58)
			transform.alpha += (M_PI / 56);//num 6
		else
			transform.alpha -= (M_PI / 56);// num 4

	if (key == 0x57)
		if (!transform.proj_type)
			transform.proj_type = 1;  // num 5
		else
			transform.proj_type = 0;
	if (key == 0x08)
		if (!transform.color_on)// c
			transform.color_on = 1;
		else
			transform.color_on = 0;
	if (key == 0x0D || key == 0x01)
	{
		if (key == 0x0D)
			transform.delta_y -= 20;// w
		else
			transform.delta_y +=20;// s
	}
		if (key == 0x00 || key == 0x02)
	{
		if (key == 0x02)
			transform.delta_x += 20;// d
		else
			transform.delta_x -=20;// a
	}

/*
	if (key == 0xff51 || key == 0xff53) // Left or right arrow pressed
	{
		if (key == 0xff53)
			transform.beta +=  (M_PI / 56);
		else
			transform.beta -=  (M_PI / 56);
	}

	if (key == 0xff52 || key == 0xff54)//Op or dow arrow pressed
	{
		if (key == 0xff52)
			transform.gamma +=  (M_PI / 56);
		else
			transform.gamma -=  (M_PI / 56);
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
			transform.alpha += (M_PI / 56);//num 6
		else
			transform.alpha -= (M_PI / 56);// num 4

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
	map_drawing(mlx_ptr, win_ptr, &map_struct, &transform);
	mlx_put_image_to_window(mlx_ptr, win_ptr, image, 0, 0);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);


}

int main(int ac, char **av)
{
	//puts("begin");
	//printf("%d", ABS(0));
	provider(4, av[1]);
	return (0);
}
