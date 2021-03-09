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

static void			parsing_params(int *ps, char *line, t_set *set)
{
	char			**param_split;

	if (NULL != (param_split = find_substr(line, "R ", ps)))
	{
		set->scene.rxy[0] = ft_atoi(*(param_split + 1));
		set->scene.rxy[1] = ft_atoi(*(param_split + 2));
		free_param_split(param_split, 3);
		return ;
	}
	else if (NULL != (param_split = find_substr(line, "NO ", ps)))
		set->scene.no_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "SO ", ps)))
		set->scene.so_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "WE ", ps)))
		set->scene.we_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "EA ", ps)))
		set->scene.ea_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "S ", ps)))
		set->scene.spr_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "F ", ps)))
		set_rgb_params(set, *(param_split + 1), 'f');
	else if (NULL != (param_split = find_substr(line, "C ", ps)))
		set_rgb_params(set, *(param_split + 1), 'c');
	param_split != NULL ? free_param_split(param_split, 2) : NULL;
}

static void			parsing_map(t_list **map_lines, t_set *set)
{
	int				i;
	t_list			*ptr_tmp;
	t_list			*free_tmp;
	size_t				max_x;

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
	set->tabs.map_h = i;
	set->tabs.map_w = max_x;
	ft_lstclear(&free_tmp, free_content);
	//isvalid_map(params);
}

void				find_player(t_set *set)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (set->scene.map[y])
	{
		while (set->scene.map[y][x])
		{
			set->scene.map[y][x] == 'N' ? set->pattr.fpa = set->ray.angle270 : 0;
			set->scene.map[y][x] == 'W' ? set->pattr.fpa = set->ray.angle180 : 0;  
			set->scene.map[y][x] == 'E' ? set->pattr.fpa = set->ray.angle0 : 0; 
			set->scene.map[y][x] == 'S' ? set->pattr.fpa = set->ray.angle90 : 0; 

			if (ft_isalpha(set->scene.map[y][x]))
			{
				set->pattr.fpx = x * 64 + 32;
				set->pattr.fpy = y * 64 + 32;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void				parsing_scene(char **av, t_set *set)
{
	char			*line;
	int				ps;
	int				fd;
	t_list			*map_lines;

	if ((fd = open(*(av + 1), O_RDONLY)) == -1)
		myerror("error: No such file exists\n", 1, set);
	ps = 0;
	map_lines = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ps < 8)
			parsing_params(&ps, line, set);
		else if (NULL != ft_strnstr(line, "1", ft_strlen(line)))
			ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(line)));
		ft_memdel(&line);
	}
	ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(line)));
	ft_memdel(&line);
	if (ps < 8)
		myerror("error: Incorrect number of patams.\n", 1, set);
	parsing_map(&map_lines, set);
	if (close(fd) == -1)
		myerror("error: Scene the file does not close.\n", 2, set);
}
