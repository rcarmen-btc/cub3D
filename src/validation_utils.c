/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/03/31 11:27:09 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int					check_file_exten(char *path, char *ext)
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

void				isvalid_arg(int ac, char **av, t_set *set)
{
	int				fd;
	char			buff[2];

	set->scene.save = -1;
	if (ac < 2 || ac > 3)
		myerror("Error\nIncorrect number of arguments.\n", 0, set);
	if (ac == 2 && !check_file_exten(av[1], ".cub"))
		myerror("Error\nCheck the extension of scene-file. \n", 0, set);
	if (ac == 3 && (ft_strlen(av[2]) != 6 || ft_strncmp(av[2], "--save", 6)))
		myerror("Error\nCheck the argument \"--save\".\n", 0, set);
	else if (ac == 3 && ft_strlen(av[2]) == 6)
		set->scene.save = 1;
	if ((fd = open(av[1], O_RDONLY)) == -1 || read(fd, buff, 1) == -1)
		myerror("Error\nNo such file exists.\n", 0, set);
}

int					in_arr(int arr1[], int arr2[], int ind1, int ind2)
{
	int i;

	i = 0;
	while (arr1[i] != -1)
	{
		if (arr1[i] == ind1 && arr2[i] == ind2)
			return (0);
		i++;
	}
	return (1);
}

int					is_valid_tile(char c)
{
	if (c == '1')
		return (0);
	else if (c == 'N')
		return (0);
	else if (c == 'S')
		return (0);
	else if (c == 'W')
		return (0);
	else if (c == 'E')
		return (0);
	else if (c == '2')
		return (0);
	else if (c == '0')
		return (0);
	return (1);
}

int					is_in_map(char c)
{
	if (c == 'N')
		return (1);
	else if (c == 'S')
		return (1);
	else if (c == 'W')
		return (1);
	else if (c == 'E')
		return (1);
	else if (c == '2')
		return (1);
	else if (c == '0')
		return (1);
	return (0);
}
