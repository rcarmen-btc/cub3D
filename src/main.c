#include "mlx.h"

int main()
{
	void	*mlx;
	//void    *mlx_win;
	void 	*img;

	mlx = mlx_init();
	//mlx_win = mlx_new_window(mlx, 512, 512, "Hello world!");
	//mlx_new_window(mlx, 512, 512, "Hello");
	//img = mlx_new_image(mlx, 512, 512);
	mlx_new_image(mlx, 512, 512);

	//mlx_loop(mlx);
}