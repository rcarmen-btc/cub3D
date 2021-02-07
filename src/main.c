#include "mlx.h"

int main()
{
	void	*mlx;
	void    *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 512, 512, "Hello world!");
	mlx_loop(mlx);
}