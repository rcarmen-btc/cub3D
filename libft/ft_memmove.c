/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:22:56 by rcarmen           #+#    #+#             */
/*   Updated: 2020/11/05 22:08:43 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d_ptr;
	unsigned char	*s_ptr;
	size_t			i;

	i = 0;
	d_ptr = (unsigned char *)dest;
	s_ptr = (unsigned char *)src;
	while (d_ptr < s_ptr && i < n)
	{
		d_ptr[i] = s_ptr[i];
		i++;
	}
	while (d_ptr > s_ptr && i < n)
	{
		d_ptr[n - 1] = s_ptr[n - 1];
		n--;
	}
	return (dest);
}
