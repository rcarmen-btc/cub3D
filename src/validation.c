#include "main.h"

//void			isvalid_map(t_params *params)
//{
//	int				i;
//	int				j;
//	int				len;
//	char			**map;

//	map = params->map;
//	i = 0;
//	j = 0;
//	while (map[j][i])
//		if ('1' != map[0][i] || ' ' == map[0][i++])
//			return ;
//	i = 0;
//	j++;
//	while (map[j])
//	{
//		while (map[j][i])
//		{
//			if (map[j][i] == 1)
//			{

//			}
//			i++;
//		}
//		j++;	
//	}	
//}

int		check_file_exten(char *path, char *ext)
{
	int		i;
	int		path_len;
	int		ext_len;

	i = 1;
	path_len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	while (i <= ext_len)
	{
		if (path[path_len - i] != ext[ext_len - i])
			return (0);
		i++;
	}
	return (1);
}

void		isvalid_arg(int ac, char **av, t_set *set)
{	
	set->scene.save = -1;
	if (ac < 2 || ac > 3)
		myerror("Error\nIncorrect number of arguments.\n", 0, set);
	if (ac == 2 && !check_file_exten(av[1], ".cub"))
		myerror("Error\nCheck the extension of scene-file. \n", 0, set);
	if (ac == 3 && (ft_strlen(av[2]) != 6 || ft_strncmp(av[2], "--save", 6)))
		myerror("Error\nCheck the argument \"--save\".\n", 0, set);
	else if (ac == 3 && ft_strlen(av[2]) == 6)
		set->scene.save = 1;
	printf("%d\n", set->scene.save);
}