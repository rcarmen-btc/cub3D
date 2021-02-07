/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:58:26 by rcarmen           #+#    #+#             */
/*   Updated: 2020/12/08 23:16:39 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *np)
{
	int				sign;
	int				res;

	sign = 1;
	res = 0;
	while (ft_isspace(*np))
		np++;
	if (*np == '-' || *np == '+')
		sign = *np++ == '-' ? -1 : 1;
	while (ft_isdigit(*np))
		res = (res * 10) + (*np++ - '0');
	return (res * sign);
}
