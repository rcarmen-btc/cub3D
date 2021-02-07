/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:20:14 by rcarmen           #+#    #+#             */
/*   Updated: 2020/11/16 13:23:15 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void	*))
{
	t_list	*tmp;

	if (del != NULL)
		while (*lst != NULL)
		{
			del((*lst)->content);
			tmp = *lst;
			*lst = tmp->next;
			free(tmp);
		}
	*lst = 0;
}
