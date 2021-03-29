#include "main.h"

// static int	space_before_map(char **map, t_set *set)
// {
// 	int row;
// 	int col;
// 	int bol;

// 	col = 0;
// 	while (map[0][col] != '\0')
// 	{
// 		bol = 0;
// 		row = 0;
// 		while (map[row] != NULL)
// 		{
// 			if (map[row][col] != ' ')
// 				bol = 1;
// 			row++;
// 		}
// 		if (bol == 0)
// 			myerror("Error\nEmpty line before map\n", 0, set);
// 		col++;
// 	}
// 	return (0);
// }

// void	map_to_arr(t_set *set)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < set->tabs.map_h)
// 	{
// 		j = 0;
// 		while (j < set->tabs.map_w)
// 		{
// 			printf("|%c|", set->scene.map_arr[i][j]);
// 			// printf("%d - %d\n", i, j);
// 			j++;
// 		}
// 		i++;		
// 		printf("\n");
// 	}
// }

// static int	wall_horiz_isvalid(char **map, t_set *set)
// {
// 	int i;
// 	int j;
// 	int k;

// 	i = 0;
// 	while (map[i] != NULL)
// 	{
// 		k = set->tabs.map_w - 1;
// 			j = 0;
// 		while (map[i][j] != '\0' && map[i][j] == ' ')
// 			j++;
// 		if (map[i][j] == '\0' || map[i][j] != '1')
// 			myerror("Error\nWhere is wall???\n", 0, set);
// 		while (k >= 0 && map[i][k] == ' ')
// 			k--;
// 		if (k < 0 || map[i][k] != '1')
// 			myerror("Error\nWhere is wall??\n", 0, set);
// 		i++;
// 	}
// 	return (0);
// }

// static int	wall_vertic_isvalid(char **map, t_set *set)
// {
// 	int i;
// 	int j;
// 	int k;
// 	// int n;

// 	// n = 0;
// 	i = 0;
// 	while (map[0][i] != '\0')
// 	{
// 		k = set->tabs.map_h - 1;
// 		j = 0;
// 		while (map[j] != NULL && map[j][i] == ' ')
// 			j++;
// 		if (map[j] == NULL || map[j][i] != '1')
// 			myerror("Error\nWhere is wall???\n", 0, set);
// 		while (k >= 0 && map[k][i] == ' ')
// 			k--;
// 		if (k < 0 || map[k][i] != '1')
// 			myerror("Error\nWhere is wall?\n", 0, set);
// 		i++;
// 	}
// 	return (0);
// }

// static int	empty_space_isvalid(char **map, t_set *set)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (map[i] != NULL)
// 	{
// 		j = 0;
// 		while (map[i][j] != '\0')
// 		{
// 			if (map[i][j] != '1' && map[i][j] != ' ')
// 			{
// 				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
// 					myerror("Error\nWe found some empry/void space in map or invalid wall\n", 0, set);
// 				if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
// 					myerror("Error\nWe found some empry/void space in map or invalid wall\n", 0, set);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }



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
}

int			in_arr(int arr1[], int arr2[], int ind1, int ind2)
{
	int i;

	i = 0;
	while (arr1[i] != -1)
	{
		if (arr1[i] == ind1 && arr2[i] == ind2)
		{
			return (0);
		}
		// printf("<%d - %d - %d - %d>\n", arr1[i], arr2[i] ,ind1, ind2);
		i++;
	}
	return (1);
}

int			is_valid_tile(char c)
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

	// printf("%c\n", c);
	return (1);
}

int			is_in_map(char c)
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

void	*ft_onealloc(size_t nmemb, size_t size)
{
	char	*mem;

	if (!(mem = malloc(nmemb * size)))
		return (NULL);
	return (ft_memset(mem, -1, nmemb * size));
}


void		floodfill(t_set *set)
{
	(void)set;
	int arr1[2];
	int arr2[2];
	(void)arr1;
	(void)arr2;
	arr1[0] = 2;
	arr2[0] = 6;
	arr1[1] = -1;
	arr2[1] = -1;
	int max;
	if (set->tabs.map_w > set->tabs.map_h)
		max = set->tabs.map_w;
	else
		max = set->tabs.map_h;

	int *mx = ft_onealloc(max * max + 1, sizeof(int));
	int *my = ft_onealloc(max * max + 1, sizeof(int));
	int i;
	i = 0;
	int start_index_x = set->pattr.fpx / 64;
	int start_index_y = set->pattr.fpy / 64;
	int n;
	int ntek;

	n = 0;
	ntek = -1;

	mx[0] = start_index_x;
	my[0] = start_index_y;
	i = 0;
	while (ntek != n || i == 0)
	{
		i = 1;
		ntek++;
		if (is_in_map(set->scene.map[my[ntek] - 1][mx[ntek]]))
		{
			if (in_arr(my, mx, my[ntek] - 1, mx[ntek]))
			{
				n++;
				my[n] = my[ntek] - 1;
				mx[n] = mx[ntek];
			}
			else if (is_valid_tile(set->scene.map[my[ntek] - 1][mx[ntek]]))
				myerror("Error\n0 contacts the void or the wall is missing.\n",
				0, set);
		}
		else if (is_valid_tile(set->scene.map[my[ntek] - 1][mx[ntek]]))
			myerror("Error\n0 contacts the void.\n", 0, set);
		if (is_in_map(set->scene.map[my[ntek] + 1][mx[ntek]]))
		{
			if (in_arr(my, mx, my[ntek] + 1, mx[ntek]))
			{
				n++;
				my[n] = my[ntek] + 1;
				mx[n] = mx[ntek];
			}
			else if (is_valid_tile(set->scene.map[my[ntek] + 1][mx[ntek]]))
				myerror("Error\n0 contacts the void or the wall is missing.\n", 
				0, set);
		}
		else if (is_valid_tile(set->scene.map[my[ntek] + 1][mx[ntek]]))
			myerror("Error\n0 contacts the void.\n", 0, set);
		if (is_in_map(set->scene.map[my[ntek]][mx[ntek] - 1]))
		{
			if (in_arr(my, mx, my[ntek], mx[ntek] - 1))
			{
				n++;
				my[n] = my[ntek];
				mx[n] = mx[ntek] - 1;
			}
			else if (is_valid_tile(set->scene.map[my[ntek]][mx[ntek] - 1]))
				myerror("Error\n0 contacts the void or the wall is missing.\n",
				 0, set);
		}
		else if (is_valid_tile(set->scene.map[my[ntek]][mx[ntek] - 1]))
			myerror("Error\n0 contacts the void or the wall is missing.\n",
			0, set);
		if (is_in_map(set->scene.map[my[ntek]][mx[ntek] + 1]))
		{
			if (in_arr(my, mx, my[ntek], mx[ntek] + 1))
			{
				n++;
				my[n] = my[ntek];
				mx[n] = mx[ntek] + 1;
			}
			else if (is_valid_tile(set->scene.map[my[ntek]][mx[ntek] + 1]))
				myerror("Error\n0 contacts the void or the wall is missing.\n",
				0, set);
		}
		else if (is_valid_tile(set->scene.map[my[ntek]][mx[ntek] + 1]))
			myerror("Error\n0 contacts the void or the wall is missing.\n",
			0, set);
	}
	free(mx);
	free(my);
}

void			isvalid_map(t_set *set)
{
	int i;
	
	i = 0;
	while (set->scene.map[0][i] != '\0')
		if (is_in_map(set->scene.map[0][i++])) 
			myerror("Error\n0 contacts the void or the wall is missing.\n",
			0, set);
	i = 0;
	while (set->scene.map[set->tabs.map_h-1][i] != '\0')
		if (set->scene.map[set->tabs.map_h-1][i++] != '1')
			myerror("Error\n0 contacts the void or the wall is missing.\n",
			0, set);
	floodfill(set);
}