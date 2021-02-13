#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_vars {
		void    *mlx;
		void    *win;
}				t_vars;

int				close(int key, void *var)
{
	t_vars *vars;

	vars = var;
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int             main(void)
{
	t_vars    vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 512, 512, "Hello worl!");
	mlx_hook(vars.win, 33, 0L, close, &vars);
	mlx_loop(vars.mlx);
} 
