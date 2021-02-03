/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:20:03 by rcarmen           #+#    #+#             */
/*   Updated: 2020/11/12 01:05:17 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *back;

	if (lst == NULL)
		return ;
	back = *lst;
	if (back == NULL)
		*lst = new;
	else
	{
		while (back->next != NULL)
			back = back->next;
		back->next = new;
	}
}
