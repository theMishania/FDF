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

	if (!mlx_ptr)
	{
		mlx_ptr = mlx_init();
		win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "NICEEEEEE");
		transform.scale = 30;
	}
	mlx_clear_window(mlx_ptr, win_ptr);
	/*    /\      */
	int arr[5][5] =
	{
		1, 0, 0, 0, -0,
		0, 2, 2, 2, 0,
		0, 2, -1, 2, 0,
		0, 2, 2, 2, 0,
		-0, -0, 0, 0, -0
	};
	if (key == 0x7B || key == 0x7C) // Left or right arrow pressed
	{
		if (key == 0x7C)
			transform.beta +=  (M_PI / 18);
		else
			transform.beta -=  (M_PI / 18);
	}

	if (key == 0x7E || key == 0x7D)//Op or dow arrow pressed
	{
		if (key == 0x7E)
			transform.gamma +=  (M_PI / 18);
		else
			transform.gamma -=  (M_PI / 18);
	}
	
	if (key == 0x1B || key == 0x18)
	{
		if (key == 0x1B)
			transform.scale -= 10;
		else
			transform.scale += 10;
	}

	if (key == 0x58 || key == 0x56)
		if (key == 0x58)
			transform.alpha += (M_PI / 18);
		else
			transform.alpha -= (M_PI / 18);

	map_drawing(mlx_ptr, win_ptr, arr, &transform);

	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);


}

int main()
{
	provider(4);
	return (0);
}