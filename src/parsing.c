/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/18 07:30:36 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char			**find_substr(char *line, char *substr, int *ps)
{
	char			*tmp;
	char			**param_split;

	param_split = NULL;
	if (NULL != (tmp = ft_strnstr(line, substr, 3)))
	{
		(*ps)++;
		param_split = ft_split(line, ' ');
		return (param_split);
	}
	return (NULL);
}

void				isfullparam(t_set set, char *line)
{
	char			**param_split;
	int ps;

	ps = 0;
	if (NULL != (param_split = find_substr(line, "R ", &ps)))
	{
		if (set.scene.rxy[0] != 0 && set.scene.rxy[1] != 0)
			myerror("Error\nTwo or more R param\n", 0, &set);
		free_param_split(param_split, 3);
		return ;
	}
	else if (NULL != (param_split = find_substr(line, "NO ", &ps)) && NULL != set.scene.no_t)
			myerror("Error\nTwo or more NO param\n", 0, &set);
	else if (NULL != (param_split = find_substr(line, "SO ", &ps)) && NULL != set.scene.so_t)
			myerror("Error\nTwo or more SO param\n", 0, &set);
	else if (NULL != (param_split = find_substr(line, "WE ", &ps)) && NULL != set.scene.we_t)
			myerror("Error\nTwo or more WE param\n", 0, &set); 
	else if (NULL != (param_split = find_substr(line, "EA ", &ps)) && NULL != set.scene.ea_t)
			myerror("Error\nTwo or more EA param\n", 0, &set);
	else if (NULL != (param_split = find_substr(line, "S ", &ps)) && NULL != set.scene.spr_t)
			myerror("Error\nTwo or more S param\n", 0, &set);
	else if (NULL != (param_split = find_substr(line, "F ", &ps)) && -1 != set.scene.f_rgb[1])
			myerror("Error\nTwo or more F param\n", 0, &set);
	else if (NULL != (param_split = find_substr(line, "C ", &ps)) && -1 != set.scene.c_rgb[1])
			myerror("Error\nTwo or more C param\n", 0, &set);

}

static void			parsing_params(int *ps, char *line, t_set *set)
{
	char			**param_split;
	int				i;
	int				j;

	i = 1;
	if (NULL != (param_split = find_substr(line, "R ", ps)))
	{
		if (get_wrd_cnt(line, ' ') > 3)
			myerror("Error\nThree or more R param in line\n", 0, set);
		while (i < 3)
		{
			j = 0;
			while (param_split[i][j] != '\0')
			{
				if (ft_isalpha(param_split[i][j]))
					myerror("Error\nInvalid R param.\n", 0, set);
				j++;
			}
			printf("%s\n", param_split[i]);
			i++;
		}


			

		
		set->scene.rxy[0] = ft_atoi(*(param_split + 1));
		set->scene.rxy[1] = ft_atoi(*(param_split + 2));
		free_param_split(param_split, 3);
		return ;
	}
	else if (NULL != (param_split = find_substr(line, "NO ", ps)) && get_wrd_cnt(line, ' ') == 2)
		set->scene.no_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "SO ", ps)) && get_wrd_cnt(line, ' ') == 2)
		set->scene.so_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "WE ", ps)) && get_wrd_cnt(line, ' ') == 2)
		set->scene.we_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "EA ", ps)) && get_wrd_cnt(line, ' ') == 2)
		set->scene.ea_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "S ", ps)) && get_wrd_cnt(line, ' ') == 2)
		set->scene.spr_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "F ", ps)) && get_wrd_cnt(line, ' ') == 2)
		set_rgb_params(set, *(param_split + 1), 'f');
	else if (NULL != (param_split = find_substr(line, "C ", ps)) && get_wrd_cnt(line, ' ') == 2)
		set_rgb_params(set, *(param_split + 1), 'c');
	else if (get_wrd_cnt(line, ' ') == 1)
		myerror("Error\nInvalid conut of param.\n", 0, set);
	param_split != NULL ? free_param_split(param_split, 2) : NULL;
}

static void			parsing_map(t_list **map_lines, t_set *set)
{
	int				i;
	t_list			*ptr_tmp;
	t_list			*free_tmp;
	size_t			max_x;

	set->scene.map = ft_calloc(ft_lstsize(*map_lines) + 1, sizeof(char *));
	i = 0;
	max_x = 0;
	ptr_tmp = *map_lines;
	free_tmp = *map_lines;
	while (ptr_tmp)
	{
		set->scene.map[i] = ft_strdup((char *)ptr_tmp->content);
		if (ft_strlen(set->scene.map[i]) > max_x)
			max_x = ft_strlen(set->scene.map[i]);
		ptr_tmp = ptr_tmp->next;
		i++;
	}
	set->scene.map[i] = NULL;
	set->tabs.map_h = i;
	set->tabs.map_w = max_x;
	// printf("%d - %ld]>\n", i, max_x);
	ft_lstclear(&free_tmp, free_content);
}

void				find_player(t_set *set)
{
	int x;
	int y;
	int pcount = 0;

	x = 0;
	y = 0;
	pcount = 0;
	while (set->scene.map[y])
	{
		while (set->scene.map[y][x])
		{	
			pcount += where_player(set, set->scene.map[y][x], x, y);
			x++;
		}
		x = 0;
		y++;
	}
	pcount == 0 ? myerror("Error\nInvalid map!!!\n", 0, set) : 0;
	pcount > 1 ? myerror("Error\nThe player must be alone.\n", 0, set) : 0;
}

void				parsing_scene(char **av, t_set *set)
{
	char			*line;
	int				ps;
	int				fd;
	t_list			*map_lines;

	if ((fd = open(*(av + 1), O_RDONLY)) == -1)
		myerror("Error\nNo such file exists\n", 0, set);
	ps = 0;
	map_lines = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		
		isfullparam(*set, line);
		if (ps < 8)
			parsing_params(&ps, line, set);
		else if (NULL != ft_strnstr(line, "1", ft_strlen(line)))
			ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(line)));
		ft_memdel(&line);
	}
	ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(line)));
	ft_memdel(&line);
	if (ps < 8)
		myerror("Error\nToo few parameters or they or the file is empty.\n",
		0, set);
	else if (ps > 8)
		myerror("Error\nToo much parameters.\n", 0, set);
	parsing_map(&map_lines, set);
	if (close(fd) == -1)
		myerror("Error\nScene the file does not close.\n", 5, set);
}
