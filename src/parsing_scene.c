/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/02/11 12:57:50 by rcarmen          ###   ########.fr       */
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

static void			valid_map(t_params *params)
{
	int				i;

	i = -1;
	while (params->map[++i])
	{
		ft_printf("%s\n", params->map[i]);
	}	
}

static void			parsing_params(int *ps, char *line, t_params *params)
{
	char			**param_split;

	if (NULL != (param_split = find_substr(line, "R ", ps)))
	{
		params->resol_xy[0] = ft_atoi(*(param_split + 1));
		params->resol_xy[1] = ft_atoi(*(param_split + 2));
		free_param_split(param_split, 3);
		return ;
	}
	else if (NULL != (param_split = find_substr(line, "NO ", ps)))
		params->no_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "SO ", ps)))
		params->so_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "WE ", ps)))
		params->we_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "EA ", ps)))
		params->ea_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "S ", ps)))
		params->sprite_t = ft_strdup(*(param_split + 1));
	else if (NULL != (param_split = find_substr(line, "F ", ps)))
		set_rgb_params(params, *(param_split + 1), 'f');
	else if (NULL != (param_split = find_substr(line, "C ", ps)))
		set_rgb_params(params, *(param_split + 1), 'c');
	param_split != NULL ? free_param_split(param_split, 2) : NULL;
}

static void			parsing_map(t_list **map_lines, t_params *params)
{
	int				i;
	t_list			*ptr_tmp;
	t_list			*free_tmp;

	params->map = ft_calloc(ft_lstsize(*map_lines) + 1, sizeof(char *));
	i = 0;
	ptr_tmp = *map_lines;
	free_tmp = *map_lines;
	while (ptr_tmp)
	{
		params->map[i++] = ft_strdup((char *)ptr_tmp->content);
		ptr_tmp = ptr_tmp->next;
	}
	ft_lstclear(&free_tmp, free_content);
	valid_map(params);
}

void				parsing_scene(int fd, t_params *params)
{
	char			*line;
	int				ps;
	t_list			*map_lines;

	ps = 0;
	map_lines = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ps < 8)
			parsing_params(&ps, line, params);
		else
			if (NULL != ft_strnstr(line, "1", ft_strlen(line)))
				ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(line)));
		ft_memdel(&line);
	}
	if (ps < 8)
		return ;
	ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(line)));
	ft_memdel(&line);
	parsing_map(&map_lines, params);
}
