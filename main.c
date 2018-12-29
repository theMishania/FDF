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
	provider(key);
	return (0);
}

void provider(int key)
{
	static void *mlx_ptr;
	static void *win_ptr;
	// static double Q;
	// static double beta;
	// static double gamma;
	static t_transform transform;
	// int colour;
	int i = 0;
	int j;

	if (transform.alpha == 0) 
	{
		mlx_ptr = mlx_init();
		win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "NICEEEEEE");
		transform.scale = 30;
		while (i < 1000)
		{
			j = 0;
			while (j < 1000)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0x000000);//0x4D4D4C);
				j++;
			}
			i++;
		}
	}
	printf("HEREEEE?1111\n");
	mlx_clear_window(mlx_ptr, win_ptr);
	/*    /\      */
	printf("HEREEEE?222\n");
	int arr[5][5] =
	{
		1, 0, 0, 0, -1,
		0, 2, 2, 2, 0,
		0, 2, -1, 2, 0,
		0, 2, 2, 2, 0,
		-1, -0, 0, 0, -1
	};
	printf("HEREEEE?333\n");
	transform.alpha = M_PI / 2;
	 //beta = M_PI / 6;
	 //gamma = M_PI / 2;
	// printf("beta = %lf\n", beta);
	// printf("gamma = %lf\n", gamma);
	printf("HEREEEE?4444\n");
	if (key == 0x7B || key == 0x7C) // Left or right arrow pressed
		if (key == 0x7C)
			transform.gamma +=  (M_PI / 18);
		else
			transform.gamma -=  (M_PI / 18);

	if (key == 0x7E || key == 0x7D)//Op or dow arrow pressed
		if (key == 0x7E)
			transform.beta +=  (M_PI / 18);
		else
			transform.beta -=  (M_PI / 18);
	
	if (key == 0x1B || key == 0x18)
		if (key == 0x1B)
			transform.scale--;
		else
			transform.scale++;

	printf("HEREEEE?55555\n");
	map_drawing(mlx_ptr, win_ptr, arr, &transform);
	printf("HEREEEE?66666\n");
	//Q += (M_PI / 72);
	//beta +=  (M_PI / 18);
	
	//mlx_string_put(mlx_ptr, win_ptr, 252, 252, 0xFFFFFF, "0");
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);


}

int main()
{
	provider(4);
	return (0);
}