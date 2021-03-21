#include "main.h"

void		myerror(char *mess, int err_code, t_set *set)
{
	int r;

	(void)r;
	r = write(2, mess, ft_strlen(mess));
	if (err_code == 1)
		free_mlx(set);
	else if (err_code == 2)
	{
		free_mlx(set);
		free_scene(set);
		free_tabs(set);
	}
	else if (err_code == 3)
	{
		free_scene(set);
		free_tabs(set);
	}
	else if (err_code == 4)
		free(((t_set *)set)->mlx.mlx);
	else if (err_code == 5)
		free_scene(set);
	exit(0);
}